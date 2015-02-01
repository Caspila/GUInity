#include "Font.hpp"
#include <iostream>

/** Constructor from a Texture, a map of available chars and their UVMapping and the font size.*/
Font::Font(shared_ptr<Texture> fontTexture, map<char, LetterFontUV> charUVMap, int fontSize)
{
	this->fontTexture = fontTexture;
	this->charUVMap = charUVMap;
	this->fontSize = fontSize;
}

/** fontTexture getter*/
shared_ptr<Texture> Font::getFontTexture()
{
	return fontTexture;
}
/** fontSize getter*/
int Font::getFontSize()
{
	return fontSize;
}
/** charUVMap getter*/
map<char, LetterFontUV> Font::getCharUVMap()
{
	return charUVMap;
}
/** Returns the LetterFontUV of a char in this font*/
LetterFontUV Font::getCharDesc(char c)
{
	auto it = charUVMap.find(c);
	if (it == charUVMap.end())
	{
		cerr << "Font does not contain character: " << c << endl;
	}

	return charUVMap[c];
}

