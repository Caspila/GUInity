//
//  File.cpp
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2014-12-30.
//  Copyright (c) 2014 Guilherme Cunha. All rights reserved.
//

#include "AssetDatabase.hpp"
#include "Asset.hpp"
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
#include "Sound.hpp"
#include <freetype/ftglyph.h>
#include "PhysicsMaterial.hpp"

/** currentID, "Primary Key"*/
unsigned int AssetDatabase::currentID = 0;
/** Class that knows how to import .obj and .fbx */
MeshImporter AssetDatabase::meshImporter;
/** Map that translates IDs to Asset */
std::map<unsigned int,shared_ptr<Asset>> AssetDatabase::idToAsset;
/** Map that translates Name to Asset */
std::map<string,shared_ptr<Asset>> AssetDatabase::nameToAsset;


/** init. Function that initializes the class. */
void AssetDatabase::init()
{
	/** Initialize the Mesh Importer */
	meshImporter.init();
}

void AssetDatabase::shutdown()
{
	/** Shutdown the Mesh Importer */
	meshImporter.shutdown();
}


/** createSerializationFile. Create a meta-file for an asset (Serialize an asset) */
void AssetDatabase::createSerializationFile(shared_ptr<Asset> asset, string filename)
{
    std::ofstream ofs(filename.append(".desc"),std::fstream::binary | std::fstream::out);
    {

        
        boost::archive::binary_oarchive oa(ofs);
        
        oa & asset;
    }
    ofs.close();
}


/** readSerialiationFile. Loads an asset from a description file. */
void AssetDatabase::readSerialiationFile(string fullPath)
{
	cout << "Loading desc file: " << fullPath << endl;
	{
		std::ifstream ifs(fullPath, std::fstream::binary | std::fstream::in);

		boost::archive::binary_iarchive ia(ifs);

		shared_ptr<Asset> asset;
		ia & asset;
	}
}

/** Once serialization is done and working, the AssetDatabase should not reload all files
everytime. It should load only the Asset Description (.meta//.desc) file and check if it's up to date.
This function loads all the meta-files existing in the CommonData folder*/

void AssetDatabase::loadAllMetaFiles()
{
    vector<path> files = getFilesInDirectory(CommonData(""));
    
    for(auto& file : files)
    {
        
        string extension = file.extension().string();
        string filename = file.filename().string();
        
        if(extension == ".desc")
        {
			readSerialiationFile(filename);
        }
     
        
    }
 
}

/** Search on the database for the asset with assetID==Asset.assetID.*/
shared_ptr<Asset> AssetDatabase::getAsset(unsigned int assetID)
{
	map<unsigned int, shared_ptr<Asset>>::iterator it;
	it = idToAsset.find(assetID);
	if (it != idToAsset.end())
		return idToAsset[assetID];

	return nullptr;
}


/** assignCurrentID. Increments the primary key and add the Asset to the maps with the proper name. */
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

/** assignCurrentID. Increments the primary key and add the Asset to the maps. Uses the assetID as the name */
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


/** tryLoadAsset. Delegates the file to the appropriate loader. */
shared_ptr<Asset> AssetDatabase::tryLoadAsset(string file, string extension)
{
	if (extension.compare(".fbx") == 0)
        return AssetDatabase::createMeshFromFBX(file);
//		cout << "Load fbx: " << file << endl;
	else if (extension.compare(".png") == 0)
        return AssetDatabase::createTexture(file);
//		cout << "Should automatically load png: " << file << endl;
	else if (extension.compare(".obj") == 0)
        return AssetDatabase::createMeshFromOBJ(file);
//		cout << "Load obj: " << file << endl;
	else if (extension.compare(".mp3") == 0)
		cout << "Should automatically load mp3: " << file << endl;
	else if (extension.compare(".ttf") == 0)
		cout << "Should automatically load ttf: " << file << endl;

	return nullptr;

}


/** Create shader from a vertex shader and a fragment shader. Name is the name of the newly created shader */
shared_ptr<Shader> AssetDatabase::createShader(string filename, string vsFilename, string fsFilename)
{
 
    shared_ptr<Shader> shader = make_shared<Shader>(vsFilename,fsFilename);
    assignCurrentID(shader,filename);
    return shader;
}

/** Create material from a shader. Several materials can have the same shader but different properties, such as textures and colors. */
shared_ptr<Material> AssetDatabase::createMaterial(string filename, shared_ptr<Shader> shader)
{
    shared_ptr<Material> material = make_shared<Material>(shader);
    assignCurrentID(material,filename);
    return material;
}
shared_ptr<PhysicsMaterial> AssetDatabase::createPhysicsMaterial(string name, float friction, float dynamicFriction, float restitution)
{
	shared_ptr<PhysicsMaterial> physicsMaterial = make_shared<PhysicsMaterial>(friction,dynamicFriction,restitution);
	assignCurrentID(physicsMaterial, name);
	return physicsMaterial;
}

/** Create mesh from .fbx files*/
 shared_ptr<Mesh> AssetDatabase::createMeshFromFBX(string filename)
{
    shared_ptr<Mesh> mesh = meshImporter.importFbxMesh(CommonData(filename));
    assignCurrentID(mesh,filename);
    return mesh;
}

 /** Create mesh from .obj files*/
 shared_ptr<Mesh> AssetDatabase::createMeshFromOBJ(string filename)
{
    shared_ptr<Mesh> mesh = meshImporter.importObjMesh(CommonData(filename));
    assignCurrentID(mesh,filename);
    return mesh;
}

 /** Create mesh from list of vertice data and triangles*/
 shared_ptr<Mesh> AssetDatabase::createMesh(vector<MeshVertex> vertex, vector<unsigned short> triangles)
{
    shared_ptr<Mesh> mesh = make_shared<Mesh>(vertex,triangles);
    assignCurrentID(mesh);
    return mesh;
}

/** Create Sound asset from file. */
shared_ptr<Sound> AssetDatabase::createSound(string filename)
{
	shared_ptr<Sound> sound = make_shared<Sound>(filename);
	assignCurrentID(sound, filename);

	return sound;
}


/** Create Texture from file. Only supported file is .png in the moment.*/
shared_ptr<Texture> AssetDatabase::createTexture(string filename)
{

	int width = 0;
	int height = 0;
	void *buffer = loadTexture(CommonData(filename), width, height);

	shared_ptr<Texture> texture = make_shared<Texture>(buffer,width,height);
	assignCurrentID(texture, filename);

	return texture;
}

shared_ptr<Font> AssetDatabase::createFont(string filename, int fontSize)
{
    string commonDataFilename = CommonData(filename);

    
	FT_Library  library;

	FT_Error error = FT_Init_FreeType(&library);
	if (error)
	{
		//	... an error occurred during library initialization ...
		cout << "Error" << endl;
	}

	FT_Face     face;      /* handle to face object */
	error = FT_New_Face(library, commonDataFilename.c_str(),
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

	error = FT_Set_Pixel_Sizes(
		face,   /* handle to face object */
		0,      /* pixel_width           */
		fontSize);   /* pixel_height */

	string textureName = filename;
	textureName.append("texture.png");

	map<char, LetterFontUV> charUVMap = createFontTexture(face, textureName);

	shared_ptr<Texture> texture = createTexture(textureName);

	shared_ptr<Font> font = make_shared<Font>(texture, charUVMap, fontSize);
	assignCurrentID(font, filename);

    
	return font;

	//TODO how to cleanup freetype library?
}

//int myX, myY;
//
//int width, height;
//png_byte color_type;
//png_byte bit_depth;
//
//png_structp png_ptr;
//png_infop info_ptr;
//int number_of_passes;
//png_bytep * row_pointers;

void abort_(const char * s, ...)
{
    va_list args;
    va_start(args, s);
    vfprintf(stderr, s, args);
    fprintf(stderr, "\n");
    va_end(args);
    abort();
}


//http://en.wikibooks.org/wiki/OpenGL_Programming/Intermediate/Textures#A_simple_libpng_example
void* AssetDatabase::loadTexture(const string filename, int &width, int &height)
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
    

    png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
//    delete[] image_data;
    delete[] row_pointers;
    fclose(fp);
    
	
    return image_data;
}


int AssetDatabase::writeImage(const char* filename, int width, int height, unsigned char *buffer, char* title)
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


void AssetDatabase::getWidthHeightForAlphabet(FT_Face face, string alphabet, int& width, int& height, int& yOrigin)
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

		FT_Glyph glyph;
		FT_Get_Glyph(face->glyph, &glyph);
	

		/* convert to an anti-aliased bitmap */
		error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

		int charWidth = face->glyph->bitmap.width + abs(face->glyph->bitmap_left);
		if (charWidth == 0)
			charWidth = face->glyph->advance.x / 64;

		width += charWidth;

		//height = max(height, face->glyph->bitmap.rows + face->glyph->bitmap_top);
		int yPos = (face->glyph->bitmap.rows - face->glyph->bitmap_top);
		yOrigin = max(yOrigin, yPos);

		int charHeight = face->glyph->bitmap.rows + yPos;

		height = max(height,charHeight);
        
        FT_Done_Glyph(glyph);

	}
}

void AssetDatabase::addGlyphToBuffer(FT_Face& face, char letter, unsigned char* buffer, int bufferWidth, int bufferHeight, int xOffset, int yOffset, int yOrigin, int& outGlyphWidth, int& outGlyphHeight)
{
	FT_UInt  glyph_index;


	/* retrieve glyph index from character code */
	glyph_index = FT_Get_Char_Index(face, letter);

	/* load glyph image into the slot (erase previous one) */
	FT_Error error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
	if (error)
	{
	
	
	}
	/* convert to an anti-aliased bitmap */
	error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);

	int offset = (bufferHeight - 1) * bufferWidth + xOffset;
	int width = face->glyph->bitmap.width;
	if (width == 0)
		width = face->glyph->advance.x / 64;

	int height = face->glyph->bitmap.rows;
	int bitmap_left = abs(face->glyph->bitmap_left);

	outGlyphWidth = width + bitmap_left;
	outGlyphHeight = height + face->glyph->bitmap_top;

	int yPos = face->glyph->bitmap.rows - face->glyph->bitmap_top;
	int yOriginDelta = yOrigin - yPos;

	int xI, yI;
	//for (yI = height - 1; yI >= 0; yI--) {
	for (yI = height - 1; yI >= 0; yI--) {
		for (xI = 0; xI<width; xI++) {

			int bufferIndex = offset - (height - yI + yOriginDelta)*bufferWidth + //y
				(xI + bitmap_left); //x
			int bitmapIndex = yI *width + xI;

			buffer[bufferIndex] = face->glyph->bitmap.buffer[bitmapIndex];
		}
	}


}


map<char, LetterFontUV> AssetDatabase::createFontTexture(FT_Face& face, string filename)
{
	map<char, LetterFontUV> charUVMap;

	int width, height, yOrigin;
	width = height = yOrigin = 0;

	string alphabet = "abcdefghjklmnopqrstuvxyzw0123456789 !?,./\[]{};':\"";
	getWidthHeightForAlphabet(face, alphabet, width, height, yOrigin);

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
		addGlyphToBuffer(face, alphabet[i], buffer, width, height, xOffset, yOffset, yOrigin, outGlyphWidth, outGlyphHeight);
		charUVMap[alphabet[i]] = LetterFontUV(glm::vec2(xOffset / (float)width, 0), glm::vec2((xOffset + outGlyphWidth) / (float)width, 1), (float)outGlyphWidth / height);
		xOffset += outGlyphWidth;
	}

	writeImage(filename.c_str(), width, height, buffer, "blabla");

	delete[] buffer;

	return charUVMap;
}



// OLD, NOT USED ANYMORE SINCE PHYSX IS BEEN USED TO CREATE CONVEX HULL
//shared_ptr<Mesh> AssetDatabase::createMesh(vector<glm::vec3> vertices,vector<int> usedIndex,vector<int> usedTris)
//{
//    shared_ptr<Mesh> mesh = make_shared<Mesh>(vertices,usedIndex,usedTris);
//    assignCurrentID(mesh);
//    
//    return mesh;
//}