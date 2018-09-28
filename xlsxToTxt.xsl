<?xml version="1.0"?>
<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
xmlns:xlsx="http://schemas.openxmlformats.org/spreadsheetml/2006/main">
	<xsl:output method="text" encoding="UTF-8" />

	<xsl:template match="/">
		<xsl:apply-templates select="//xlsx:t" />
	</xsl:template>

	<xsl:template match="//xlsx:t">
    	<xsl:value-of select="./text()" />
    	<xsl:text>&#xA;</xsl:text> <!-- line break-->
	</xsl:template>
</xsl:stylesheet>
