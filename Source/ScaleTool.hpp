//
//  ScaleTool.h
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-22.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __opengl_testing_mag__ScaleTool__
#define __opengl_testing_mag__ScaleTool__

#include "ScriptComponent.hpp"
#include "ScaleHandle.hpp"

class ScaleTool : public ScriptComponent
{
	
    
public:
	
	ScaleTool();
	~ScaleTool();
    
//	MoveMode moveMode;
    
	virtual void awake() override;
    virtual void tick(float deltaSeconds) override;
    
	weak_ptr<ScaleHandle> forward, up, right;
};



#endif /* defined(__opengl_testing_mag__ScaleTool__) */
