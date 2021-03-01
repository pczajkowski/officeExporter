CFLAGS=`xml2-config --cflags` `xslt-config --cflags` -I/usr/local/opt/libarchive/include -g -Wall -Wextra -Wshadow -O3 -std=c99
LDLIBS=`xml2-config --libs` `xslt-config --libs` -larchive
objects=fileinfo.o transform.o zip.o xmlbuff.o

extractText: $(objects)

.PHONY: clean
clean:
	rm *.o

test: default
	@./extractText testFiles/test.docx
	@cmp document.txt testFiles/document.txt
	@rm document.txt
	@./extractText testFiles/test.xlsx
	@cmp sharedStrings.txt testFiles/sharedStrings.txt
	@rm sharedStrings.txt
	@./extractText testFiles/test.pptx
	@cmp drawing1.txt testFiles/drawing1.txt
	@cmp slide1.txt testFiles/slide1.txt
	@cmp slide2.txt testFiles/slide2.txt
	@cmp slide3.txt testFiles/slide3.txt
	@rm drawing1.txt
	@rm slide1.txt
	@rm slide2.txt
	@rm slide3.txt
	@rm extractText

default: extractText
