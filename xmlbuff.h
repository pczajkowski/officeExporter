typedef struct XMLBuff
{
	char *data;
	const char *name;
	int size;
} XMLBuff;

XMLBuff *XMLBuffNew(char *data, const char *name, int size);
void XMLBuffFree(XMLBuff *in);
