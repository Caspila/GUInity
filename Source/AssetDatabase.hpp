//
//  File.h
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2014-12-30.
//  Copyright (c) 2014 Guilherme Cunha. All rights reserved.
//

#ifndef __opengl_testing_mag__File__
#define __opengl_testing_mag__File__

#include <iostream>
#include "MeshImporter.hpp"
#include <map>
#include "Font.hpp"
#include "Asset.hpp"
#include "Mesh.hpp"

class Shader;
class Material;
class Shader;
class Texture;
class Font;
class Sound;


#include <ft2build.h>
#include FT_FREETYPE_H

/** AssetDatabase is a static class that creates and holds all user Assets (exceptions are the assets used by the system). 
	The idea is to simulate Unity's Asset folder, making sure that whenever a file is added, it's automatically loaded.*/

class AssetDatabase
{
private:
	/** Class that knows how to import .obj and .fbx */
    static MeshImporter meshImporter;
	/** currentID, "Primary Key"*/
	static unsigned int currentID;

	/** Map that translates IDs to Asset */
	static std::map<unsigned int, shared_ptr<Asset>> idToAsset;
	/** Map that translates Name to Asset */
	static std::map<string, shared_ptr<Asset>> nameToAsset;


public:
    
	/** init. Function that initializes the class. */
    static void init();
	/** shutdown. Releases allocated memmory */
    static void shutdown();
	
	/** readSerialiationFile. Loads an asset from a description file (Deserialize an asset) */
	static void readSerialiationFile(string fullPath);
	/** createSerializationFile. Create a meta-file for an asset (Serialize an asset) */
	static void createSerializationFile(shared_ptr<Asset> asset, string filename);
	/** Once serialization is done and working, the AssetDatabase should not reload all files
	everytime. It should load only the Asset Description (.meta<->.desc) file and check if it's up to date */
	static void loadAllMetaFiles();

	/** Search on the database for the asset with name==filename.*/
	static shared_ptr<Asset> getAsset(string filename);
	/** Search on the database for the asset with assetID==assetID.*/
	static shared_ptr<Asset> getAsset(unsigned int assetID);

	/** assignCurrentID. Increments the primary key and add the Asset to the maps with the proper name. */
	template <typename T>
	static void assignCurrentID(T asset, string name);
	/** assignCurrentID. Increments the primary key and add the Asset to the maps. Uses the assetID as the name */
	template <typename T>
	static void assignCurrentID(T asset);

	/** tryLoadAsset. Delegates the file to the appropriate loader. */
	static shared_ptr<Asset> tryLoadAsset(string file, string extension);

	/** Create shader from a vertex shader and a fragment shader. Name is the name of the newly created shader */
    static shared_ptr<Shader> createShader(string name, string vsFilename, string fsFilename);
	/** Create material from a shader. Several materials can have the same shader but different properties, such as textures and colors. */
	static shared_ptr<Material> createMaterial(string name, shared_ptr<Shader> shader);
	
	/** Create mesh from .fbx files*/
    static shared_ptr<Mesh> createMeshFromFBX(string filename);
	/** Create mesh from .obj files*/
	static shared_ptr<Mesh> createMeshFromOBJ(string filename);
	/** Create mesh from list of vertice data and triangles*/
	static shared_ptr<Mesh> createMesh(vector<MeshVertex> vertex, vector<unsigned short> triangles);
	/** Create empty mesh. Used for FontMeshes that dynamicaly create the mesh*/
    //static shared_ptr<Mesh> createMesh();
    
	/** Create Sound asset from file. */
	static shared_ptr<Sound> createSound(string filename);
	/** Create Texture from file. Only supported file is .png in the moment.*/
    static shared_ptr<Texture> createTexture(string filename);
	/** Create Font from .ttf file.*/
	static shared_ptr<Font> createFont(string filename, int fontSize);

	
private:
	// TODO. AssetDatabase should only delegate the job of loading an asset, not load it itself.
	// -Create a class to handle wrap pgn files
	// =Create a class to handle wrap freetype library and load font

	/** creates a .png texture for the a Font */
	static map<char, LetterFontUV> createFontTexture(FT_Face& face, string filename);
	/** adds a Glyph (character) to the image buffer. Used by createFontTexture. */
	static void addGlyphToBuffer(FT_Face& face, char letter, unsigned char* buffer, int bufferWidth, int bufferHeight, int xOffset, int yOffset, int yOrigin, int& outGlyphWidth, int& outGlyphHeight);
	/** calculate the Width and Height of the resulting font Texture for the alphabet*/
	static void getWidthHeightForAlphabet(FT_Face face, string alphabet, int& width, int& height, int &yOrigin);
	/** Write a buffer to a .png file*/
	static int writeImage(const char* filename, int width, int height, unsigned char *buffer, char* title);
	/** loads a .png file to a buffer */
	static void* loadTexture(const string filename, int &width, int &height);

	// OLD, NOT USED ANYMORE SINCE PHYSX IS BEEN USED TO CREATE CONVEX HULL
	//static shared_ptr<Mesh> createMesh(vector<glm::vec3> vertices, vector<int> usedIndex, vector<int> usedTris);

};


#endif /* defined(__opengl_testing_mag__File__) */
