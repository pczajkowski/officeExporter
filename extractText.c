#include <stdio.h>
#include <string.h>
#include "transform.h"
#include "zip.h"
#include "stopif.h"
#include "extractText.h"
#include "incbin.h"

INCBIN(DocxToTxt, "docxToTxt.xsl");
INCBIN(PptxToTxt, "pptxToTxt.xsl");
INCBIN(XlsxToTxt, "xlsxToTxt.xsl");

void usage(const char *name) {
	printf("%s inputFile\n", name);
	printf("Docx, xlsx and pptx are supported.\n");
}

int main(int argc, char **argv) {
	if (argc < 2) {
		usage(argv[0]);
		return 1;
	}

	char *dot = strrchr(argv[1], '.');
	Stopif(!dot, return 1, "Bad input file name!\n");

	if (strcmp(dot, ".docx") == 0) {
		Stopif(!transformLoad((char*)gDocxToTxtData, gDocxToTxtSize), return 1, "Can't load transform!\n");
		readZIP(argv[1], wordFile);
		transformCleanup();	
	}
	else if (strcmp(dot, ".pptx") == 0) {
		Stopif(!transformLoad((char*)gPptxToTxtData, gPptxToTxtSize), return 1, "Can't load transform!\n");
		readZIP(argv[1], slideFiles);
		readZIP(argv[1], drawingFiles);
		transformCleanup();
	}
	else if (strcmp(dot, ".xlsx") == 0) {
		Stopif(!transformLoad((char*)gXlsxToTxtData, gXlsxToTxtSize), return 1, "Can't load transform!\n");
		readZIP(argv[1], xlsxFile);
		transformCleanup();
	}
}
