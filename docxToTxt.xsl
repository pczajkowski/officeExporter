<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:w="http://schemas.openxmlformats.org/wordprocessingml/2006/main">
	<xsl:output method="text" encoding="UTF-8"/>

	<xsl:template match="/">
    <xsl:apply-templates select="//w:p" />
	</xsl:template>

	<xsl:template match="//w:p">
		<xsl:variable name="output">
				<xsl:for-each select="./w:r/w:t">
					<xsl:value-of select="./text()"/>
				</xsl:for-each>
		</xsl:variable>
		<xsl:if test="$output != ''">
			<xsl:value-of select="$output"/>
			<xsl:text>&#xA;</xsl:text> <!-- line break-->
		</xsl:if>
	</xsl:template>
</xsl:stylesheet>
