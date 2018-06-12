#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "fileinfo.h"

struct fileInfo* newFileInfo(const char *filePath) {
	if (!strrchr(filePath, '.')) return NULL;

	struct fileInfo *info = malloc(sizeof(struct fileInfo));
	info->fullname = malloc(strlen(filePath)+1);
	strcpy(info->fullname, filePath);

	info->_base = malloc(strlen(basename(info->fullname))+1);
	strcpy(info->_base, basename(info->fullname));

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
