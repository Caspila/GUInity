//
//  Asset.h
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2014-12-30.
//  Copyright (c) 2014 Guilherme Cunha. All rights reserved.
//

#pragma once

//#include <iostream>
#include <string>
#include "Module.hpp"

//#include <boost/serialization/serialization.hpp>
//#include <boost/serialization/export.hpp>


using namespace std;

/** Class Asset. This class represents assets in game. This can vary from textures to meshes and audio files. 
	Virtually, everything that can be serialized to a file is an Asset. Currently, these are the assets:
	-Texture
	-Font
	-Audio
	-Mesh

	The idea is to simulate the Assets folder in Unity. Therefore, assets place in a folder should be loaded automatically. 
	Each Asset has a CRC (checksum) to check if the file has changed or not.
*/
class Asset
{

private:
	/** assetID is the "Primary Key" of the asset. Since they're all stored in the AssetDatabase */
	unsigned int assetID;
	/** Full path of the file */
	string fullPath;
	/** Name of the file */
	string name;
	/** Checksum of the file */
	int crc; //Checksum

public:
    
	/** Default Constructor */
    Asset() {};
	/** Default Destructor - Virtual because it's a parent class */
    virtual ~Asset(){}
    

	/** assetID setter */
    void setAssetID(unsigned int newAssetID) { this->assetID = newAssetID;}
	/** assetID getter */
    unsigned int getAssetID() const { return assetID;}

	/** Full path getter */
    string getPath() { return fullPath;}
	/** Full path setter */
	void setPath(string newPath) { fullPath = newPath;}
	/** name setter*/
    void setName(string name) { this->name = name; setPath(CommonData(name));}
	/** name getter*/
	string getName() { return name;}
	/** CRC setter */
    void setCRC(int crc) {this->crc = crc;}
	/** CRC getter */
	int setCRC() { return crc; }
    
    
    
};
