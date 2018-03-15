struct fileInfo
{
	char *fullname, *name, *ext;
	char *_base; // this is just for slicing
};

struct fileInfo* newFileInfo(char const *filePath);
void freeFileInfo(struct fileInfo *info);
