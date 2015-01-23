#pragma once
#include "Asset.hpp"
#include <glm/glm.hpp>
#include <map>

class Texture;


struct LetterFontUV
{
	glm::vec2 bottomLeft, topRight;

	LetterFontUV()
	{

	}
	LetterFontUV(glm::vec2 botLeft, glm::vec2 topRight)
	{
		this->bottomLeft = botLeft;
		this->topRight = topRight;
	}

};


class Font :
	public Asset
{
public:
	Font(shared_ptr<Texture> fontTexture, map<char, LetterFontUV> charUVMap, int fontSize);
	virtual ~Font();
	
	shared_ptr<Texture> fontTexture;
	int fontSize;
	map<char, LetterFontUV> charUVMap;


};

