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


/** Deserialize a list of Components and attaches them to an Actor
 @param[in] actor Actor that will receive the Components
 @param[in] compDescs List of ComponentDescription
 */
void Factory::DeserializeComponents(shared_ptr<Actor> actor, vector<shared_ptr<ComponentDescription>> compDescs)
{
    for(auto& x: compDescs)
    {
        shared_ptr<Component> comp = prototypes[x->type]->clone();
        comp->deserialize(x);
        actor->addComponent(comp);
    }
        
}

/** Deserialize an Actor
 @param[in] desc The ActorDescription
 @return The deserialized Actor
 */
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
        actor->addChild(DeserializeActor(x));
    }
    
    return actor;
}

/** Create a new Actor
 @param[in] name Name of the Actor
 @return Reference to the Actor that was created
 */
shared_ptr<Actor> Factory::CreateActor(string name)
{
	shared_ptr<Actor> actor = make_shared<Actor>(name);
	actor->transform->setActor(actor);

	actor->setEditorFlag(false);

    notify(ActorEventType::NewActor, actor, false);
    
//    CreateReferenceActor(actor);
    
	return actor;
}

/** Destroys an Actor
 @param[in] actor Reference to the actor to be destroyed
 */
void Factory::DestroyActor(weak_ptr<Actor> actor)
{
    shared_ptr<Actor> actorLock = actor.lock();
    if(actorLock)
        notify(ActorEventType::RemovedActor,actorLock,false);
}



/** Create reference actor. Every Actor in the Game World has a Reference Actor in the Editor World to allow them to be manipulated in the Editor
 @param[in] realActor Reference to the actor
 */
void Factory::CreateReferenceActor(shared_ptr<Actor> realActor)
{

    
    shared_ptr<Actor> editorRef = CreateEditorActor(string(realActor->name).append("___editorRef"));
	shared_ptr<EditorCollider> editorCollider = editorRef->AddComponent<EditorCollider>();
	editorCollider->setGameActor(realActor);
	editorRef->AddComponent<SphereCollider>();
}

/** Create a new Editor Actor, one that lives only in the Editor World
 @param[in] name Name of the Actor
 @return Reference to the Editor Actor
 */
shared_ptr<Actor> Factory::CreateEditorActor(string name)
{
	shared_ptr<Actor> actor = make_shared<Actor>(name);
	actor->transform->setActor(actor);

	actor->setEditorFlag(true);

	notify(ActorEventType::NewActor, actor, true);

	return actor;
}

/** Gets a ActorDescription from an Actor
 @param[in] actor The Actor
 @return ActorDescription
 */
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


/** Gets a TransformDescription from a Transform
 @param[in] transform The transform
 @return TransformDescription
 */
TransformDescription Factory::getTransformDescription(shared_ptr<Transform> transform)

{
    return TransformDescription {transform->position,transform->scale,transform->rotation};
}

/** Gets a list of ComponentDescriptions for each Component in an Actor
 @param[in] actor The Actor
 @return list of ComponentDescriptions
 */
vector<shared_ptr<ComponentDescription>> Factory::getActorComponentsDescription(shared_ptr<Actor> actor)
{
    vector<shared_ptr<ComponentDescription>> descs;
    
    for(auto&x : actor->components)
        descs.push_back((x->getComponentDescription()));
    
    return descs;
}

/** Gets a list of ActorDescription from a World. Technically it could be used for describing a scene.
 @param[in] world The World
 @return list of ActorDescription
 */
 vector<ActorDescription> Factory::getSceneDescription(shared_ptr<World> world)
{
    vector<ActorDescription> sceneDesc;
    for(auto &x: world->actors)
    {
        sceneDesc.push_back(getActorDescription(x));
    }
    
    return sceneDesc;
}
/** Loads a scene description, deserializing every ActorDescription into new Actors.
 @param[in] sceneDesc The list of ActorDescription
 */
 void Factory::loadSceneDescription(vector<ActorDescription> sceneDesc)
{
    for(auto &x: sceneDesc)
    {
        DeserializeActor(x);
    }
}

/** Notifies when an Actor has been deserialized.
 @param[in] actor The Actor that was deserialized
 */
void Factory::ActorDeserialized(shared_ptr<Actor> actor)
{
    notify(ActorEventType::NewActor, actor, false);

}
