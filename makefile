CFLAGS=`pkg-config --cflags --libs libxml-2.0` `xslt-config --cflags` -g -Wall -Wextra -O3 -std=c99
LDLIBS=`pkg-config --libs libxml-2.0` `xslt-config --libs` -larchive
objects=fileinfo.o transform.o zip.o xmlbuff.o
mingwCFLAGS=`x86_64-w64-mingw32-pkg-config --cflags --libs libxml-2.0 libxslt` -g -Wall -Wextra -O3 -std=c99
mingwLDLIBS=`x86_64-w64-mingw32-pkg-config --libs libxml-2.0 libxslt`  -larchive
mingw=x86_64-w64-mingw32-gcc
MACCFLAGS=`pkg-config --cflags --libs libxml-2.0 libarchive` `xslt-config --cflags` -g -Wall -Wextra -O3 -std=c99
MACLDLIBS=`pkg-config --libs libxml-2.0 libarchive` `xslt-config --libs`

extractText: $(objects)

win/extractText.exe:
	$(mingw) $(mingwCFLAGS) -c fileinfo.c $(mingwLDLIBS)
	$(mingw) $(mingwCFLAGS) -c transform.c $(mingwLDLIBS)
	$(mingw) $(mingwCFLAGS) -c zip.c $(mingwLDLIBS)
	$(mingw) $(mingwCFLAGS) -c xmlbuff.c $(mingwLDLIBS)
	$(mingw) $(mingwCFLAGS) extractText.c $(objects) $(mingwLDLIBS) -o $@

mac/extractText:
	gcc $(MACCFLAGS) -c fileinfo.c $(MACLDLIBS)
	gcc $(MACCFLAGS) -c transform.c $(MACLDLIBS)
	gcc $(MACCFLAGS) -c zip.c $(MACLDLIBS)
	gcc $(MACCFLAGS) -c xmlbuff.c $(MACLDLIBS)
	gcc $(MACCFLAGS) extractText.c $(objects) $(MACLDLIBS) -o $@

.PHONY: clean
clean:
	rm *.o

win: win/extractText.exe

mac: mac/extractText

default: extractText
