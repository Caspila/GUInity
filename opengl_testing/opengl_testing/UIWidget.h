//
//  UIWidget.h
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-12.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __opengl_testing_mag__UIWidget__
#define __opengl_testing_mag__UIWidget__

#include <iostream>
#include <glm/glm.hpp>
#include "Mesh.hpp"
#include "Module.hpp"
#include "UILayout.h"
#include <map>

enum UILayoutType { none, vertical, horizontal };



class UIWidget : public std::enable_shared_from_this<UIWidget>
{
public:
    UIWidget();
    virtual ~UIWidget();
    glm::vec4 bounds;
    glm::vec3 position;
    glm::vec3 scale;
    
    glm::vec4 color;
    
    int depth;
    
    glm::mat4 getModelMatrix();
    void setBounds(float x,float y, float width, float height);

    weak_ptr<UIWidget> parent;
    vector<weak_ptr<UIWidget>> children;
    
    void addWidget(shared_ptr<UIWidget> widget);
    
    void updateDepth(int newDepth);
    
    void setBounds(glm::vec4 bounds);
    void updateBounds();
    glm::vec4 getBounds();
    void updatePositionAndScale();
    
    UILayout layout;
    
    
    shared_ptr<Mesh> mesh;
    
    static map<int,vector<shared_ptr<UIWidget>>> depthToWidgetVector;
    
    std::function<void()> clickFunction;
    std::function<void()> hoverOnFunction;
    std::function<void()> hoverOffFunction;
    
};

#endif /* defined(__opengl_testing_mag__UIWidget__) */
