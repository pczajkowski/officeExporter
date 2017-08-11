#include <stdlib.h>
#include "xmlbuff.h"

XMLBuff *XMLBuffNew(void) {
	XMLBuff *out = malloc(sizeof(XMLBuff));
	*out = (XMLBuff){ .data=NULL };                          
	return out;
}

void XMLBuffFree(XMLBuff *in) {
	free(in);
}