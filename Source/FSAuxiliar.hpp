//
//  FSAuxiliar.h
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-19.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#pragma once 

#include <iostream>
#include <vector>
#include <fstream>
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

/** FileSystem helper
    Collection of functions that manipulates files in the filesystem
 */

/** Get all files in a directory
 @param[in] fullPath The path of the directory
 @return List of files in the directory
 */
vector<path> getFilesInDirectory(string fullPath);
/** Calculates the CRC of a file
 @param[in] fullPath The path of the file
 @return the CRC of a file
 */
int getCRC(string fullPath);

