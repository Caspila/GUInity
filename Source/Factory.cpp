#include "Factory.hpp"
#include "Actor.hpp"
#include "Transform.hpp"
//#include "Script.hpp"
#include "ScriptComponent.hpp"
#include "RigidStatic.hpp"
#include "SphereCollider.hpp"
#include "BoxCollider.hpp"
#include "CapsuleCollider.hpp"
#include "EditorCollider.hpp"
#include "MeshFilter.hpp"
#include "MeshRenderer.hpp"
#include "SerializationStructs.hpp"
#include "Camera.hpp"
#include "RigidBody.hpp"
#include "RigidStatic.hpp"
#include "Light.hpp"
#include "World.hpp"
#include "FontMesh.hpp"

/**  The model of each Component for the Prototype Design Pattern. */
vector<shared_ptr<Component>> Factory::prototypes =
{make_shared<MeshFilter>(),
make_shared<MeshRenderer>(),
make_shared<Camera>(),
make_shared<RigidBody>(),
make_shared<RigidStatic>(),
make_shared<Light>(),
make_shared<BoxCollider>(),
make_shared<SphereCollider>(),
make_shared<CapsuleCollider>(),
make_shared<FontMesh>()};


/** Deserialize a list of Components and attaches them to an Actor */
void Factory::DeserializeComponents(shared_ptr<Actor> actor, vector<shared_ptr<ComponentDescription>> compDescs)
{
    for(auto& x: compDescs)
    {
        shared_ptr<Component> comp = prototypes[x->type]->clone();
        comp->deserialize(x);
        actor->addComponent(comp);
    }
        
}

/** Deserialize an Actor*/
shared_ptr<Actor> Factory::DeserializeActor(ActorDescription& desc)
{
    shared_ptr<Actor> actor = desc.editorFlag ?
    Factory::CreateEditorActor(desc.name) :
    Factory::CreateActor(desc.name);
    
    actor->transform->rotation = desc.transform.rotation;
    actor->transform->scale = desc.transform.scale;
    actor->transform->position = desc.transform.position;
    
    DeserializeComponents(actor,desc.components);
    
    for(auto& x: desc.children)
    {
        actor->addChildren(DeserializeActor(x));
    }
    
    return actor;
}

/** Create a new Actor */
shared_ptr<Actor> Factory::CreateActor(string name)
{
	shared_ptr<Actor> actor = make_shared<Actor>(name);
	actor->transform->setActor(actor);

	actor->setEditorFlag(false);

    notify(ActorEventType::NewActor, actor, false);
    
//    CreateReferenceActor(actor);
    
	return actor;
}

/** Create a new Actor */
void Factory::DestroyActor(weak_ptr<Actor> actor)
{
    shared_ptr<Actor> actorLock = actor.lock();
    if(actorLock)
        notify(ActorEventType::RemovedActor,actorLock,false);
}



/** Create reference actor. Every Actor in the Game World has a Reference Actor in the Editor World to allow them to be manipulated */
void Factory::CreateReferenceActor(shared_ptr<Actor> realActor)
{

    
    shared_ptr<Actor> editorRef = CreateEditorActor(string(realActor->name).append("___editorRef"));
	shared_ptr<EditorCollider> editorCollider = editorRef->AddComponent<EditorCollider>();
	editorCollider->setGameActor(realActor);
	editorRef->AddComponent<SphereCollider>();
}

/** Create a new Editor Actor, one that lives only in the Editor World */
shared_ptr<Actor> Factory::CreateEditorActor(string name)
{
	shared_ptr<Actor> actor = make_shared<Actor>(name);
	actor->transform->setActor(actor);

	actor->setEditorFlag(true);

	notify(ActorEventType::NewActor, actor, true);

	return actor;
}

TransformDescription Factory::getTransformDescription(shared_ptr<Transform> t)

{
    return TransformDescription {t->position,t->scale,t->rotation};
}

ActorDescription Factory::getActorDescription(shared_ptr<Actor> actor)
{
    ActorDescription desc;
    
    desc.name = actor->name;
    desc.isActive = actor->getIsActive();
    desc.editorFlag = actor->getEditorFlag();
    desc.transform = getTransformDescription(actor->transform);
    
    desc.components = getActorComponentsDescription(actor);
    
    for(auto &x:actor->children)
    {
        shared_ptr<Actor> childrenLock = x.lock();
        
        desc.children.push_back(getActorDescription(childrenLock));
    }
    
    return desc;

}

vector<shared_ptr<ComponentDescription>> Factory::getActorComponentsDescription(shared_ptr<Actor> actor)
{
    vector<shared_ptr<ComponentDescription>> descs;
    
    for(auto&x : actor->components)
        descs.push_back((x->getComponentDescription()));
    
    return descs;
}
 vector<ActorDescription> Factory::getSceneDescription(shared_ptr<World> world)
{
    vector<ActorDescription> sceneDesc;
    for(auto &x: world->actors)
    {
        sceneDesc.push_back(getActorDescription(x));
    }
    
    return sceneDesc;
}
 void Factory::loadSceneDescription(vector<ActorDescription> sceneDesc)
{
    for(auto &x: sceneDesc)
    {
        DeserializeActor(x);
    }
}
