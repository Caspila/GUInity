//
//  WXGL_Context.h
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-07-13.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __GUInity_MacOS__WXGL_Context__
#define __GUInity_MacOS__WXGL_Context__

#include <iostream>
#include "GLContext.hpp"

#define __WXMAC_XCODE__
#define __WXOSX_COCOA__
//#define wxUSE_GLCANVAS

#include <iostream>
#include <memory>
#include <string>

//#include <wx/wx.h>
//#include <wx/glcanvas.h>
#include "StaticCounter.hpp"

class wxGLCanvas;
class wxGLContext;

class WXGL_Context : public GLContext
{
private:
    wxGLCanvas * glCanvas;
    wxGLContext*   context;
    
public:
    WXGL_Context(wxGLCanvas * glCanvas,wxGLContext*   context);
    virtual void swapBuffers() override;
    virtual int init(int screenWidth, int screenHeight) override;
    virtual void shutdown() override;
    virtual bool shouldClose() override;
};

#endif /* defined(__GUInity_MacOS__WXGL_Context__) */
