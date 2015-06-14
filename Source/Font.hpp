//
//  Font.hpp
//  GUInity Project - A 3D component-based one-man game engine
//
//  Created by Guilherme Cunha on 2014-12-30.
//  Copyright (c) 2014 Guilherme Cunha. All rights reserved.
//

#pragma once
#include "Asset.hpp"
#include <glm/glm.hpp>
#include <map>

class Texture;



/** Describes the UV and ratio for a letter in a Font */
struct LetterFontUV
{
    /** The UV */
	glm::vec2 bottomLeft, topRight;
    /** The ratio (width/height) */
	float ratio;

    /** Default Constructor */
	LetterFontUV() {}
    
    /** Constructor
     @param[in] bottomLeft the bottom left UV coordinate
     @param[in] topRight the top right UV coordinate
     @param[in] ratio the ratio of the letter (width/height)
     */
	LetterFontUV(glm::vec2 bottomLeft, glm::vec2 topRight, float ratio) :
    bottomLeft {bottomLeft}, topRight {topRight}, ratio{ratio}
	{	}

};



/** A catalog of all available characters and their description for a Font */
class CharacterCatalog
{
private:
    
    /** The list of available characters and their UV mapping according to the fontTexture */
  	map<char, LetterFontUV> charUVMap;
public:
    /** Default Constructor */
    CharacterCatalog() {}
    /** Default Destructor */
    ~CharacterCatalog() {}
    
    /** Adds a new description to the catalog
     @param[in] character the character
     @param[in] fontUV the LetterFontUV description of the character */
    void addCharacterDescription(char character, LetterFontUV fontUV)
    {
        charUVMap[character] = fontUV;
    }
    /** Get the description for a character
     @param[in] character the character
     @return the LetterFontUV description for the character */
    const LetterFontUV& getCharacterDescription(char character)
    {
        auto it = charUVMap.find(character);
        if (it == charUVMap.end())
        {
            cerr << "Character Catalog does not contain character: " << character << endl;
            return LetterFontUV();
        }
        return charUVMap[character];
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
	CharacterCatalog characterCatalog;

public:
	/** Constructor from a Texture, a map of available chars and their UVMapping and the font size.*/
	Font(shared_ptr<Texture> fontTexture, CharacterCatalog characterCatalog, int fontSize);
	/** Default Destructor */
	virtual ~Font() {}

    /** fontTexture Setter
     @param[in] fontTexture the texture for this font
     */
    void setFontTexture(shared_ptr<Texture> fontTexture);
	/** fontTexture Getter
     @return the texture of the Font
     */
	const shared_ptr<Texture> getFontTexture() const;

    /** fontSize Getter
     @return the size of the font
     */
	int getFontSize() const;

	/** characterCatalog Getter
     @return the character catalog of this Font
     */
	const CharacterCatalog& getCharacterCatalog();

	/** Returns the reference of a LetterFontUV struct for a specific character
     @param[in] c the character
     @return the LetterFontUV struct (UV coordinates and letter ratio) of the character
     */
	const LetterFontUV& getCharDesc(char c);

};

