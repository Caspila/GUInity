//
//  UIButton.cpp
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-12.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "UIButton.hpp"


void UIButton::defaultHoverOn()
{
    color = hoverColor;
}

void UIButton::defaultHoverOff()
{
    color = defaultColor;
}


UIButton::UIButton()
{

    hoverOnFunction = std::bind(&UIButton::defaultHoverOn,this);
    hoverOffFunction = std::bind(&UIButton::defaultHoverOff,this);
    
    hoverColor = glm::vec4(0.2,0.2,0.2,1);
    pressColor = glm::vec4(0.4,0.4,0.4,1);

    defaultColor = color;
}

UIButton::~UIButton()
{
    
}