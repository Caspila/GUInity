//
//  Font.cpp
//  GUInity Project - A 3D component-based one-man game engine
//
//  Created by Guilherme Cunha on 2014-12-30.
//  Copyright (c) 2014 Guilherme Cunha. All rights reserved.
//

#include "Font.hpp"
#include <iostream>

	/** Constructor from a Texture, a map of available chars and their UVMapping and the font size.*/
Font::Font(shared_ptr<Texture> fontTexture, CharacterCatalog characterCatalog, int fontSize) :
fontTexture{fontTexture}, characterCatalog{characterCatalog}, fontSize{fontSize}
{ }

/** fontTexture Setter
 @param[in] fontTexture the texture for this font
 */
void Font::setFontTexture(shared_ptr<Texture> fontTexture)
{
    this->fontTexture = fontTexture;
}

/** fontTexture Getter
 @return the texture of the Font
 */
const shared_ptr<Texture> Font::getFontTexture() const
{
	return fontTexture;
}
/** fontSize Getter
 @return the size of the font
 */
int Font::getFontSize() const
{
	return fontSize;
}
/** charUVMap Getter
 @return a dictionary that maps each char available for this font to its LetterFontUV struct (UV coordinates and letter ratio)
 */
const CharacterCatalog& Font::getCharacterCatalog()
{
	return characterCatalog;
}

/** Returns the reference of a LetterFontUV struct for a specific character
 @param[in] c the character
 @return the LetterFontUV struct (UV coordinates and letter ratio) of the character
 */
const LetterFontUV& Font::getCharDesc(char c)
{
    return characterCatalog.getCharacterDescription(c);
}

