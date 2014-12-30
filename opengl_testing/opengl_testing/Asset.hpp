//
//  Asset.h
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2014-12-30.
//  Copyright (c) 2014 Guilherme Cunha. All rights reserved.
//

#pragma once

#include <iostream>

class Asset
{
public:
    unsigned int assetID;
    
    void setAssetID(unsigned int newAssetID) { assetID = newAssetID;}
    unsigned int getAssetID() { return assetID;}
};

