#include <stdio.h>
#include <string.h>
#include "fileinfo.h"
#include "transform.h"
#include "zip.h"
#include "stopif.h"
#include "extractText.h"
#include "incbin.h"

INCBIN(DocxToTxt, "xsl/docxToTxt.xsl");
INCBIN(PptxToTxt, "xsl/pptxToTxt.xsl");
INCBIN(XlsxToTxt, "xsl/xlsxToTxt.xsl");

void usage(const char *name) {
	printf("%s inputFile\n", name);
	printf("Docx, xlsx and pptx are supported.\n");
}

int main(int argc, char **argv) {
	if (argc < 2) {
		usage(argv[0]);
		return 1;
	}

	struct fileInfo *fi = newFileInfo(argv[1]);
	Stopif(!fi, return 1, "Can't establish fileinfo!\n");

	if (strcmp(fi->ext, "docx") == 0) {
		Stopif(!transformLoad((char*)gDocxToTxtData, gDocxToTxtSize), return 1, "Can't load transform!\n");
		readZIP(fi->fullname, wordFile);
		transformCleanup();
	}
	else if (strcmp(fi->ext, "pptx") == 0) {
		Stopif(!transformLoad((char*)gPptxToTxtData, gPptxToTxtSize), return 1, "Can't load transform!\n");
		readZIP(fi->fullname, slideFiles);
		readZIP(fi->fullname, drawingFiles);
		transformCleanup();
	}
	else if (strcmp(fi->ext, "xlsx") == 0) {
		Stopif(!transformLoad((char*)gXlsxToTxtData, gXlsxToTxtSize), return 1, "Can't load transform!\n");
		readZIP(fi->fullname, xlsxFile);
		transformCleanup();
	}

	free(fi);
}
