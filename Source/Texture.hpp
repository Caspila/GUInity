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

/** Texture is an Asset that holds image data and the OpenGL-specific Texture ID
 */
class Texture : public Asset
{
private:
    /** The width of the image */
    int width;
    /** The height of the image */
    int height;
    
    /** Pointer to the image buffer */
    void* data;
    
    /** The OpenGL-specific texture buffer ID */
    GLuint textureID;
    

    
public:
    /** Constructor
     @param[in] buffer The image data buffer
     @param[in] width The width of the image
     @param[in] height The height of the image
     */
    Texture(void* buffer, int width, int height);
    /** Default Constructor */
	Texture();
    /** Default Destructor */
    virtual ~Texture();
    
    /** Creates the OpenGL-specific texture buffer */
    void createOpenGLTextureBuffer();

    /** textureID Getter
     @return OpenGL-specific texture ID
     */
    GLuint getTextureID() const;
    
};

#endif
