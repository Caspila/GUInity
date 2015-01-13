//
//  UILayout.h
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-12.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __opengl_testing_mag__UILayout__
#define __opengl_testing_mag__UILayout__

#include "Module.hpp"
#include <memory>
#include <glm/glm.hpp>

class UIWidget;

class UILayout
{
public:
    glm::vec4 getPositionFor(shared_ptr<UIWidget> container, shared_ptr<UIWidget> newWidget);
};

#endif /* defined(__opengl_testing_mag__UILayout__) */
