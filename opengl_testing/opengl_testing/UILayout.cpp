//
//  UILayout.cpp
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-12.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "UILayout.h"
#include "UIWidget.h"

glm::vec4 UILayout::getPositionFor(shared_ptr<UIWidget> container, shared_ptr<UIWidget> newWidget)
{
    glm::vec4 containerBounds = container->getBounds();
    
    glm::vec4 newWidgetBounds = newWidget->getBounds();
    
    return glm::vec4(containerBounds.z,containerBounds.y,containerBounds.z + newWidgetBounds.z - newWidgetBounds.x,containerBounds.y + newWidgetBounds.w - newWidgetBounds.y);
    
}