struct fileInfo
{
	char *fullname, *name, *ext;
	int fullnameLength, nameLength;
	char *_base; // this is just for slicing
};

struct fileInfo* newFileInfo(const char *filePath);
void freeFileInfo(struct fileInfo *info);
