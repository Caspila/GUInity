#include "FontMesh.hpp"
#include "Mesh.hpp"
#include "Font.hpp"
#include "Actor.hpp"

/** Default Constructor*/
FontMesh::FontMesh()
{
//#ifdef GUINITY_DEBUG
//	nCount++;
//#endif
}

/** Default Destructor. Virtual because it's children class.*/
FontMesh::~FontMesh()
{
//#ifdef GUINITY_DEBUG
//	nCount--;
//	cout << "FontRenderer destroyed (" << nCount << " remaining)" << endl;
//#endif
}




/** font setter */
void FontMesh::setFont(shared_ptr<Font> font)
{
	this->font = font;
}
/** font getter */
shared_ptr<Font> FontMesh::getFont()
{
	return font;
}

/** text setter */
void FontMesh::setText(string text)
{
	this->text = text;

	createMesh();
}
/** text getter */
string FontMesh::getText()
{
	return text;
}


/** create the mesh according to the font and text */
void FontMesh::createMesh()
{
	mesh = make_shared<Mesh>();

	float letterWidth = 0.5f;
	float letterHeight = 0.5f;



	float xOffset = 0;

	for (int i = 0; i < text.size(); i++)
	{
		char c = text[i];

		LetterFontUV letterUV = font->getCharDesc(c);

		letterWidth = letterHeight * letterUV.ratio;
		/*letterWidth *= letterUV.widthRatioToMax;
		letterHeight *= letterUV.heightRatioToMax;*/

		int i0, i1, i2, i3;
		glm::vec3 p0, p1, p2, p3;

		p0 = glm::vec3(xOffset, 0, 0);
		p1 = glm::vec3(xOffset+letterWidth, 0, 0);
		p2 = glm::vec3(xOffset + letterWidth, letterHeight, 0);
		p3 = glm::vec3(xOffset, letterHeight, 0);

		mesh->addVertex(p0, letterUV.bottomLeft, glm::vec3(0, 0, -1)); //i
		mesh->addVertex(p1, glm::vec2(letterUV.topRight.x, letterUV.bottomLeft.y), glm::vec3(0, 0, -1)); //i+1
		mesh->addVertex(p2, letterUV.topRight, glm::vec3(0, 0, -1)); //i+2
		mesh->addVertex(p3, glm::vec2(letterUV.bottomLeft.x, letterUV.topRight.y), glm::vec3(0, 0, -1)); //i+3

		mesh->addTriangle(i * 4);
		mesh->addTriangle(i * 4+1);
		mesh->addTriangle(i * 4+3);

		mesh->addTriangle(i * 4+3);
		mesh->addTriangle(i * 4+1);
		mesh->addTriangle(i * 4+2);

		xOffset += letterWidth;
	}

	mesh->createBuffers3();
}
/** Get a description for the current component*/
shared_ptr<ComponentDescription> FontMesh::getComponentDescription()
{
	return nullptr;
}
/** Deserialize a component description to a collider */
void FontMesh::deserialize(shared_ptr<ComponentDescription> desc)
{

}
