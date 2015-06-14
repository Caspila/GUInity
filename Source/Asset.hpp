//
//  Asset.hpp
//  GUInity Project - A 3D component-based one-man game engine
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
 -Sound
 -Mesh
 -Material
 -PhysicsMaterial
 -Shader
 
 Every Asset placed in the data folder is automatically loaded in the game and can be accessed using the AssetDatabase.
 Each Asset has a CRC (checksum) to check if the file has changed or not.
 
 
 */
class Asset
{
    
private:
	/** assetID is the "Primary Key" of the asset. Since they're all stored in the AssetDatabase */
	unsigned int assetID;
	/** Full path of the file */
	string filePath;
	/** Name of the file */
	string name;
	/** Checksum of the file */
	int crc;
    
public:
    
	/** Default Constructor */
    Asset() {};
	/** Default Destructor */
    virtual ~Asset(){}
    
    
    /** assetID Setter
     @param[in] the unique number that identifies the Asset
     */
    void setAssetID(unsigned int assetID);
    
    /** assetID Getter
     @return the unique number that identifies the Asset
     */
    
    unsigned int getAssetID() const;
    
    /** filePath Setter
     @param[in] filePath  the path of the Asset in the filesystem
     */
    void setPath(string filePath);
    
    /** filePath Getter
     @return the path of the file in the filesystem
     */
    string getPath() const;
    
    /** name Setter
     @param[in] name of the asset (Includes extension)
     */
    void setName(string name);
    /** name Getter
     @return name of the asset (Includes extension)
     */
    string getName() const;
    
    /** CRC Setter
     @param[in] the crc of the file
     https://en.wikipedia.org/wiki/Cyclic_redundancy_check
     */
    void setCRC(int crc);
    /** CRC Getter
     @return the crc of the file
     https://en.wikipedia.org/wiki/Cyclic_redundancy_check
     */
    int setCRC();
    
    
    
};
