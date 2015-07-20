//
//  QT_GLContex.h
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-07-14.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __GUInity_MacOS__QT_GLContex__
#define __GUInity_MacOS__QT_GLContex__

#include <iostream>
#include "GLContext.hpp"
#include <QtGui/qwindow.h>
#include <QtGui/qopengl.h>
#include <QtGui/qopenglcontext.h>

class QT_GLContext : public GLContext
{
private:
    QWindow *window;
    QOpenGLContext *context;
    
public:
    QT_GLContext(QWindow *window, QOpenGLContext *context);
    virtual int init(int screenWidth, int screenHeight);
    virtual void shutdown();
    virtual void swapBuffers();
    virtual bool shouldClose();
};


#endif /* defined(__GUInity_MacOS__QT_GLContex__) */
