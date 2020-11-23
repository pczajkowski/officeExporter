struct fileInfo
{
	char *fullname, *name, *ext;
	size_t fullnameLength, nameLength, basenameLength;
	char *_base; // this is just for slicing
};

struct fileInfo* newFileInfo(const char *filePath);
void freeFileInfo(struct fileInfo *info);
