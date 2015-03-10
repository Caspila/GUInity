#pragma once

#include "Component.hpp"
#include "Subject.hpp"
#include "MeshComponent.hpp"

class Font;
class Mesh;
class Material;

/**
	FontMesh is a MeshComponent, meaning that it holds reference to a Mesh.
	Unlike MeshFilter, that makes reference to a "static" mesh, a file mesh, the FontMesh makes reference to a dynamic mesh, created according
	to the text it's going to display.
*/
class FontMesh :
	public MeshComponent
{
private:
	/** The Font asset*/
	shared_ptr<Font> font;
	/** The text */
	string text;
	/** The material used to render the Mesh*/
	shared_ptr<Material> material;

public:
	/** Default Constructor*/
	FontMesh();
	/** Default Destructor. Virtual because it's children class.*/
	virtual ~FontMesh();

	/** font setter */
	void setFont(shared_ptr<Font> font);
	/** font getter */
	shared_ptr<Font> getFont();
	
	/** text setter */
	void setText(string text);
	/** text getter */
	string getText();

	/** create the mesh according to the font and text */
	void createMesh();

	/** Prototype design pattern*/
	virtual shared_ptr<Component> clone() override{ shared_ptr<FontMesh> compClone = make_shared<FontMesh>(); return compClone; };

	/** Serialization region*/
	/** Get a description for the current component*/
	virtual shared_ptr<ComponentDescription> getComponentDescription() override;
	/** Deserialize a component description to a collider */
	void deserialize(shared_ptr<ComponentDescription> desc) override;


};

