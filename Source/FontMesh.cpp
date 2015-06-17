#include "FontMesh.hpp"
#include "Mesh.hpp"
#include "Font.hpp"
#include "Actor.hpp"
#include "Texture.hpp"
#include "AssetDatabase.hpp"

/** Default Constructor*/
FontMesh::FontMesh():
alignment{FontAlignment::center}
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
shared_ptr<Font> FontMesh::getFont() const
{
	return font;
}

/** text setter */
void FontMesh::setText(string text)
{
    // Do nothing if text is not changed
    if(this->text.compare(text)==0)
        return;
    
	this->text = text;
    
	createMesh();
}

/** text getter */
string FontMesh::getText() const
{
	return text;
}

/** alignment Setter
 @param[in] alignment the new FontAlignment */
void FontMesh::setAlignment(FontAlignment alignment)
{
    if(this->alignment != alignment)
        changeAlignment(this->alignment,alignment);
    
    this->alignment = alignment;
}
/** alignment Getter
 @return the current FontAlignment */
FontAlignment FontMesh::getAlignment() const
{
    return alignment;
}

/** Changes the alignment of the current Mesh */
void FontMesh::changeAlignment(FontAlignment from, FontAlignment to)
{
    float xOffset = 0;
    glm::vec3 bounds = calculateTextBounds(text);
    
    switch(from)
    {
        case FontAlignment::left:
        {
            switch(to)
            {
                case FontAlignment::right:
                    xOffset = -bounds.x;
                    break;
                case FontAlignment::center:
                    xOffset = -bounds.x/2;
                    break;
            }
        }
            break;
            
        case FontAlignment::center:
        {
            switch(to)
            {
                case FontAlignment::left:
                    xOffset = bounds.x/2;
                    break;
                case FontAlignment::right:
                    xOffset = -bounds.x/2;
                    break;
            }
        }
            break;
        case FontAlignment::right:
        {
            switch(to)
            {
                case FontAlignment::right:
                    xOffset = bounds.x/2;
                    break;
                case FontAlignment::center:
                    xOffset = bounds.x/2;
                    break;
            }
        }
            break;
    }
    applyOffsetToMesh(glm::vec3(xOffset,0,0));
}

/** Applies an offset to each vertex of the Mesh
 @param[in] offset The offset that will be applied*/
void FontMesh::applyOffsetToMesh(glm::vec3 offset)
{
    for(auto&vertex : mesh->meshVertices)
    {
        vertex.position += offset;
    }
}



/** Calculate the bounds of a string
 @param[in] text The text that will be used for calculation
 @return The bounding box of the string */
glm::vec3 FontMesh::calculateTextBounds(const string& text)
{
	float letterWidth = 0.5f;
	float letterHeight = 0.5f;
    
	float xOffset = 0;
    
	for (int i = 0; i < text.size(); i++)
	{
		char c = text[i];
        
		LetterFontUV letterUV = font->getCharDesc(c);
        
		letterWidth = letterHeight * letterUV.ratio;
		xOffset += letterWidth;
	}
    
    return glm::vec3(xOffset,0,0);
}


/** create the mesh according to the font and text */
void FontMesh::createMesh()
{
	mesh = make_shared<Mesh>();
    
	float letterWidth = 0.5f;
	float letterHeight = 0.5f;
    
    
    
    glm::vec3 bounds = calculateTextBounds(text);
  	float xOffset = 0;
    switch (alignment)
    {
        case FontAlignment::left:
            break;
        case FontAlignment::right:
            xOffset = -bounds.x;
            break;
        case FontAlignment::center:
            xOffset = -bounds.x/2.0f;
            break;
    }
    
    
	for (int i = 0; i < text.size(); i++)
	{
		char c = text[i];
        
		LetterFontUV letterUV = font->getCharDesc(c);
        
		letterWidth = letterHeight * letterUV.ratio;
		/*letterWidth *= letterUV.widthRatioToMax;
         letterHeight *= letterUV.heightRatioToMax;*/
        
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
    
	mesh->createBuffers();
}

/** Clones current component (Prototype Design Pattern)
 @return shared_ptr to cloned FontMesh Component
 */

shared_ptr<Component> FontMesh::clone()
{
    shared_ptr<FontMesh> compClone = make_shared<FontMesh>();
    
    compClone->setFont(getFont());
    compClone->setText(text);
    
    return compClone;
};

/** Creates a description for the Component*/
shared_ptr<ComponentDescription> FontMesh::getComponentDescription()
{
    return make_shared<FontMeshDescription>(text,font->getAssetID());
}
/** Deserializes a description to a Component */
void FontMesh::deserialize(shared_ptr<ComponentDescription> desc)
{
    shared_ptr<FontMeshDescription> fontMeshDesc = dynamic_pointer_cast<FontMeshDescription>(desc);
    
    setFont(AssetDatabase::getAsset<Font>(fontMeshDesc->fontID));
    
    setText(fontMeshDesc->text);
}

