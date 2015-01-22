//
//  File.cpp
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2014-12-30.
//  Copyright (c) 2014 Guilherme Cunha. All rights reserved.
//

#include "AssetDatabase.hpp"
#include "Asset.hpp"
//#include "Mesh.hpp"
#include "Material.hpp"
#include "Shader.hpp"
#include "Texture.hpp"
#include <png.h>
#include <boost/filesystem.hpp>
#include "FSAuxiliar.hpp"
#include <boost/archive/text_oarchive.hpp>
#include "Module.hpp"
#include "Serialization2.hpp"

unsigned int AssetDatabase::currentID = 0;
MeshImporter AssetDatabase::meshImporter;
std::map<unsigned int,shared_ptr<Asset>> AssetDatabase::idToAsset;
std::map<string,shared_ptr<Asset>> AssetDatabase::nameToAsset;



//int AssetDatabase::getCRC(string fullPath)
//{
//    using namespace boost::filesystem;
//    
//    path p(fullPath);
//    if(exists(p))
//    {
//        if(is_regular_file(p))
//        {
//            ifstream file(fullPath,ios::in | ios::binary);
//            
//            //ifstream::pos_type fileSize = file.tellg();
//            int fileSize = file_size(p);
//            char* fileContents = new char[fileSize];
//            
//            file.seekg(0, ios::beg);
//            if(!file.read(fileContents, fileSize))
//            {
//                cout << "fail to read" << endl;
//            }
//            
////            boost::crc_basic<16> crc_ccitt1(
//                boost::crc_basic<32>  crc_ccitt1( 0x1021, 0xFFFF, 0, false, false );
//                crc_ccitt1.process_bytes( fileContents, fileSize );
//            
//            int checkSum = crc_ccitt1.checksum();
//            cout << checkSum << endl;
//            return checkSum;
//        }
//            
//    }
//    cerr << "Error when trying to get CRC for file: "<< fullPath << endl;
//    return -1;
//}

void AssetDatabase::loadFile(string fullPath)
{
    cout << "Loading desc file: " << fullPath << endl;
    {
        std::ifstream ifs(fullPath,std::fstream::binary | std::fstream::in);
//        if(ifs.good())
//        {
//        //    ifs.seekg (0, ifs.end);
//            cout <<         ifs.tellg() << endl;
//        }


        
        boost::archive::binary_iarchive ia(ifs);
        
        shared_ptr<Asset> asset;
        ia & asset;
    }
}

void createSerializationFile(shared_ptr<Asset> asset,string filename)
{
        std::ofstream ofs(filename.append(".desc"),std::fstream::binary | std::fstream::out);
    {

        
        boost::archive::binary_oarchive oa(ofs);
        
        oa & asset;
    }
    ofs.close();
}

void AssetDatabase::loadAllMetaFiles()
{
    vector<path> files = getFilesInDirectory(CommonData(""));
    
    for(auto& file : files)
    {
        
        string extension = file.extension().string();
        string filename = file.filename().string();
        
        if(extension == ".desc")
        {
            loadFile(filename);
        }
     
        
    }
 
}
void AssetDatabase::init()
{
    meshImporter.init();
    
//   loadAllMetaFiles();
 
    cout << idToAsset.size() << endl;
}

void AssetDatabase::shutdown()
{
    meshImporter.shutdown();
}

shared_ptr<Asset> AssetDatabase::getAsset(string filename)
{
    map<string,shared_ptr<Asset>>::iterator it;
    it = nameToAsset.find(filename);
    if(it!=nameToAsset.end())
        return nameToAsset[filename];
    

    
    return nullptr;
}



template <typename T>
void AssetDatabase::assignCurrentID(T asset, string name)
{
    asset->setAssetID(currentID);
    
    idToAsset[currentID] = asset;
    
    asset->setName(name);

    asset->setCRC(getCRC(CommonData(name)));
    
    nameToAsset[name] = asset;
    
    createSerializationFile(asset,CommonData(name));
    
    currentID++;
}

template <typename T>
void AssetDatabase::assignCurrentID(T asset)
{
    asset->setAssetID(currentID);
    
    idToAsset[currentID] = asset;
    
    string name = std::to_string(currentID);
    asset->setName(name);
    
    nameToAsset[name] = asset;
    
    currentID++;
}

//template <typename T>
//void AssetDatabase::assignName(T asset, string name)
//{
//    asset->setName(name);
//
//    nameToAsset[name] = asset;
//}


shared_ptr<Shader> AssetDatabase::createShader(string filename, string vsFilename, string fsFilename)
{
 
    shared_ptr<Shader> shader = make_shared<Shader>(vsFilename,fsFilename);
    assignCurrentID(shader,filename);
//    assignName(shader,filename);
    
    return shader;
}

shared_ptr<Material> AssetDatabase::createMaterial(string filename, shared_ptr<Shader> shader)
{
    shared_ptr<Material> material = make_shared<Material>(shader);
    assignCurrentID(material,filename);
//    assignName(material,filename);
    
    return material;
}

 shared_ptr<Mesh> AssetDatabase::createMeshFromFBX(string filename)
{
    shared_ptr<Mesh> mesh = meshImporter.importFbxMesh(filename);
    assignCurrentID(mesh,filename);
//    assignName(mesh,filename);
    

    
    return mesh;
}
 shared_ptr<Mesh> AssetDatabase::createMeshFromOBJ(string filename)
{
    shared_ptr<Mesh> mesh = meshImporter.importObjMesh(filename);
    assignCurrentID(mesh,filename);
//    assignName(mesh,filename);

    return mesh;
}
 shared_ptr<Mesh> AssetDatabase::createMesh(vector<MeshVertex> vertex, vector<unsigned short> triangles)
{
    shared_ptr<Mesh> mesh = make_shared<Mesh>(vertex,triangles);
    assignCurrentID(mesh);
    
    return mesh;
}

shared_ptr<Mesh> AssetDatabase::createMesh(vector<glm::vec3> vertices,vector<int> usedIndex,vector<int> usedTris)
{
    shared_ptr<Mesh> mesh = make_shared<Mesh>(vertices,usedIndex,usedTris);
    assignCurrentID(mesh);
    
    return mesh;
}


int myX, myY;

int width, height;
png_byte color_type;
png_byte bit_depth;

png_structp png_ptr;
png_infop info_ptr;
int number_of_passes;
png_bytep * row_pointers;

void abort_(const char * s, ...)
{
    va_list args;
    va_start(args, s);
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}



//void* read_png_file(const char* file_name)
//{
//    char header[8];    // 8 is the maximum size that can be checked
//    
//    /* open file and test for it being a png */
//    FILE *fp = fopen(file_name, "rb");
//    if (!fp)
//        abort_("[read_png_file] File %s could not be opened for reading", file_name);
//    fread(header, 1, 8, fp);
//    //    if (png_sig_cmp(header, 0, 8))
//    //        abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);
//    
//    
//    /* initialize stuff */
//    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//    
//    if (!png_ptr)
//        abort_("[read_png_file] png_create_read_struct failed");
//    
//    info_ptr = png_create_info_struct(png_ptr);
//    if (!info_ptr)
//        abort_("[read_png_file] png_create_info_struct failed");
//    
//    if (setjmp(png_jmpbuf(png_ptr)))
//        abort_("[read_png_file] Error during init_io");
//    
//    png_init_io(png_ptr, fp);
//    png_set_sig_bytes(png_ptr, 8);
//    
//    png_read_info(png_ptr, info_ptr);
//    
//    width = png_get_image_width(png_ptr, info_ptr);
//    height = png_get_image_height(png_ptr, info_ptr);
//    color_type = png_get_color_type(png_ptr, info_ptr);
//    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
//    
//    number_of_passes = png_set_interlace_handling(png_ptr);
//    png_read_update_info(png_ptr, info_ptr);
//    
//    
//    /* read file */
//    if (setjmp(png_jmpbuf(png_ptr)))
//        abort_("[read_png_file] Error during read_image");
//    
//    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
//    for (myY=0; myY<height; myY++)
//        row_pointers[myY] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
//    
//    png_read_image(png_ptr, row_pointers);
//    
//    fclose(fp);
//    
//    return image_data;
//}

//http://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures#A_simple_libpng_example
void* loadTexture(const string filename, int &width, int &height)
{
    //header for testing if it is a png
    png_byte header[8];
    
    //open file as binary
    FILE *fp = fopen(filename.c_str(), "rb");
    if (!fp) {
//        return TEXTURE_LOAD_ERROR;
    }
    
    //read the header
    fread(header, 1, 8, fp);
    
    //test if png
    int is_png = !png_sig_cmp(header, 0, 8);
    if (!is_png) {
        fclose(fp);
//        return TEXTURE_LOAD_ERROR;
    }
    
    //create png struct
    png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL,
                                                 NULL, NULL);
    if (!png_ptr) {
        fclose(fp);
//        return (TEXTURE_LOAD_ERROR);
    }
    
    //create png info struct
    png_infop info_ptr = png_create_info_struct(png_ptr);
    if (!info_ptr) {
        png_destroy_read_struct(&png_ptr, (png_infopp) NULL, (png_infopp) NULL);
        fclose(fp);
//        return (TEXTURE_LOAD_ERROR);
    }
    
    //create png info struct
    png_infop end_info = png_create_info_struct(png_ptr);
    if (!end_info) {
        png_destroy_read_struct(&png_ptr, &info_ptr, (png_infopp) NULL);
        fclose(fp);
//        return (TEXTURE_LOAD_ERROR);
    }
    
    //png error stuff, not sure libpng man suggests this.
    if (setjmp(png_jmpbuf(png_ptr))) {
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
//        return (TEXTURE_LOAD_ERROR);
    }
    
    //init png reading
    png_init_io(png_ptr, fp);
    
    //let libpng know you already read the first 8 bytes
    png_set_sig_bytes(png_ptr, 8);
    
    // read all the info up to the image data
    png_read_info(png_ptr, info_ptr);
    
    //variables to pass to get info
    int bit_depth, color_type;
    png_uint_32 twidth, theight;
    
    // get info about png
    png_get_IHDR(png_ptr, info_ptr, &twidth, &theight, &bit_depth, &color_type,
                 NULL, NULL, NULL);
    
    //update width and height based on png info
    width = twidth;
    height = theight;
    
    // Update the png info struct.
    png_read_update_info(png_ptr, info_ptr);
    
    // Row size in bytes.
    int rowbytes = png_get_rowbytes(png_ptr, info_ptr);
    
    // Allocate the image_data as a big block, to be given to opengl
    png_byte *image_data = new png_byte[rowbytes * height];
    if (!image_data) {
        //clean up memory and close stuff
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        fclose(fp);
//        return TEXTURE_LOAD_ERROR;
    }
    
    //row_pointers is for pointing to image_data for reading the png with libpng
    png_bytep *row_pointers = new png_bytep[height];
    if (!row_pointers) {
        //clean up memory and close stuff
        png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
        delete[] image_data;
        fclose(fp);
//        return TEXTURE_LOAD_ERROR;
    }
    // set the individual row_pointers to point at the correct offsets of image_data
    for (int i = 0; i < height; ++i)
        row_pointers[height - 1 - i] = image_data + i * rowbytes;
    
    //read the png into image_data through row_pointers
    png_read_image(png_ptr, row_pointers);
    
    //Now generate the OpenGL texture object
//    GLuint texture;
//    glGenTextures(1, &texture);
//    glBindTexture(GL_TEXTURE_2D, texture);
//    glTexImage2D(GL_TEXTURE_2D,0, GL_RGBA, width, height, 0,
//                 GL_RGB, GL_UNSIGNED_BYTE, (GLvoid*) image_data);
//    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
//    
//    //clean up memory and close stuff
    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
//    delete[] image_data;
    delete[] row_pointers;
    fclose(fp);
    
    return image_data;
}


shared_ptr<Texture> AssetDatabase::createTexture(string filename)
{
    shared_ptr<Texture> texture = make_shared<Texture>();
    assignCurrentID(texture);
    
    //texture->data = read_png_file(filename.c_str());
    int width, height;
    width = height = 0;
    
    texture->data = loadTexture(filename,width,height);
    texture->width = width;
    texture->height = height;
    
    texture->init();
    
    return texture;
}
