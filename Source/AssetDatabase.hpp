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
#include "FSAuxiliar.hpp"

class Shader;
class Material;
class Shader;
class Texture;
class Font;
class Sound;
class PhysicsMaterial;

#include <ft2build.h>
#include FT_FREETYPE_H

/** AssetDatabase is a static class that loads and holds a reference to all the Assets in the game. It automatically loads all the assets that are inside the data folder.
 
 TODO
 ----
 -Keep track of files and reimport when they're modified
 */

class AssetDatabase
{
private:
	/** Class that knows how to import .obj and .fbx */
    static MeshImporter meshImporter;
	/** Unique identifier of the Asset */
	static unsigned int currentID;
    
	/** Map that translates IDs to Asset */
	static std::map<unsigned int, shared_ptr<Asset>> idToAsset;
	/** Map that translates Name to Asset */
	static std::map<string, shared_ptr<Asset>> nameToAsset;
    
    
public:
    
	/** Initialize the AssetDatabase */
    static void init();
	/** Releases allocated memmory */
    static void shutdown();
	
	/** Loads an asset from a description file (Deserialize an asset) */
	static void readSerialiationFile(string fullPath);
	/** Create a meta-file for an asset (Serialize an asset)
     @param[in] asset Asset that will be serialized
     @param[in] filename Meta file output
     */
	static void createSerializationFile(shared_ptr<Asset> asset, string filename);
	/** Once serialization is done and working, the AssetDatabase should not reload all files
     everytime. It should load only the Asset Description (.meta<->.desc) file and check if it's up to date */
	static void loadAllMetaFiles();
    
	/** Search on the database for the asset with name==filename.
     @param[in] name Name of the Asset
     @return Reference to Asset or nullptr it there's no Asset with the name or if it's a different type.
     */
    template <class T>
    static shared_ptr<T> getAsset(string name)
    {
        
        map<string,shared_ptr<Asset>>::iterator it;
        it = nameToAsset.find(name);
        if(it!=nameToAsset.end())
        {
            shared_ptr<T> ptr = dynamic_pointer_cast<T>(nameToAsset[name]);
            if(!ptr)
            {
                cout << "Could not get Asset as " << typeid(T).name() << endl;
                return nullptr;
            }
            return ptr;
        }
        
        return nullptr;
        
    }
	/** Search on the database for the asset with assetID==assetID
     @param[in] assetID ID of the asset
     @return Reference to Asset or nullptr it there's no Asset with the assetID or if it's a different type.
     */
    template <class T>
    static shared_ptr<T> getAsset(unsigned int assetID)
    {
        
        map<unsigned int, shared_ptr<Asset>>::iterator it;
        it = idToAsset.find(assetID);
        
        if (it != idToAsset.end())
        {
            shared_ptr<T> ptr = dynamic_pointer_cast<T>(idToAsset[assetID]);
            if(!ptr)
            {
                cout << "Could not get Asset as " << typeid(T).name() << endl;
                return nullptr;
            }
            return ptr;
        }
        
        return nullptr;
    }
    
    
	/** Increments the global uniqueID and add the Asset to the maps with the proper name and ID
     @param[in] asset The Asset
     @param[in] name The name of the Asset
     */
	template <typename T>
	static void assignCurrentID(T asset, string name)
    {
        asset->setAssetID(currentID);
        
        idToAsset[currentID] = asset;
        
        asset->setName(name);
        asset->setCRC(getCRC(CommonData(name)));
        
        nameToAsset[name] = asset;
        
        //    createSerializationFile(asset,CommonData(name));
        
        currentID++;
    }
    
	/** Increments the global uniqueID and add the Asset to the map with the proper ID. Uses assetID as the name
     @param[in] asset The Asset
     */
	template <typename T>
	static void assignCurrentID(T asset)
    {
        asset->setAssetID(currentID);
        
        idToAsset[currentID] = asset;
        
        string name = std::to_string(currentID);
        asset->setName(name);
        
        nameToAsset[name] = asset;
        
        currentID++;
    }
    
	/** Tries to load and asset, checking its extension and delegating the file to the appropriate loader
     @param[in] filename The filename without extension
     @param[in] filename The extension of the file
     @return Reference to the loaded Asset or nullptr
     */
	static shared_ptr<Asset> tryLoadAsset(string filename, string extension);
    
	/** Create shader from a vertex shader and a fragment shader
     @param[in] name Name of the Asset
     @param[in] vsFilename Vertex Shader filename
     @param[in] fsFilename Fragment Shader filename
     @return Reference to the Asset that was created
     @*/
    static shared_ptr<Shader> createShader(string name, string vsFilename, string fsFilename);
	/** Create material from a shader. Several materials can have the same shader but different properties, such as textures and colors.
     @param[in] name Name of the Asset
     @param[in] shader Reference to the Shader
     @return Reference to the Asset that was created
     */
	static shared_ptr<Material> createMaterial(string name, shared_ptr<Shader> shader);
	
	/** Create a physics material that can be used to specify behaviour of shapes in the physics scene
     @param[in] name Name of the Asset
     @param[in] friction The friction of the material
     @param[in] dynamicFriction The dynamic friction of the material
     @param[in] restitution The restiturion of the material
     @return Reference to the Asset that was created
     */
	static shared_ptr<PhysicsMaterial> createPhysicsMaterial(string name, float friction, float dynamicFriction, float restitution);
    
    /** Automatically checks all files on the root of the CommonData folder and tries to load it to memory */
    static void loadFilesInCommonData();
    
    
	/** Create Mesh from .fbx file
     @param[in] filename The Asset filename
     @return Reference to the Asset that was created
     */
    static shared_ptr<Mesh> createMeshFromFBX(string filename);
	/** Create Mesh from .obj file
     @param[in] filename The Asset filename
     @return Reference to the Asset that was created
     */
	static shared_ptr<Mesh> createMeshFromOBJ(string filename);
	/** Create Mesh from list of vertice data and triangles
     @param[in] vertices The vertices of the Mesh
     @param[in] triangles The indexed triangles of the Mesh
     @return Reference to the Asset that was created
     */
	static shared_ptr<Mesh> createMesh(vector<MeshVertex> vertices, vector<unsigned short> triangles);
    
    
	/** Create Sound asset from file.
     @param[in] filename The Asset filename
     @return Reference to the Asset that was created
     */
	static shared_ptr<Sound> createSound(string filename);
	/** Create Texture from file. Only supported file is .png in the moment.
     @param[in] filename The Asset filename
     @return Reference to the Asset that was created
     */
    static shared_ptr<Texture> createTexture(string filename);
	/** Create Font from .ttf file.
     @param[in] filename The Asset filename
     @param[in] fontSize The size of the font
     
     @return Reference to the Asset that was created
     */
	static shared_ptr<Font> createFont(string filename, int fontSize);
    
	
private:
	// TODO. AssetDatabase should only delegate the job of loading an asset, not load it itself.
	// -Create a class to handle wrap pgn files
	// =Create a class to handle wrap freetype library and load font
    
	/** creates a .png texture for the a Font
     @param[in] face Reference to the loaded FreeType FT_Face
     @param[in] textureFilename The texture output
     @return the CharacterCatalog for the Font. Character Catalog is created together with the Texture to save some processing
     */
	static CharacterCatalog createFontTexture(FT_Face& face, string textureFilename);
	/** adds a Glyph (character) to an image buffer. Used by createFontTexture.
     @param[in] face Reference to the loaded FreeType FT_Face
     @param[in] letter The character that's being added
     @param[in,out] buffer The image buffer
     @param[in] bufferWidth The width of the buffer
     @param[in] bufferHeight The height of the buffer
     @param[in] xOffset The x offset on the buffer to add this character
     @param[in] yOffset The y offset on the buffer to add this character
     @param[in] yOrigin Secondary y offset to make sure that all letters are aligned
     @param[out] outGlyphWidth Width of the character
     @param[out] outGlyphHeight Height of the character
     */
	static void addGlyphToBuffer(FT_Face& face, char letter, unsigned char* buffer, int bufferWidth, int bufferHeight, int xOffset, int yOffset, int yOrigin, int& outGlyphWidth, int& outGlyphHeight);
	/** calculate the Width and Height of the resulting font Texture for the alphabet
     @param[in] face Reference to the loaded FreeType FT_Face
     @param[in] alphabet The alphabet, all the characters, that the Font should support
     @param[out] width The width of the Texture
     @param[out] height The height of the Texture
     @param[out] yOrigin The Y position that ensures that all characters are aligned
     */
	static void getWidthHeightForAlphabet(FT_Face face, string alphabet, int& width, int& height, int &yOrigin);
	/** Write a buffer to a .png file
     @param[in] filename The file output
     @param[in] width The width of the buffer
     @param[in] height The height of the buffer
     @param[in] buffer The image data
     @param[in] title PNG description title
     */
	static int writeImage(const char* filename, int width, int height, unsigned char *buffer, char* title);
	/** loads a .png file to a buffer
     
     @param[in] filename The Asset filename
     @param[out] width The width of image
     @param[out] height The height of image
     */
    
	static void* loadTexture(const string filename, int &width, int &height);
    
    
};


#endif
