//
//  PointsTracker.h
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-06-16.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#ifndef __GUInity_MacOS__PointsTracker__
#define __GUInity_MacOS__PointsTracker__

#include "Module.hpp"
#include "ScriptComponent.hpp"
#include "Input.hpp"
#include "Transform.hpp"


class Material;
class Mesh;
class FontMesh;

class PointsTracker : public ScriptComponent
{
public:
    static int score;
    static weak_ptr<FontMesh> _fontMesh;
    
    virtual void awake() override;

    static void changeScore(int deltaScore);
    
    static void setGameOver();
    
    
};

#endif /* defined(__GUInity_MacOS__PointsTracker__) */
