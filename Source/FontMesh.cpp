#include "FontMesh.hpp"
#include "Mesh.hpp"
#include "Font.hpp"
#include "Actor.hpp"

FontMesh::FontMesh()
{
//#ifdef GUINITY_DEBUG
//	nCount++;
//#endif
}


FontMesh::~FontMesh()
{
//#ifdef GUINITY_DEBUG
//	nCount--;
//	cout << "FontRenderer destroyed (" << nCount << " remaining)" << endl;
//#endif
}


//void FontRenderer::init()
//{
//	FontRenderer::notify(ComponentEventType::NewFontRenderer, shared_from_this(), getActor()->editorFlag);
//}


void FontMesh::setFont(shared_ptr<Font> font)
{
	this->font = font;
}

void FontMesh::setText(string text)
{
	this->text = text;

	createMesh();
}

void FontMesh::createMesh()
{
	//shared_ptr<Mesh> mesh = make_shared<Mesh>();
	mesh = make_shared<Mesh>();

	float letterWidth = 0.5f;
	float letterHeight = 0.5f;

	float xOffset = 0;

	//TODO RIGHTMOST VERTEX ARE DUPLICATED
	for (int i = 0; i < text.size(); i++)
	{
		char c = text[i];

		LetterFontUV letterUV = font->charUVMap[c];

		//letterWidth = letterHeight *1/letterUV.ratio;
		letterWidth = letterHeight * letterUV.ratio;

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

shared_ptr<ComponentDescription> FontMesh::getComponentDescription()
{
	return nullptr;
}

void FontMesh::deserialize(shared_ptr<ComponentDescription> desc)
{

}
