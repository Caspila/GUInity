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

vector<path> getFilesInDirectory(string fullPath);
int getCRC(string fullPath);

