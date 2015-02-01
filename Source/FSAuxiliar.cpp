//
//  FSAuxiliar.cpp
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-19.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "FSAuxiliar.hpp"
#include <boost/crc.hpp>

/** Returns all files in a directory */
vector<path> getFilesInDirectory(string fullPath)
{
    path p(fullPath);
    
    vector<path> vec;
    if(is_directory(p))
    {
        copy(directory_iterator(p), directory_iterator(), back_inserter(vec));
    }
    
    return vec;
}

/** Returns the checksum of a files */
int getCRC(string fullPath)
{
    using namespace boost::filesystem;
    
    path p(fullPath);
    if(exists(p))
    {
        if(is_regular_file(p))
        {
            ifstream file(fullPath,ios::in | ios::binary);
            
            //ifstream::pos_type fileSize = file.tellg();
            int fileSize = file_size(p);
            char* fileContents = new char[fileSize];
            
            file.seekg(0, ios::beg);
            if(!file.read(fileContents, fileSize))
            {
                cout << "fail to read" << endl;
            }
            
            //            boost::crc_basic<16> crc_ccitt1(
            boost::crc_basic<32>  crc_ccitt1( 0x1021, 0xFFFF, 0, false, false );
            crc_ccitt1.process_bytes( fileContents, fileSize );
            
            int checkSum = crc_ccitt1.checksum();
            //cout << checkSum << endl;
            return checkSum;
        }
        
    }
    cerr << "Error when trying to get CRC for file: "<< fullPath << endl;
    return -1;
}