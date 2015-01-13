//
//  UIWidget.cpp
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-12.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "UIWidget.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <algorithm>


map<int,vector<shared_ptr<UIWidget>>> UIWidget::depthToWidgetVector;

UIWidget::UIWidget()
{
    color = glm::vec4(1,1,1,1);
    depth = 0;
}

UIWidget::~UIWidget()
{
    
}


void UIWidget::setBounds(glm::vec4 bounds)
{
    this->bounds = bounds;
    
    updatePositionAndScale();
}
void UIWidget::setBounds(float x,float y, float width, float height)
{
    bounds = glm::vec4(x,y,x + width,y + height);
    
    updatePositionAndScale();
}

void UIWidget::updatePositionAndScale()
{
    float x = bounds.x;
    float y = bounds.y;
    float width = bounds.z - bounds.x;
    float height = bounds.w - bounds.y;
    
    position = glm::vec3(x+width/2,y + height/2,0);
    scale = glm::vec3(width,height,1);
}

glm::mat4 UIWidget::getModelMatrix()
{
//    shared_ptr<UIWidget> parentLock = parent.lock();
//    if(!parentLock)
        return glm::translate(position) * glm::scale(scale);
//    else
//    return parentLock->getModelMatrix() * glm::translate(position) * glm::scale(scale);
}


void UIWidget::updateDepth(int newDepth)
{
    auto iterator = find(UIWidget::depthToWidgetVector[depth].begin(),UIWidget::depthToWidgetVector[depth].end(),shared_from_this());
    
    if(iterator != depthToWidgetVector[depth].end())
        UIWidget::depthToWidgetVector[depth].erase(iterator);
    
    UIWidget::depthToWidgetVector[newDepth].push_back(shared_from_this());
    
    depth = newDepth;
    
    for(auto&x : children)
    {
        shared_ptr<UIWidget> childrenLock = x.lock();
        
        if(childrenLock)
            updateDepth(newDepth+1);
    }
}

void UIWidget::addWidget(shared_ptr<UIWidget> widget)
{
    children.push_back(widget);
    widget->parent = shared_from_this();
    widget->updateDepth(depth+1);
    
    widget->setBounds(layout.getPositionFor(shared_from_this(), widget));
                                                                          
    updateBounds();
}

void UIWidget::updateBounds()
{
    float minX, minY, maxX, maxY;
    
    minX = bounds.x;
    minY = bounds.y;
    maxX = bounds.z;
    maxY = bounds.w;
    
    for (auto&x : children)
    {
        shared_ptr<UIWidget> childrenLock = x.lock();
        
        if(!childrenLock)
            continue;
        
        glm::vec4 childrenBound = childrenLock->getBounds();
        
        minX = min(minX,childrenBound.x);
        maxX = max(maxX,childrenBound.z);
        
        minY = min(minY,childrenBound.y);
        maxY = max(maxY,childrenBound.w);
        
    }
    
//    bounds = glm::vec4(minX,minY,maxX,maxY);
    setBounds(glm::vec4(minX,minY,minX+maxX,minY+maxY));
}

glm::vec4 UIWidget::getBounds()
{
    return bounds;
}