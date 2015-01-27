#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/gtc/quaternion.hpp>
#include <stdio.h>
#include <memory>
#include <iostream>
#include <fstream>

#include "Serialization2.hpp"

#include "Material.hpp"
#include <vector>
#include "Actor.hpp"
#include "Camera.hpp"
#include <tuple>
#include "Input.hpp"
#include "GraphicsSystem.hpp"
#include "Time.hpp"
#include "World.hpp"
#include "Mesh.hpp"
#include "MeshRenderer.hpp"
#include "Shader.hpp"
//#include <Box2D\Box2D.h>
#include <PxPhysicsAPI.h>
#include <PxQueryReport.h>
#include "FontMesh.hpp"

#include "print.hpp"
#include "Factory.hpp"
#include "PhysXEventCallback.hpp"
#include "Physics.hpp"
#include "Light.hpp"
#include "PhysicsMaterial.hpp"
#include "PlayerScript.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include "MeshFilter.hpp"
#include "SphereCollider.hpp"
#include "IncreaseColliderScript.hpp"
#include "Editor.hpp"
#include "Game.hpp"
#include "MeshCollider.hpp"
#include "MeshImporter.hpp"
#include "AssetDatabase.hpp"
#include "Font.hpp"

#include <fmod.hpp>
#include <fmod_common.h>
#include <fmod_errors.h>
#include <fbxsdk.h>
#include "EditorCameraControl.hpp"
#include "mainwindow.h"
#include "Texture.hpp"
#include <png.h>
#include "Math.hpp"
#include <iostream>
#include <thread>
#include "RotateOverTime.hpp"
#include "AddForceScript.hpp"

//-------Loading PhysX libraries----------]
#ifdef _DEBUG
#pragma comment(lib, "PhysX3DEBUG_x86.lib")
#pragma comment(lib, "PhysX3CommonDEBUG_x86.lib")
#pragma comment(lib, "PhysX3ExtensionsDEBUG.lib")
#pragma comment(lib, "PhysX3CookingDEBUG_x86.lib")
#else
#pragma comment(lib, "PhysX3_x86.lib")
#pragma comment(lib, "PhysX3Common_x86.lib")
#pragma comment(lib, "PhysX3Extensions.lib")
#pragma comment(lib, "PhysX3Cooking_x86.lib")
#endif
using namespace physx;
using namespace std;
using namespace fbxsdk_2015_1;




BOOST_CLASS_EXPORT_GUID(Asset, "Asset")
BOOST_CLASS_EXPORT_GUID(Mesh, "Mesh")
BOOST_CLASS_EXPORT_GUID(Material, "Material")
BOOST_CLASS_EXPORT_GUID(Shader, "Shader")
//BOOST_CLASS_EXPORT_GUID(Component, "Component")
//BOOST_CLASS_EXPORT_GUID(RigidBody, "RigidBody")
//BOOST_CLASS_EXPORT_GUID(MeshFilter, "MeshFilter")
//BOOST_CLASS_EXPORT_GUID(MeshRenderer, "MeshRenderer")
BOOST_CLASS_EXPORT_GUID(ComponentDescription, "ComponentDescription")
BOOST_CLASS_EXPORT_GUID(MeshFilterDescription, "MeshFilterDescription")
BOOST_CLASS_EXPORT_GUID(MeshRendererDescription, "MeshRendererDescription")
BOOST_CLASS_EXPORT_GUID(CameraDescription, "CameraDescription")
BOOST_CLASS_EXPORT_GUID(RigidBodyDescription, "RigidBodyDescription")
BOOST_CLASS_EXPORT_GUID(RigidStaticDescription, "RigidStaticDescription")
BOOST_CLASS_EXPORT_GUID(LightDescription, "LightDescription")
BOOST_CLASS_EXPORT_GUID(ColliderDescription, "ColliderDescription")
BOOST_CLASS_EXPORT_GUID(BoxColliderDescription, "BoxColliderDescription")
BOOST_CLASS_EXPORT_GUID(SphereColliderDescription, "SphereColliderDescription")
BOOST_CLASS_EXPORT_GUID(CapsuleColliderDescription, "CapsuleColliderDescription")

#include <fstream>

#include <ft2build.h>
#include FT_FREETYPE_H


//#define _GLFW_USE_MENUBAR
//#include "mainwindow.h"
//#include <QApplication>
//#include <qsurfaceformat.h>

#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

#include "Module.hpp"
#include "FSAuxiliar.hpp"



void checkFilesOnCommonData(){

    while(true)
    {
//        cout << "OI" <<endl;
        
        
        vector<path> files = getFilesInDirectory(CommonData(""));
        
        for(auto& file : files)
        {
            
            
            string filename = file.filename().string();
            shared_ptr<Asset> asset =AssetDatabase::getAsset(filename);
            
            if(asset)
            {
                int crc = getCRC(file.string());
                
                if(crc == asset->crc)
                    cout << "CRC Matches!" << endl;
                else
                    cout << "CRC does not match!" << endl;
            }
            
        }
        
        
//        path p(CommonData(""));
//        
//        if(is_directory(p))
//        {
//                      // so we can sort them later
//            vector<path> vec;             // store paths,
//            
//            copy(directory_iterator(p), directory_iterator(), back_inserter(vec));
//
//            for(auto& file : vec)
//            {
//                int crc = AssetDatabase::getCRC(CommonData(file));
//            }
//            
//        }
    }
    
}
//
//int writeImage(const char* filename, int width, int height, unsigned char *buffer, char* title)
//{
//	int code = 0;
//	FILE *fp;
//	png_structp png_ptr = NULL;
//	png_infop info_ptr = NULL;
//	png_bytep row = NULL;
//
//		// Open file for writing (binary mode)
//		fp = fopen(filename, "wb");
//	if (fp == NULL) {
//		fprintf(stderr, "Could not open file %s for writing\n", filename);
//		code = 1;
//		goto finalise;
//	}
//		// Initialize write structure
//		png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
//	if (png_ptr == NULL) {
//		fprintf(stderr, "Could not allocate write struct\n");
//		code = 1;
//		goto finalise;
//	}
//
//	// Initialize info structure
//	info_ptr = png_create_info_struct(png_ptr);
//	if (info_ptr == NULL) {
//		fprintf(stderr, "Could not allocate info struct\n");
//		code = 1;
//		goto finalise;
//	}
//		// Setup Exception handling
//		if (setjmp(png_jmpbuf(png_ptr))) {
//			fprintf(stderr, "Error during png creation\n");
//			code = 1;
//			goto finalise;
//		}
//		png_init_io(png_ptr, fp);
//
//	// Write header (8 bit colour depth)
//	png_set_IHDR(png_ptr, info_ptr, width, height,
//		8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
//		PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
//
//	// Set title
//	if (title != NULL) {
//		png_text title_text;
//		title_text.compression = PNG_TEXT_COMPRESSION_NONE;
//		title_text.key = "Title";
//		title_text.text = title;
//		png_set_text(png_ptr, info_ptr, &title_text, 1);
//	}
//
//	png_write_info(png_ptr, info_ptr);
//
//		// Allocate memory for one row (3 bytes per pixel - RGB)
//		//row = (png_bytep)malloc(3 * width * sizeof(png_byte));
//	row = (png_bytep)malloc(4 * width * sizeof(png_byte));
//
//	// Write image data
//	int x, y;
//	for (y = 0; y<height; y++) {
//		for (x = 0; x<width; x++) {
//			//setRGB(&(row[x * 3]), buffer[y*width + x]);
//			//cout << buffer[y*width + x] << endl;
//			//row[x * 3] = buffer[y*width + x];
//			float value = buffer[y*width + x] > 0 ? 255 : 0;
//			float alpha = buffer[y*width + x];
//			row[x * 4 + 0] = value;
//			row[x * 4 + 1] = value;
//			row[x * 4 + 2] = value;
//			row[x * 4 + 3] = alpha;
//			//row[x * 4] = buffer[y*width + x];
//			//cout << x * 4 << endl;
//			//cout << y*width + x<< endl;
//			//cout << endl << endl;
//			//row[x * 3 + 1] = 0;
//		}
//		png_write_row(png_ptr, row);
//	}
//
//	// End write
//	png_write_end(png_ptr, NULL);
//	finalise:
//	if (fp != NULL) fclose(fp);
//	if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
//	if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
//	if (row != NULL) free(row);
//
//	return code;
//}
//
//
////vector<FT_GlyphSlot> getAllCharacters(FT_Face face, string alphabet)
////{
////	vector<FT_GlyphSlot> result;
////	vector<FT_Bitmap> result2;
////
////	for(int i = 0; i < alphabet.size(); i++)
////	{
////		FT_UInt  glyph_index;
/////* retrieve glyph index from character code */
////		glyph_index = FT_Get_Char_Index(face, alphabet[i]);
////
////		/* load glyph image into the slot (erase previous one) */
////		FT_Error error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
////		if (error)
////		{
////			cout << error << endl;
////			continue;  /* ignore errors */
////		}
////		/* convert to an anti-aliased bitmap */
////		error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
////		result.push_back(FT_GlyphSlot(face->glyph));
////		result2.push_back(face->num)
////	}
////
////	return result;
////}
//
//
//
//void getWidthHeightForAlphabet(FT_Face face, string alphabet, int& width, int& height)
//{
//	width = 0;
//	for (int i = 0; i < alphabet.size(); i++)
//	{
//		FT_UInt  glyph_index;
//
//
//		/* retrieve glyph index from character code */
//		glyph_index = FT_Get_Char_Index(face, alphabet[i]);
//
//		/* load glyph image into the slot (erase previous one) */
//		FT_Error error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
//		if (error)
//		{
//			cout << error << endl;
//			continue;  /* ignore errors */
//		}
//		/* convert to an anti-aliased bitmap */
//		error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
//
//		width += face->glyph->bitmap.width + face->glyph->bitmap_left;
//		height = max(height, face->glyph->bitmap.rows + face->glyph->bitmap_top);
//	}
//}
//
//void addGlyphToBuffer(FT_Face& face, char letter, unsigned char* buffer, int bufferWidth, int bufferHeight, int xOffset, int yOffset, int& outGlyphWidth, int& outGlyphHeight)
//{
//	FT_UInt  glyph_index;
//
//
//	/* retrieve glyph index from character code */
//	glyph_index = FT_Get_Char_Index(face, letter);
//
//	/* load glyph image into the slot (erase previous one) */
//	FT_Error error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
//	if (error)
//	{
//		//cout << error << endl;
//		//continue;  /* ignore errors */
//	}
//	/* convert to an anti-aliased bitmap */
//	error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
//
//	//int offset = yOffset * bufferWidth + xOffset;
//	//int width = face->glyph->bitmap.width;
//	//int height = face->glyph->bitmap.rows;
//
//	//outGlyphWidth = width + face->glyph->bitmap_left;
//	//outGlyphHeight = height + face->glyph->bitmap_top;
//
//	//int xI, yI;
//	//for (yI = 0; yI<height; yI++) {
//	////for (yI = height- 1; yI >= 0; yI--) {
//	//	for (xI = 0; xI<width; xI++) {
//
//	//		int bufferIndex = offset + (yI + face->glyph->bitmap_top)*bufferWidth + (xI + face->glyph->bitmap_left);
//	//		int bitmapIndex = yI *width + xI;
//
//	//		buffer[bufferIndex] = face->glyph->bitmap.buffer[bitmapIndex];
//	//	}
//	//}
//
//	int offset = (bufferHeight-1) * bufferWidth + xOffset;
//	int width = face->glyph->bitmap.width;
//	int height = face->glyph->bitmap.rows;
//
//	outGlyphWidth = width + face->glyph->bitmap_left;
//	outGlyphHeight = height + face->glyph->bitmap_top;
//
//	int xI, yI;
//	//for (yI = 0; yI<height; yI++) {
//	for (yI = height- 1; yI >= 0; yI--) {
//		for (xI = 0; xI<width; xI++) {
//
//			int bufferIndex = offset - (height - yI )*bufferWidth + //y
//				(xI + face->glyph->bitmap_left); //x
//			int bitmapIndex = yI *width + xI;
//
//			buffer[bufferIndex] = face->glyph->bitmap.buffer[bitmapIndex];
//		}
//	}
//
//
//}
//
//struct LetterFontUV
//{
//	glm::vec2 bottomLeft, topRight;
//
//	LetterFontUV()
//	{
//
//	}
//	LetterFontUV(glm::vec2 botLeft, glm::vec2 topRight)
//	{
//		this->bottomLeft = botLeft;
//		this->topRight = topRight;
//	}
//
//};
//
//
//void createFontTexture(FT_Library& library, FT_Face& face, string filename)
//{
//	map<char, LetterFontUV> charUVMap;
//
//	int width, height;
//	string alphabet = "abcd";
//	getWidthHeightForAlphabet(face,alphabet, width, height);
//
//	int xOffset, yOffset;
//	xOffset = yOffset = 0;
//	unsigned char* buffer = new unsigned char[width*height];
//	for (int i = 0; i < width*height; i++)
//	{
//		buffer[i] = 0;
//	}
//
//	for (int i = 0; i < alphabet.size(); i++)
//	{
//		int outGlyphWidth, outGlyphHeight;
//		addGlyphToBuffer(face, alphabet[i], buffer, width,height, xOffset, yOffset, outGlyphWidth, outGlyphHeight);
//		charUVMap[alphabet[i]] = LetterFontUV(glm::vec2(xOffset / (float)width,0),glm::vec2((xOffset+outGlyphWidth)/(float)width,1));
//		xOffset += outGlyphWidth;
//	}
//
//	writeImage(filename.c_str(), width, height, buffer, "blabla");
//}
//	
//	//vector<FT_GlyphSlot> characters = getAllCharacters(face, "abcd");
//
//	int code = 0;
//	FILE *fp;
//	png_structp png_ptr = NULL;
//	png_infop info_ptr = NULL;
//	png_bytep row = NULL;
//
////	// Open file for writing (binary mode)
////	fp = fopen(filename.c_str(), "wb");
////	if (fp == NULL) {
////		fprintf(stderr, "Could not open file %s for writing\n", filename);
////		code = 1;
////		goto finalise;
////	}
////	// Initialize write structure
////	png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
////	if (png_ptr == NULL) {
////		fprintf(stderr, "Could not allocate write struct\n");
////		code = 1;
////		goto finalise;
////	}
////
////	// Initialize info structure
////	info_ptr = png_create_info_struct(png_ptr);
////	if (info_ptr == NULL) {
////		fprintf(stderr, "Could not allocate info struct\n");
////		code = 1;
////		goto finalise;
////	}
////	// Setup Exception handling
////	if (setjmp(png_jmpbuf(png_ptr))) {
////		fprintf(stderr, "Error during png creation\n");
////		code = 1;
////		goto finalise;
////	}
////	png_init_io(png_ptr, fp);
////
////	// Write header (8 bit colour depth)
////	png_set_IHDR(png_ptr, info_ptr, width, height,
////		8, PNG_COLOR_TYPE_RGBA, PNG_INTERLACE_NONE,
////		PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);
////
////	// Set title
////	if (title != NULL) {
////		png_text title_text;
////		title_text.compression = PNG_TEXT_COMPRESSION_NONE;
////		title_text.key = "Title";
////		title_text.text = title;
////		png_set_text(png_ptr, info_ptr, &title_text, 1);
////	}
////
////	png_write_info(png_ptr, info_ptr);
////
////	// Allocate memory for one row (3 bytes per pixel - RGB)
////	//row = (png_bytep)malloc(3 * width * sizeof(png_byte));
////	row = (png_bytep)malloc(4 * width * sizeof(png_byte));
////
////	// Write image data
////	int x, y;
////	for (y = 0; y<height; y++) {
////		for (x = 0; x<width; x++) {
////			//setRGB(&(row[x * 3]), buffer[y*width + x]);
////			//cout << buffer[y*width + x] << endl;
////			//row[x * 3] = buffer[y*width + x];
////			float value = buffer[y*width + x] > 0 ? 255 : 0;
////			float alpha = buffer[y*width + x];
////			row[x * 4 + 0] = value;
////			row[x * 4 + 1] = value;
////			row[x * 4 + 2] = value;
////			row[x * 4 + 3] = alpha;
////			//row[x * 4] = buffer[y*width + x];
////			//cout << x * 4 << endl;
////			//cout << y*width + x<< endl;
////			//cout << endl << endl;
////			//row[x * 3 + 1] = 0;
////		}
////		png_write_row(png_ptr, row);
////		//png_ptr
////	}
////
////	// End write
////	png_write_end(png_ptr, NULL);
////finalise:
////	if (fp != NULL) fclose(fp);
////	if (info_ptr != NULL) png_free_data(png_ptr, info_ptr, PNG_FREE_ALL, -1);
////	if (png_ptr != NULL) png_destroy_write_struct(&png_ptr, (png_infopp)NULL);
////	if (row != NULL) free(row);
////
//	return code;
//}
//


int main(int argc, char *argv[]) {
  
//
//	FT_Library  library;
//
//	FT_Error error = FT_Init_FreeType(&library);
//	if (error)
//	{
//	//	... an error occurred during library initialization ...
//		cout << "Erro" << endl;
//	}
//
//	FT_Face     face;      /* handle to face object */
//	error = FT_New_Face(library, CommonData("arial.ttf").c_str(),
//		0,
//		&face);
//	if (error == FT_Err_Unknown_File_Format)
//	{
//
//	}
//	else if (error)
//	{
//	}
//	else
//	{
//		cout << "Loaded OK" << endl;
//	}
//
//	error = FT_Set_Char_Size(
//		face,    /* handle to face object           */
//		0,       /* char_width in 1/64th of points  */
//		16 * 64,   /* char_height in 1/64th of points */
//		300,     /* horizontal device resolution    */
//		300);   /* vertical device resolution      */
//
//	FT_GlyphSlot  slot = face->glyph;  /* a small shortcut */
//	int           pen_x, pen_y, n;
//	pen_x = 0; pen_y = 0;
//
//	string alphabet = "abcdefg";
//
//	createFontTexture(library, face, CommonData("Test2.png"));
//
//	int width, height;
//	getWidthHeightForAlphabet(face, alphabet, width, height);
//
//	for (int i = 0; i < alphabet.size(); i++)
//	{
//		FT_UInt  glyph_index;
//
//
//		/* retrieve glyph index from character code */
//		glyph_index = FT_Get_Char_Index(face, alphabet[i]);
//
//		/* load glyph image into the slot (erase previous one) */
//		error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
//		if (error)
//		{
//			cout << error << endl;
//			continue;  /* ignore errors */
//		}
//		/* convert to an anti-aliased bitmap */
//		error = FT_Render_Glyph(face->glyph, FT_RENDER_MODE_NORMAL);
//		if (error)
//			continue;
//
//		FT_Bitmap bitmap = slot->bitmap;
//		if (bitmap.pixel_mode == FT_PIXEL_MODE_GRAY)
//			cout << "FT_PIXEL_MODE_GRAY" << endl;
//		if (bitmap.pixel_mode == FT_PIXEL_MODE_MONO)
//			cout << "FT_PIXEL_MODE_MONO" << endl;
//		if (bitmap.pixel_mode == FT_PIXEL_MODE_GRAY2)
//			cout << "FT_PIXEL_MODE_GRAY2" << endl;
//		if (bitmap.pixel_mode == FT_PIXEL_MODE_GRAY4)
//			cout << "FT_PIXEL_MODE_GRAY4" << endl;
//		if (bitmap.pixel_mode == FT_PIXEL_MODE_LCD)
//			cout << "FT_PIXEL_MODE_LCD" << endl;
//		if (bitmap.pixel_mode == FT_PIXEL_MODE_LCD_V)
//			cout << "FT_PIXEL_MODE_LCD_V" << endl;
//		/*if (bitmap.pixel_mode == FT_PIXEL_MODE)
//			cout << "FT_PIXEL_MODE_BGRA" << endl;*/
//		
//		writeImage(CommonData("Test.png").c_str(), bitmap.width, bitmap.rows, bitmap.buffer, "test");
//
//		//bitmap.pi
//		//if(bitmap.pixel_mode == Ftbit
//
//		/* now, draw to our target surface */
//		/*my_draw_bitmap(&slot->bitmap,
//			pen_x + slot->bitmap_left,
//			pen_y - slot->bitmap_top);
//*/
//		/* increment pen position */
//		pen_x += slot->advance.x >> 6;
//		pen_y += slot->advance.y >> 6; /* not useful for now */
//	}
//



//    std::thread t1(checkFilesOnCommonData);
//    t1.detach();
    
    
//    glm::vec3 p1,p2,p3;
//
//    p1 = glm::vec3(1,0,0);
//    p2 = glm::vec3(0,0,1);
//    p3 = glm::vec3(0,0,0);
//    
//    cout << p1 << " " << p2 << " " << p3 << endl;
//    
//
//    
//    orderVertexCCW(p1, p2, p3);
//
//        cout << p1 << " " << p2 << " " << p3 << endl;
//
//        glm::vec3 p4(0,1,0);
//
//        cout << isPlaneFacingPoint(Plane(p1,p2,p3), p4) << endl;
    
//    QApplication app(argc, argv);
//
//
//    MainWindow myWindow;// = new MainWindow;
//    //QWidget *window = myWindow->window();
//
    int notOK = GraphicsSystem::getInstance()->init();
	if (notOK)
		return 1;
    
    
//
//    //GraphicsSystem::getInstance()->setGraphicsParent(app.activeWindow());
//
//    myWindow.init();
//    myWindow.show();
//
//
//    return app.exec();

//    while(true)
//    {
//        if(app.hasPendingEvents())
//            app.processEvents();

//        myWindow.tick();
//    }
//    return app.exec();

    Input input(GraphicsSystem::getInstance()->window);


//	FMOD_RESULT result;
//	FMOD::System *system = NULL;

//	result = FMOD::System_Create(&system);      // Create the main system object.
//	if (result != FMOD_OK)
//	{
//		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
//		exit(-1);
//	}

//	result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
//	if (result != FMOD_OK)
//	{
//		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
//		exit(-1);
//	}
//	FMOD::Channel    *channel = 0;
//	FMOD::Sound *sound1;
//	result = system->createSound(CommonData("mp3test.mp3").c_str(), FMOD_DEFAULT, 0, &sound1);
//	//ERRCHECK(result);

//	result = system->playSound(sound1, 0, false, &channel);
    //ERRCHECK(result);
	
    Physics physics;
    physics.init();
    
    EngineMode engineMode = EngineMode::editor;
    
	AssetDatabase::init();

	
		vector<MeshVertex> quadVertex;
		MeshVertex meshVertex;
		meshVertex.position.x = -0.5;
		meshVertex.position.y = -0.5;
		meshVertex.position.z = 0;
		meshVertex.normal.x = 0;
		meshVertex.normal.y = 0;
		meshVertex.normal.z = 1;
		meshVertex.uv.x = 0;
		meshVertex.uv.y = 0;

		quadVertex.push_back(meshVertex);

		meshVertex.position.x = -0.5;
		meshVertex.position.y = 0.5;
		meshVertex.position.z = 0;
		meshVertex.normal.x = 0;
		meshVertex.normal.y = 0;
		meshVertex.normal.z = 1;
		meshVertex.uv.x = 0;
		meshVertex.uv.y = 1;

		quadVertex.push_back(meshVertex);

		meshVertex.position.x = 0.5;
		meshVertex.position.y = -0.5;
		meshVertex.position.z = 0;
		meshVertex.normal.x = 0;
		meshVertex.normal.y = 0;
		meshVertex.normal.z = 1;
		meshVertex.uv.x = 1;
		meshVertex.uv.y = 0;

		quadVertex.push_back(meshVertex);

		meshVertex.position.x = 0.5;
		meshVertex.position.y = 0.5;
		meshVertex.position.z = 0;
		meshVertex.normal.x = 0;
		meshVertex.normal.y = 0;
		meshVertex.normal.z = 1;
		meshVertex.uv.x = 1;
		meshVertex.uv.y = 1;

		quadVertex.push_back(meshVertex);

		vector<unsigned short> triangles;
		triangles.push_back(0);
		triangles.push_back(1);
		triangles.push_back(2);
		triangles.push_back(2);
		triangles.push_back(1);
		triangles.push_back(3);

		shared_ptr<Mesh> quadMesh = AssetDatabase::createMesh(quadVertex, triangles);

		shared_ptr<Texture> texture = AssetDatabase::createTexture(CommonData("button.png"));

		shared_ptr<Font> font = AssetDatabase::createFont(CommonData("arial.ttf"),48);


		//        read_png_file(CommonData("Crosshair.png").c_str());

		// shared_ptr<Mesh> fbxMesh = AssetDatabase::createMeshFromFBX("cylinder.fbx");
		//fbxMesh->setScaleFactor(0.1f);

		shared_ptr<Mesh> cylinderMesh = AssetDatabase::createMeshFromFBX("cylinder3.fbx");

		shared_ptr<Mesh> cubeMesh = AssetDatabase::createMeshFromFBX("cubeCenter.fbx");

		shared_ptr<Mesh> objMesh = AssetDatabase::createMeshFromOBJ("sphere.obj");

		//    vector<glm::vec3> fbxNonDup = fbxMesh->getNonDuplicateMeshVertex();
		//    
		//    for(int i = 0; i < fbxNonDup.size(); i++)
		//    {
		//        cout << i << " " << fbxNonDup[i]<< endl;
		//    }
		//    
		//    vector<glm::vec3> hullTest = {
		//        glm::vec3(0,0,0), //p0
		//        glm::vec3(0,1,0), //p1
		//        glm::vec3(1,1,0), //p2
		//        glm::vec3(1,0,0), //p3
		//        glm::vec3(0,0,1), //p4
		//        glm::vec3(1,0,1), //p5
		//        glm::vec3(1,1,1), //p6
		//        glm::vec3(0,1,1), //p7
		//        //glm::vec3(0.5f,2,0.5f), //p8
		//        //glm::vec3(0.5f,-1,0.5f), //p9
		//        glm::vec3(2.0f,0.5f,0.5f), //p8
		//    //    glm::vec3(2,0 ,1)
		//    }; //p9
		//    
		//    vector<int> usedIndex;
		//    vector<int> usedTris;
		//    
		//    convexHull(fbxNonDup, usedIndex, usedTris);
		//
		//    shared_ptr<Mesh> tryMesh = AssetDatabase::createMesh(fbxNonDup,usedIndex,usedTris);
		//    


		shared_ptr<Shader> s = AssetDatabase::createShader("LightShader", CommonData("vsLight.vs"), CommonData("fsLight.fragmentshader"));
		//shared_ptr<Shader> s = AssetDatabase::createShader(CommonData("vsLight.vs"),CommonData("fsNoLight.fragmentshader"));

		shared_ptr<Material> defaultMaterial = AssetDatabase::createMaterial("DefaultMaterial", s);
		defaultMaterial->setParamTexture("myTextureSampler", texture);
		shared_ptr<Material> fontMaterial = AssetDatabase::createMaterial("FontMaterial", s);
		fontMaterial->setParamTexture("myTextureSampler", font->fontTexture);

		shared_ptr<Editor> editor = make_shared<Editor>();
		editor->init();

		shared_ptr<Game> game = make_shared<Game>();
		game->init();
		{
		// create and open a character archive for output
		std::ofstream ofs(CommonData("filename"));


		shared_ptr<Actor> fbxTest;

		fbxTest = Factory::CreateActor("FBXTest");// , meshRenderer1);
		//fbxTest->transform->setScale(glm::vec3(10,10,10));
		//    fbxTest->transform->setRotationQuat(glm::quat(glm::vec3(45 * Deg2Radian, 45 * Deg2Radian, 45 * Deg2Radian)));
		shared_ptr<MeshFilter> meshFilter = fbxTest->AddComponent<MeshFilter>();

		//meshFilter->mesh = dynamic_pointer_cast<Mesh>(objMesh);
		meshFilter->mesh = objMesh;
		shared_ptr<MeshRenderer> meshRenderer = fbxTest->AddComponent<MeshRenderer>();
		meshRenderer->material = defaultMaterial;
		shared_ptr<RigidBody> rigidBody = fbxTest->AddComponent<RigidBody>();
		//rigidBody->setMoveEnabled(TransformAxis::y, false);
		//    rigidBody->setMoveEnabled(TransformAxis::z, false);
		//        rigidBody->setMoveEnabled(TransformAxis::x, false);

		//     rigidBody->setRotateEnabled(TransformAxis::x, false);
		//     rigidBody->setRotateEnabled(TransformAxis::y, false);
		//     rigidBody->setRotateEnabled(TransformAxis::z, false);


		//fbxTest->AddComponent<RigidBody>();
		fbxTest->AddComponent<SphereCollider>();
		fbxTest->AddComponent<AddForceScript>();
		//fbxTest->AddComponent<SphereCollider>();



		shared_ptr<Actor> fontTest = Factory::CreateActor("FontTest");// , meshRenderer1);
		shared_ptr<FontMesh> fontMesh = fontTest->AddComponent<FontMesh>();
		fontMesh->setFont(font);
		fontMesh->setText("opa,blz?");
		meshRenderer = fontTest->AddComponent<MeshRenderer>();
		meshRenderer->setMaterial(fontMaterial);


		//    int bla = 0;
		//    //while(bla == 0)
		//    for(int i = 0; i < fbxNonDup.size(); i++)
		//    {
		//        stringstream ss;
		//        ss.append("point");
		//        ss.append(i);
		//        fbxTest = Factory::CreateActor(ss);// , meshRenderer1);
		//    //fbxTest->transform->setScale(glm::vec3(10,10,10));
		//        //fbxTest->transform->setScale(glm::vec3(0.5f,0.5f,0.5f));
		//        fbxTest->transform->setPosition(glm::vec3(0,0,1));
		//     //fbxTest->transform->setRotationQuat(glm::quat(glm::vec3(-90 * Math::Deg2Radian, 0, 0)));
		//        shared_ptr<MeshFilter> meshFilter = fbxTest->AddComponent<MeshFilter>();
		//        //meshFilter->mesh = dynamic_pointer_cast<Mesh>(objMesh);
		//        meshFilter->mesh = objMesh;
		//            shared_ptr<MeshRenderer> meshRenderer = fbxTest->AddComponent<MeshRenderer>();
		//        meshRenderer->material = m;
		//        
		//        bla++;
		//    }

		//    shared_ptr<MeshFilter> meshFilter = fbxTest->AddComponent<MeshFilter>();
		//    //meshFilter->mesh = dynamic_pointer_cast<Mesh>(objMesh);
		//    meshFilter->mesh = tryMesh;
		//    shared_ptr<MeshRenderer> meshRenderer = fbxTest->AddComponent<MeshRenderer>();
		//    meshRenderer->material = m;
		//    fbxTest->AddComponent<RigidBody>();
		//    fbxTest->AddComponent<BoxCollider>();

		shared_ptr<Actor> floor = Factory::CreateActor("Floor");

		meshFilter = floor->AddComponent<MeshFilter>();
		floor->transform->setPosition(glm::vec3(0, -4, 0));
		floor->transform->setRotationQuat(glm::quat(glm::vec3(0, 0, 45 * Deg2Radian)));
		floor->transform->setScale(glm::vec3(5, 0.1f, 5.0f));

		meshFilter->mesh = cubeMesh;
		meshRenderer = floor->AddComponent<MeshRenderer>();
		meshRenderer->material = defaultMaterial;
		floor->AddComponent<BoxCollider>();


		//    floor->AddComponent<RotateOverTime>();
		//    floor->AddComponent<RigidSta>();


		//    //fbxTest = nullptr;
		//	
		//    
		// //   shared_ptr<World> testWorld = game->world;
		//    
		// //   shared_ptr<RigidBody> rigidBody = fbxTest->AddComponent<RigidBody>();
		//    // save data to archive
		//    {
		//        boost::archive::text_oarchive oa(ofs);
		//        // write class instance to archive
		//        oa & AssetDatabase::idToAsset;
		//        oa & AssetDatabase::currentID;
		//        
		//        //oa & rigidBody;
		//        //oa & fbxTest;
		////        oa & fbxTest->components;
		//        
		//        ActorDescription desc = getActorDescription(fbxTest);
		//        
		//        oa & desc;
		//        vector<shared_ptr<ComponentDescription>> compDescs = getActorComponentsDescription(fbxTest);
		//        oa & compDescs;
		//        
		//        //oa & game->world;
		//        // archive and stream closed when destructors are called
		//    }
		//  //  exit(0);
		//    
		//    
		//    //Actor x;
		//    shared_ptr<Actor> serializeTest;
		//    {
		//        // create and open an archive for input
		//        std::ifstream ifs(CommonData("filename"),std::fstream::binary | std::fstream::in);
		//        boost::archive::text_iarchive ia(ifs);
		//        // read class state from archive
		//        //ia >> objLoad;
		//        ia & AssetDatabase::idToAsset;
		//        ia & AssetDatabase::currentID;
		//    //    ia & testWorld;
		//        //ia & fbxTest;
		//        //ia & x;
		//        //ia & testWorld;
		//        
		//       // ia & game->world;
		//        
		//        ActorDescription desc;// = getActorDescription(*fbxTest);
		//        
		//        ia & desc;
		//        
		//        serializeTest = Factory::DeserializeActor(desc);
		//        
		//        vector<shared_ptr<ComponentDescription>> compDescs;
		//        ia & compDescs;
		//        
		//        Factory::DeserializeComponents(serializeTest,compDescs);
		//    }
		//
		//    shared_ptr<Asset> loadedObjMesh = dynamic_pointer_cast<Mesh>(AssetDatabase::idToAsset[1]);///AssetDatabase::createMeshFromOBJ("sphere.obj");
		//
		//     shared_ptr<Shader> loadedShader = dynamic_pointer_cast<Shader>(AssetDatabase::idToAsset[2]);///
		//    
		//    shared_ptr<Material> loadedMaterial = dynamic_pointer_cast<Material>(AssetDatabase::idToAsset[3]);///
		//    
		//    
		//    shared_ptr<MeshFilter> meshFilter2 = serializeTest->AddComponent<MeshFilter>();
		//    meshFilter2->mesh = dynamic_pointer_cast<Mesh>(loadedObjMesh);
		//    shared_ptr<MeshRenderer> meshRenderer2 = serializeTest->AddComponent<MeshRenderer>();
		//    meshRenderer2->material = loadedMaterial;

		shared_ptr<Actor> myLight = Factory::CreateActor("Light");// , meshRenderer4);
		myLight->transform->setPosition(glm::vec3(0, 10, 10));
		myLight->AddComponent<Light>();

		shared_ptr<Actor> myCamera = Factory::CreateActor("Camera");// , meshRenderer4);
		myCamera->transform->setPosition(glm::vec3(0, 0, 10));
		myCamera->transform->setRotationQuat(glm::quat(glm::vec3(0, 180 * Deg2Radian, 0)));
		myCamera->AddComponent<Camera>();
		myCamera->AddComponent<EditorCameraControl>();

		shared_ptr<PhysicsMaterial> physMaterial = physics.createMaterial(0.5f, 0.5f, 0.75f);
	}

    editor->world->awake();
    game->world->awake();

    while (!glfwWindowShouldClose(GraphicsSystem::getInstance()->window.get())) {
        Time::frameStart();

        Input::updateInputState();

        
        switch (engineMode)
        {
        case EngineMode::editor:
            editor->update(Time::deltaTime,game->world);
            break;
        case EngineMode::game:
            game->update(Time::deltaTime);
            break;
        default:
            break;
        }
		
        if (Input::getKeyPressed(GLFW_KEY_1))
            engineMode = EngineMode::editor;
        if (Input::getKeyPressed(GLFW_KEY_2))
            engineMode = EngineMode::game;
	
        Time::frameEnd();
    }

    physics.shutdown();
	
    editor->shutdown();

    game->shutdown();

    // close GL context and any other GLFW resources
    GraphicsSystem::getInstance()->shutdown();


	return 0;
}	
