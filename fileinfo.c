#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "fileinfo.h"

struct fileInfo* newFileInfo(const char *filePath) {
	if (!strrchr(filePath, '.')) return NULL;

	struct fileInfo *info = malloc(sizeof(struct fileInfo));
	size_t filePathLength = strlen(filePath);
	info->fullname = calloc(filePathLength+1, 1);
	strncpy(info->fullname, filePath, filePathLength);
	
	size_t basenameLength = strlen(basename(info->fullname));
	info->_base = calloc(basenameLength+1, 1);
	strncpy(info->_base, basename(info->fullname), basenameLength);

	char *dot = ".";
	info->name = strtok(info->_base, dot);
	info->ext = strtok(NULL, dot);
	if (info->name && info->ext)
		return info;
	freeFileInfo(info);
	return NULL;
}

void freeFileInfo(struct fileInfo *info) {
	free(info->fullname);
	free(info->_base);
	free(info);
}
