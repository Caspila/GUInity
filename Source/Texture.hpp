//
//  Texture.h
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-12.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __opengl_testing_mag__Texture__
#define __opengl_testing_mag__Texture__

#include <iostream>
#include "Asset.hpp"
#include "Module.hpp"

class Texture : public Asset
{
public:
    Texture(void* buffer, int width, int height);
	Texture();
    ~Texture();
    
    void init();
    void* data;
    
    int width, height;
    
    GLuint textureID;
};

#endif /* defined(__opengl_testing_mag__Texture__) */
