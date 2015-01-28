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
#include "Font.hpp"
#include <ft2build.h>
#include FT_FREETYPE_H

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
    
//    createSerializationFile(asset,CommonData(name));
    
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


int writeImage(const char* filename, int width, int height, unsigned char *buffer, char* title)
{
	int code = 0;
	FILE *fp;
	png_structp png_ptr = NULL;
	png_infop info_ptr = NULL;
	png_bytep row = NULL;

	// Open file for writing (binary mode)
	fp = fopen(filename, "wb");
	if (fp == NULL) {
		fprintf(stderr, "Could not open file %s for writing\n", filename);
		code = 1;
		goto finalise;
	}
	// Initialize write structure
	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (png_ptr == NULL) {
		fprintf(stderr, "Could not allocate write struct\n");
		code = 1;
		goto finalise;
	}

	// Initialize info structure
	info_ptr = png_create_info_struct(png_ptr);
	if (info_ptr == NULL) {
		fprintf(stderr, "Could not allocate info struct\n");
		code = 1;
		goto finalise;
	}
	// Setup Exception handling
	if (setjmp(png_jmpbuf(png_ptr))) {
		fprintf(stderr, "Error during png creation\n");
		code = 1;
		goto finalise;
	}
	png_init_io(png_ptr, fp);

	// Write header (8 bit colour depth)
	png_set_IHDR(png_ptr, info_ptr, width, height,
		8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
		PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

	// Set title
	if (title != NULL) {
		png_text title_text;
		title_text.compression = PNG_TEXT_COMPRESSION_NONE;
		title_text.key = "Title";
		title_text.text = title;
		png_set_text(png_ptr, info_ptr, &title_text, 1);
	}

	png_write_info(png_ptr, info_ptr);

	// Allocate memory for one row (3 bytes per pixel - RGB)
	//row = (png_bytep)malloc(3 * width * sizeof(png_byte));
	row = (png_bytep)malloc(4 * width * sizeof(png_byte));

	// Write image data
	int x, y;
	for (y = 0; y<height; y++) {
		for (x = 0; x<width; x++) {
			//setRGB(&(row[x * 3]), buffer[y*width + x]);
			//cout << buffer[y*width + x] << endl;
			//row[x * 3] = buffer[y*width + x];
			float value = buffer[y*width + x] > 0 ? 255 : 0;
			float alpha = buffer[y*width + x];
			row[x * 4 + 0] = value;
			row[x * 4 + 1] = value;
			row[x * 4 + 2] = value;
			row[x * 4 + 3] = alpha;
			//row[x * 4] = buffer[y*width + x];
			//cout << x * 4 << endl;
			//cout << y*width + x<< endl;
			//cout << endl << endl;
			//row[x * 3 + 1] = 0;
		}
		png_write_row(png_ptr, row);
	}

	// End write
	png_write_end(png_ptr, NULL);
finalise:
	if (fp != NULL) fclose(fp);
	if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
	if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
	if (row != NULL) free(row);

	return code;
}


void getWidthHeightForAlphabet(FT_Face face, string alphabet, int& width, int& height)
{
	width = 0;
	for (int i = 0; i < alphabet.size(); i++)
	{
		FT_UInt  glyph_index;


		/* retrieve glyph index from character code */
		glyph_index = FT_Get_Char_Index(face, alphabet[i]);

		/* load glyph image into the slot (erase previous one) */
		FT_Error error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
		if (error)
		{
			cout << error << endl;
			continue;  /* ignore errors */
		}
		/* convert to an anti-aliased bitmap */
		error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

		width += face->glyph->bitmap.width + face->glyph->bitmap_left;
		height = max(height, face->glyph->bitmap.rows + face->glyph->bitmap_top);
	}
}

void addGlyphToBuffer(FT_Face& face, char letter, unsigned char* buffer, int bufferWidth, int bufferHeight, int xOffset, int yOffset, int& outGlyphWidth, int& outGlyphHeight)
{
	FT_UInt  glyph_index;


	/* retrieve glyph index from character code */
	glyph_index = FT_Get_Char_Index(face, letter);

	/* load glyph image into the slot (erase previous one) */
	FT_Error error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
	if (error)
	{
		//cout << error << endl;
		//continue;  /* ignore errors */
	}
	/* convert to an anti-aliased bitmap */
	error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

	//int offset = yOffset * bufferWidth + xOffset;
	//int width = face->glyph->bitmap.width;
	//int height = face->glyph->bitmap.rows;

	//outGlyphWidth = width + face->glyph->bitmap_left;
	//outGlyphHeight = height + face->glyph->bitmap_top;

	//int xI, yI;
	//for (yI = 0; yI<height; yI++) {
	////for (yI = height- 1; yI >= 0; yI--) {
	//	for (xI = 0; xI<width; xI++) {

	//		int bufferIndex = offset + (yI + face->glyph->bitmap_top)*bufferWidth + (xI + face->glyph->bitmap_left);
	//		int bitmapIndex = yI *width + xI;

	//		buffer[bufferIndex] = face->glyph->bitmap.buffer[bitmapIndex];
	//	}
	//}

	int offset = (bufferHeight - 1) * bufferWidth + xOffset;
	int width = face->glyph->bitmap.width;
	int height = face->glyph->bitmap.rows;

	outGlyphWidth = width + face->glyph->bitmap_left;
	outGlyphHeight = height + face->glyph->bitmap_top;

	int xI, yI;
	//for (yI = 0; yI<height; yI++) {
	for (yI = height - 1; yI >= 0; yI--) {
		for (xI = 0; xI<width; xI++) {

			int bufferIndex = offset - (height - yI)*bufferWidth + //y
				(xI + face->glyph->bitmap_left); //x
			int bitmapIndex = yI *width + xI;

			buffer[bufferIndex] = face->glyph->bitmap.buffer[bitmapIndex];
		}
	}


}


map<char, LetterFontUV> createFontTexture(FT_Face& face, string filename)
{
	map<char, LetterFontUV> charUVMap;

	int width, height;
	//string alphabet = "abcd";
	string alphabet = "bpabcdefghjklmnopqrstuvxyzw0123456789!?,./\[]{};':\"";
	getWidthHeightForAlphabet(face, alphabet, width, height);

	int xOffset, yOffset;
	xOffset = yOffset = 0;
	unsigned char* buffer = new unsigned char[width*height];
	for (int i = 0; i < width*height; i++)
	{
		buffer[i] = 0;
	}

	for (int i = 0; i < alphabet.size(); i++)
	{
		int outGlyphWidth, outGlyphHeight;
		addGlyphToBuffer(face, alphabet[i], buffer, width, height, xOffset, yOffset, outGlyphWidth, outGlyphHeight);
		charUVMap[alphabet[i]] = LetterFontUV(glm::vec2(xOffset / (float)width, 0), glm::vec2((xOffset + outGlyphWidth) / (float)width, 1), (float)outGlyphWidth / outGlyphHeight);
		xOffset += outGlyphWidth;
	}

	writeImage(filename.c_str(), width, height, buffer, "blabla");

	delete[] buffer;

	return charUVMap;
}

shared_ptr<Font> AssetDatabase::createFont(string filename, int fontSize)
{
	FT_Library  library;

	FT_Error error = FT_Init_FreeType(&library);
	if (error)
	{
		//	... an error occurred during library initialization ...
		cout << "Erro" << endl;
	}

	FT_Face     face;      /* handle to face object */
	error = FT_New_Face(library, filename.c_str(),
		0,
		&face);
	if (error == FT_Err_Unknown_File_Format)
	{

	}
	else if (error)
	{
	}
	else
	{
		cout << "Loaded OK" << endl;
	}

	//error = FT_Set_Char_Size(
	//	face,    /* handle to face object           */
	//	0,       /* char_width in 1/64th of points  */
	//	16 * 64,   /* char_height in 1/64th of points */
	//	300,     /* horizontal device resolution    */
	//	300);   /* vertical device resolution      */

	error = FT_Set_Pixel_Sizes(
		face,   /* handle to face object */
		0,      /* pixel_width           */
		fontSize);   /* pixel_height */

	// string alphabet = "abcdefghijklmnopqrstuvxyzw0123456789!?";

	string textureName = filename;
	textureName.append("texture.png");

	map<char, LetterFontUV> charUVMap = createFontTexture(face, textureName);

	shared_ptr<Texture> texture = createTexture(textureName);

	shared_ptr<Font> font = make_shared<Font>(texture,charUVMap,fontSize);
	assignCurrentID(font,filename);

	return font;

	//TODO how to cleanup freetype library?
}