//
//  PointsTracker.cpp
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-06-16.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "PointsTracker.hpp"
#include "FontMesh.hpp"
#include "Actor.hpp"


int PointsTracker::score = 0;
weak_ptr<FontMesh> PointsTracker::_fontMesh ;

 void PointsTracker::awake()
{
    _fontMesh = getActor()->GetComponent<FontMesh>();
    
    if(_fontMesh.lock())
        _fontMesh.lock()->setText(std::to_string(score));
}

void PointsTracker::changeScore(int deltaScore)
{
    score += deltaScore;
    if(_fontMesh.lock())
        _fontMesh.lock()->setText(std::to_string(score));
}

void PointsTracker::setGameOver()
{
    if(_fontMesh.lock())
        _fontMesh.lock()->setText("game over");
}