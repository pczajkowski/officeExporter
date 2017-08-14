#include <stdio.h>
#include <string.h>
#include <archive.h>
#include <archive_entry.h>

int processContent(struct archive *archiveIn, const char *fileMask);
int readZIP(char const *infile, const char *fileMask);