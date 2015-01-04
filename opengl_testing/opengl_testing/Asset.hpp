//
//  Asset.h
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2014-12-30.
//  Copyright (c) 2014 Guilherme Cunha. All rights reserved.
//

#pragma once

#include <iostream>


#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>


class Asset
{
public:
    Asset(){}
    virtual ~Asset(){}
    
    unsigned int assetID;
    
    void setAssetID(unsigned int newAssetID) { assetID = newAssetID;}
    unsigned int getAssetID() { return assetID;}
    
    
    
    
};
