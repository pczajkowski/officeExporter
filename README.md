# Extract text from Office documents

This tool will help you to extract text from various Office documents into text files.

Usage is simple:

	./extractText test.docx - content of document.xml will be exported as document.txt

Same is true for other file types:

	./extractText test.pptx - content of each slideNUMBER.xml and drawingNUMBER.xml will be exported as slideNUMBER.txt and drawingNUMBER.txt respectively

	./extractText test.xlsx - content of sharedStrings.xml will be exported as sharedStrings.txt

As you can see for Excel files export is limited to shared strings which are stored in order of input to original document. First entered text is first on the list, last will be last. This list won't contain duplicated values.

This is a hobby project created for fun and to explore C and its libraries further. Feel free to use it however you want, but I take no responsibility for eventual damage.

It's using [incbin](https://github.com/graphitemaster/incbin) for embedding xsl files into binary.
