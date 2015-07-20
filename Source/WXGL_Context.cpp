//
//  WXGL_Context.cpp
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-07-13.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "WXGL_Context.hpp"

#include <wx/wx.h>
#include <wx/glcanvas.h>


WXGL_Context::WXGL_Context(wxGLCanvas * glCanvas, wxGLContext*   context)

{
    this->glCanvas = glCanvas;
        this->context =context;
}

int WXGL_Context::init(int screenWidth, int screenHeight)
{
    glCanvas->SetCurrent(*context);
    return 0;
}

void WXGL_Context::swapBuffers()
{
    glCanvas->SwapBuffers();
}

void WXGL_Context::shutdown()
{
}

bool WXGL_Context::shouldClose()
{
    return false;
}