#include <string.h>
#include <stdio.h>
#include <libxml/xmlmemory.h>
#include <libxml/debugXML.h>
#include <libxml/HTMLtree.h>
#include <libxml/xmlIO.h>
#include <libxml/xinclude.h>
#include <libxml/catalog.h>
#include <libxslt/xslt.h>
#include <libxslt/xsltInternals.h>
#include <libxslt/transform.h>
#include <libxslt/xsltutils.h>
#include "fileinfo.h"
#include "transform.h"

extern int xmlLoadExtDtdDefaultValue;

xmlDocPtr stylesheetDoc;
xsltStylesheetPtr stylesheet;
int transformLoad(const char *stylesheetData, size_t stylesheetSize) {
	xmlLoadExtDtdDefaultValue = 1;
	xmlSubstituteEntitiesDefault(1);

	stylesheetDoc = xmlReadMemory(stylesheetData, stylesheetSize, NULL, NULL, 0);
	Stopif(!stylesheetDoc, return 0, "Unable to read stylesheet !\n");
	stylesheet = xsltParseStylesheetDoc(stylesheetDoc);
	Stopif(!stylesheet, return 0, "Unable to parse stylesheet !\n");
	return 1;
}

int transformXML(const XMLBuff *infile) {
	xmlDocPtr doc = xmlReadMemory(infile->data, infile->size, infile->name, NULL, 0);
	Stopif(!doc, return 0, "Unable to read %s!\n", infile->name);
	xmlDocPtr result = xsltApplyStylesheet(stylesheet, doc, NULL);
	Stopif(!result, return 0, "Transformation failed for %s!\n", infile->name);

	struct fileInfo *fi = newFileInfo(infile->name);
	Stopif(!fi, return 0, "Failed to establish fileinfo for %s!\n", infile->name);

	int toPrint = fi->nameLength+5;
	char *outFile = malloc(toPrint);
	Stopif(toPrint <= snprintf(outFile, toPrint, "%s.txt", fi->name), return 0, "Failed to create output filename for %s!\n", infile->name);
	freeFileInfo(fi);

	FILE *fp = fopen(outFile, "w");
	Stopif(!fp, return 0, "Can't open %s for writing!\n", outFile);
	Stopif(xsltSaveResultToFile(fp, result, stylesheet) < 0, return 0, "Nothing saved to %s!\n", outFile);
	fclose(fp);
	free(outFile);

	xmlFreeDoc(result);
	xmlFreeDoc(doc);
	return 1;
}

void transformCleanup() {
	xsltFreeStylesheet(stylesheet);
	xsltCleanupGlobals();
	xmlCleanupParser();
}
