#include "zip.h"
#include "transform.h"
#include "stopif.h"

static int processContent(struct archive *archiveIn, const char *fileMask) {
	struct archive_entry *entryIn;

	while (archive_read_next_header(archiveIn, &entryIn) == ARCHIVE_OK) {
		const char* path = archive_entry_pathname(entryIn);
		if (strstr(path, fileMask) == NULL) continue;

		int64_t size = archive_entry_size(entryIn);
		char buf[size];
		Stopif(archive_read_data(archiveIn, buf, size) != size, return 0, "Archive entry has no size (%s)!\n", path);

		XMLBuff *file = XMLBuffNew(buf, path, size);
		Stopif(!file, return 0, "Can't create XMLBuff for %s!\n", path);
		Stopif(!transformXML(file), return 0, "Can't process file (%s)!\n", path);
		XMLBuffFree(file);
	}
	return 1;
}

int readZIP(char const *infile, const char *fileMask) {
	struct archive *archiveIn;

	archiveIn = archive_read_new();
	archive_read_support_format_zip(archiveIn);
	Stopif(archive_read_open_filename(archiveIn, infile, 10240) != ARCHIVE_OK, return 0, "Can't read file %s!\n", infile);

	Stopif(!processContent(archiveIn, fileMask), return 0, "Can't process file %s!\n", infile);

	Stopif(archive_read_free(archiveIn) != ARCHIVE_OK, return 0, "Can't free %s!\n", infile);
	return 1;
}
