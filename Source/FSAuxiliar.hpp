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

/** FileSystem helper */

/** Returns all files in a directory */
vector<path> getFilesInDirectory(string fullPath);
/** Returns the checksum of a files */
int getCRC(string fullPath);

