#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include "fileinfo.h"

#define FAILURE 0
#define SUCCESS 1

static int initializeFullname(struct fileInfo *info, const char *filePath) {
	info->fullnameLength = strlen(filePath);
	info->fullname = malloc(info->fullnameLength+1);
	if (!info->fullname) return FAILURE;

	strcpy(info->fullname, filePath);
	return SUCCESS;
}

static int initializeBasename(struct fileInfo *info) {
	char *base = basename(info->fullname);
	info->basenameLength = strlen(base);
	info->_base = malloc(info->basenameLength+1);
	if (!info->_base) return FAILURE;

	strcpy(info->_base, base);
	return SUCCESS;
}

static int initializeExt(struct fileInfo *info) {
	char *baseCopy = malloc(info->basenameLength+1);
	if (!baseCopy) return FAILURE;
	strcpy(baseCopy, info->_base);

	char *dot = strrchr(baseCopy, '.');
	if (!dot) {
		free(baseCopy);
		return FAILURE;
	}
	dot[0] = '\0';

	info->nameLength = strlen(baseCopy);
	info->name = malloc(info->nameLength+1);
	if (!info->name) {
		free(baseCopy);
		return FAILURE;
	}
	strcpy(info->name, baseCopy);

	info->ext = malloc(strlen(dot+1)+1);
	if (!info->ext) {
		free(baseCopy);
		return FAILURE;
	}
	strcpy(info->ext, dot+1);

	free(baseCopy);
	return SUCCESS;
}

struct fileInfo* newFileInfo(const char *filePath) {
	if (!strrchr(filePath, '.')) return NULL;

	struct fileInfo *info = malloc(sizeof(struct fileInfo));
	if (!info) return NULL;

	if (!initializeFullname(info, filePath)) return NULL;

	if (!initializeBasename(info)) return NULL;

	if (initializeExt(info)) return info;

	freeFileInfo(info);
	return NULL;
}

void freeFileInfo(struct fileInfo *info) {
	free(info->fullname);
	free(info->_base);
	free(info->name);
	free(info->ext);
	free(info);
}
