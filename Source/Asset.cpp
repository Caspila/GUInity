//
//  Asset.cpp
//  GUInity Project - A 3D component-based one-man game engine
//
//  Created by Guilherme Cunha on 2014-12-30.
//  Copyright (c) 2014 Guilherme Cunha. All rights reserved.
//

#include <stdio.h>

#include "Asset.hpp"
#include "Mesh.hpp"


/** assetID Setter
 @param[in] the unique number that identifies the Asset
 */
void Asset::setAssetID(unsigned int assetID)
{
    this->assetID = assetID;
}

/** assetID Getter
 @return the unique number that identifies the Asset
 */

unsigned int Asset::getAssetID() const
{
    return assetID;
}

/** filePath Setter
 @param[in] filePath  the path of the Asset in the filesystem
 */
void Asset::setPath(string filePath)
{
    this->filePath = filePath;
    
}

/** filePath Getter
 @return the path of the file in the filesystem
 */
string Asset::getPath() const
{
    return filePath;
}

/** name Setter
 @param[in] name of the asset (Includes extension)
 */
void Asset::setName(string name)
{
    this->name = name;
    setPath(CommonData(name));
}
/** name Getter
 @return name of the asset (Includes extension)
 */
string Asset::getName() const
{
    return name;
}
/** CRC Setter
 @param[in] the crc of the file
 https://en.wikipedia.org/wiki/Cyclic_redundancy_check
 */
void Asset::setCRC(int crc)
{
    this->crc = crc;
}
/** CRC Getter
 @return the crc of the file
 https://en.wikipedia.org/wiki/Cyclic_redundancy_check
 */
int Asset::setCRC()
{
    return crc;
}
