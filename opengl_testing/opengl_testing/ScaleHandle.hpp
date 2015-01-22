//
//  ScaleHandle.h
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-22.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __opengl_testing_mag__ScaleHandle__
#define __opengl_testing_mag__ScaleHandle__

#include <glm/common.hpp>
#include "ScriptComponent.hpp"
#include "Enums.hpp"


class ScaleHandle : public ScriptComponent
{
    
    
public:
    
	ScaleHandle();
	~ScaleHandle();
    
	TransformAxis axis;
	
	void setAxis(TransformAxis axis);
    
	virtual void tick(float deltaSeconds) override;
    
private:
	bool isPressed;
};



#endif /* defined(__opengl_testing_mag__ScaleHandle__) */
