#!/bin/sh
install_name_tool /Users/guilherme_cunha/Dev/GITHUB/GUInity/GUInity_MacOS/DerivedData/GUInity_MacOS/Build/Products/Debug/GUInity_Editor -change   /usr/local/lib/libfreetype.6.dylib @executable_path/libfreetype.6.dylib
install_name_tool /Users/guilherme_cunha/Dev/GITHUB/GUInity/GUInity_MacOS/DerivedData/GUInity_MacOS/Build/Products/Debug/GUInity_Editor -change   libboost_system.dylib @executable_path/libboost_system.dylib
install_name_tool /Users/guilherme_cunha/Dev/GITHUB/GUInity/GUInity_MacOS/DerivedData/GUInity_MacOS/Build/Products/Debug/GUInity_Editor -change   libboost_filesystem.dylib @executable_path/libboost_filesystem.dylib
install_name_tool /Users/guilherme_cunha/Dev/GITHUB/GUInity/GUInity_MacOS/DerivedData/GUInity_MacOS/Build/Products/Debug/GUInity_Editor -change   libboost_serialization.dylib @executable_path/libboost_serialization.dylib
install_name_tool /Users/guilherme_cunha/Dev/GITHUB/GUInity/GUInity_MacOS/DerivedData/GUInity_MacOS/Build/Products/Debug/GUInity_Editor -change   /Users/guilherme_cunha/Dev/libpng-1.6.16/build/lib/libpng16.16.dylib @executable_path/libpng16.16.dylib
install_name_tool /Users/guilherme_cunha/Dev/GITHUB/GUInity/GUInity_MacOS/DerivedData/GUInity_MacOS/Build/Products/Debug/GUInity_Editor -change   @rpath/libfmod.dylib @executable_path/libfmod.dylib
install_name_tool /Users/guilherme_cunha/Dev/GITHUB/GUInity/GUInity_MacOS/DerivedData/GUInity_MacOS/Build/Products/Debug/GUInity_Editor -change   libboost_serialization.dylib @executable_path/libboost_serialization.dylib
install_name_tool /Users/guilherme_cunha/Dev/GITHUB/GUInity/GUInity_MacOS/DerivedData/GUInity_MacOS/Build/Products/Debug/GUInity_Editor -change   /usr/lib/libGLEW.1.11.0.dylib @executable_path/libGLEW.1.11.0.dylib
install_name_tool /Users/guilherme_cunha/Dev/GITHUB/GUInity/GUInity_MacOS/DerivedData/GUInity_MacOS/Build/Products/Debug/GUInity_Editor -change   /usr/lib/libGLEWmx.1.11.0.dylib @executable_path/libGLEWmx.1.11.0.dylib



