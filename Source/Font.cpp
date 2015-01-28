#include "Font.hpp"


Font::Font(shared_ptr<Texture> fontTexture, map<char, LetterFontUV> charUVMap, int fontSize)
{
	this->fontTexture = fontTexture;
	this->charUVMap = charUVMap;
	this->fontSize = fontSize;
}


Font::~Font()
{
}
