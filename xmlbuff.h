typedef struct XMLBuff
{
	char *data;
	const char *name;
	int size;
} XMLBuff;

XMLBuff *XMLBuffNew(void);
void XMLBuffFree(XMLBuff *in);
