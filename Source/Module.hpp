#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include "StaticCounter.hpp"
#include "PointerHolder.hpp"

#ifndef DATA_PATH
#ifdef _WIN32 // note the underscore: without it, it's not msdn official!
// Windows (x64 and x86)

#define DATA_PATH "../data/"

#elif __unix__ // all unices, not all compilers
// Unix
#elif __linux__
// linux
#elif __APPLE__

//#define DATA_PATH "../../../../../../data/"
#define DATA_PATH "/Users/guilherme_cunha/Dev/GITHUB/GUInity/data/"
// Mac OS, not sure if this is covered by __posix__ and/or __unix__ though...
#endif
#endif


using namespace std;


string CommonData(string file);
