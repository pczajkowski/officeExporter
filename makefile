CFLAGS=`pkg-config --cflags --libs libxml-2.0` `xslt-config --cflags` -I/usr/local/opt/libarchive/include -g -Wall -Wextra -Wshadow -O3 -std=c99
LDLIBS=`pkg-config --libs libxml-2.0` `xslt-config --libs` -larchive
objects=fileinfo.o transform.o zip.o xmlbuff.o

extractText: $(objects)

.PHONY: clean
clean:
	rm *.o

default: extractText
