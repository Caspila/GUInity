//
//  Asset.h
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2014-12-30.
//  Copyright (c) 2014 Guilherme Cunha. All rights reserved.
//

#pragma once

#include <iostream>
#include <string>
#include "Module.hpp"

#include <boost/serialization/serialization.hpp>
#include <boost/serialization/export.hpp>


using namespace std;

class Asset
{
public:
    
    Asset() {};
//    unsigned int assetID, string fullPath)
//    {
//        this->assetID = assetID;
//        this->fullPath = fullPath;
//    }
    virtual ~Asset(){}
    
    unsigned int assetID;
    string fullPath;
        string name;
    int crc; //Checksum
    
    void setAssetID(unsigned int newAssetID) { this->assetID = newAssetID;}
    
    unsigned int getAssetID() { return assetID;}
    string getPath() { return fullPath;}
    void setPath(string newPath) { fullPath = newPath;}
    void setName(string name) { this->name = name; setPath(CommonData(name));}
    void setCRC(int crc) {this->crc = crc;}
    
    
    
    
    
};
