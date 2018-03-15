#include <stdio.h>
#include <string.h>
#include "transform.h"
#include "zip.h"
#include "stopif.h"
#include "extractText.h"

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
		Stopif(!transformLoad(docxToTxt, sizeof(docxToTxt)), return 1, "Can't load transform!\n");
		readZIP(argv[1], wordFile);
		transformCleanup();	
	}
	else if (strcmp(dot, ".pptx") == 0) {
		Stopif(!transformLoad(pptxToTxt, sizeof(pptxToTxt)), return 1, "Can't load transform!\n");
		readZIP(argv[1], slideFiles);
		transformCleanup();
	}
	else if (strcmp(dot, ".xlsx") == 0) {
		Stopif(!transformLoad(xlsxToTxt, sizeof(xlsxToTxt)), return 1, "Can't load transform!\n");
		readZIP(argv[1], xlsxFile);
		transformCleanup();
	}
}
