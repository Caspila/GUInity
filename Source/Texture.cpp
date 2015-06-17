//
//  Texture.cpp
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-12.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "Texture.hpp"

/** Constructor
 @param[in] buffer The image data buffer
 @param[in] width The width of the image
 @param[in] height The height of the image
 */
Texture::Texture(void* buffer, int width, int height, ColorBitDepth depth)
: data{buffer}, width{width}, height{height}, depth{depth}
{
	createOpenGLTextureBuffer();
}

/** Default Destructor */
Texture::~Texture()
{
  	delete[] data;
    
    glDeleteTextures(1, &textureID);
}


/** Creates the OpenGL-specific texture buffer */
void Texture::createOpenGLTextureBuffer()
{
    // Create one OpenGL texture
    glGenTextures(1, &textureID);
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    GLint glDepth = GL_RGBA;
    
    switch (depth) {
        case ColorBitDepth::RGB:
            glDepth = GL_RGB;
            break;
        case ColorBitDepth::RGBA:
            glDepth = GL_RGBA;
            break;
        default:
            break;
    }
    
    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,glDepth, width, height, 0, glDepth, GL_UNSIGNED_BYTE, (GLvoid*)data);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    
}

/** textureID Getter
 @return OpenGL-specific texture ID
 */
GLuint Texture::getTextureID() const
{
    return textureID;
}