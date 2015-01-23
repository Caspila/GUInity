#pragma once

#include "Component.hpp"
#include "Subject.hpp"

class Font;
class Mesh;
class Material;

class FontRenderer :
	public Component
#ifdef GUINITY_DEBUG
	, public StaticCounter<FontRenderer>, public Subject<FontRenderer>
#endif
{
public:
	FontRenderer();
	virtual ~FontRenderer();


	virtual void init() override;

	void setFont(shared_ptr<Font> font);
	void setText(string text);

	shared_ptr<Material> material;

	shared_ptr<Mesh> mesh;
	shared_ptr<Font> font;
	string text;

	void createMesh();

	virtual shared_ptr<ComponentDescription> getComponentDescription() override;

	virtual shared_ptr<Component> clone() override{ shared_ptr<FontRenderer> compClone = make_shared<FontRenderer>(); return compClone; };

	void deserialize(shared_ptr<ComponentDescription> desc) override;


};

