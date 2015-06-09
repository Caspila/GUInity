#pragma once
#include "Asset.hpp"
#include <glm/glm.hpp>
#include <map>

class Texture;


struct LetterFontUV
{
	glm::vec2 bottomLeft, topRight;
	float ratio;

	LetterFontUV()
	{

	}
	LetterFontUV(glm::vec2 botLeft, glm::vec2 topRight, float ratio)
	{
		this->bottomLeft = botLeft;
		this->topRight = topRight;
		this->ratio = ratio;
	}
	

};


/** Font is an Asset. It holds the information of the font size, the available characters and their UV mapping to the
	corresponding Texture */
class Font :
	public Asset
{
private:
	/** The Texture of the font */
	shared_ptr<Texture> fontTexture;
	/** The font size */
	int fontSize;
	/** The list of available characters and their UV mapping according to the fontTexture */
	map<char, LetterFontUV> charUVMap;

public:
	/** Constructor from a Texture, a map of available chars and their UVMapping and the font size.*/
	Font(shared_ptr<Texture> fontTexture, map<char, LetterFontUV> charUVMap, int fontSize);
	/** Default Destructor. Virtual cause it's children class */
	virtual ~Font() {}
	
	/** fontTexture getter*/
	shared_ptr<Texture> getFontTexture() const;
	/** fontTexture getter*/
    void setFontTexture(shared_ptr<Texture> fontTexture);
	
    /** fontSize getter*/
	int getFontSize();
	/** charUVMap getter*/
	map<char, LetterFontUV> getCharUVMap();
	/** Returns the LetterFontUV of a char in this font*/
	LetterFontUV getCharDesc(char c);

};

