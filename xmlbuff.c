#include <stdlib.h>
#include "xmlbuff.h"

XMLBuff *XMLBuffNew(char *data, const char *name, int size) {
	XMLBuff *out = malloc(sizeof(XMLBuff));
	if (!out) return NULL;

	*out = (XMLBuff){ .data=data, .name=name, .size=size };
	return out;
}

void XMLBuffFree(XMLBuff *in) {
	if (in) free(in);
}
