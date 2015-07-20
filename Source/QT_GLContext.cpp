//
//  QT_GLContex.cpp
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-07-14.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "QT_GLContext.hpp"


QT_GLContext::QT_GLContext(QWindow *window, QOpenGLContext *context)

{
        this->window = window;
    this->context = context;
}

int QT_GLContext::init(int screenWidth, int screenHeight)
{
    return 0;
}

void QT_GLContext::swapBuffers()
{
    context->swapBuffers(window);
//    glCanvas->wxGLCanvasBase::SwapBuffers();
}

void QT_GLContext::shutdown()
{
}

bool QT_GLContext::shouldClose()
{
    return false;
}