//
//  Texture.cpp
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-12.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "Texture.h"

Texture::Texture()
{
    
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
}


void Texture::init()
{
    // Create one OpenGL texture
    //GLuint textureID;
    glGenTextures(1, &textureID);
    
    // "Bind" the newly created texture : all future texture functions will modify this texture
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    // Give the image to OpenGL
    glTexImage2D(GL_TEXTURE_2D, 0,GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)data);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
}