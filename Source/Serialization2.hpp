#pragma once

#include <fstream>
#include "Module.hpp"
//#include "StaticCounter.h"
#include <vector>
#include <glm/common.hpp>
// include headers that implement a archive in simple text format
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/serialization/map.hpp>
#include <boost/serialization/base_object.hpp>
#include <boost/serialization/export.hpp>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/shared_ptr.hpp>
#include <boost/serialization/weak_ptr.hpp>
#include <boost/serialization/unique_ptr.hpp>
#include <boost/serialization/shared_ptr_helper.hpp>
#include <boost/serialization/shared_ptr_132.hpp>

//#include <boost/serialization/
#include "AssetDatabase.hpp"
#include "Actor.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include <memory>
#include "print.hpp"
#include "Texture.hpp"
#include "Font.hpp"
#include "Component.hpp"
#include "MeshComponent.hpp"
#include "MeshFilter.hpp"
#include "MeshRenderer.hpp"
#include "Collider.hpp"
#include "BoxCollider.hpp"
#include "SphereCollider.hpp"
#include "CapsuleCollider.hpp"
#include "PhysicsMaterial.hpp"
#include "RigidBody.hpp"
#include "RigidStatic.hpp"
#include "FontMesh.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "ScriptComponent.hpp"

#include <iostream>

#include "SerializationStructs.hpp"

namespace boost {
    namespace serialization {
        
        /** STRUCTS SERIALIZATION **/
        template<class Archive>
        void serialize(Archive & ar, PxVec3 & v, const unsigned int version)
        {
            
            ar & v.x;
            ar & v.y;
            ar & v.z;
            
        }
        
        template<class Archive>
        void serialize(Archive & ar, glm::vec3 & v, const unsigned int version)
        {
            ar & v.x;
            ar & v.y;
            ar & v.z;
            
        }
        
        template<class Archive>
        void serialize(Archive & ar, glm::quat & v, const unsigned int version)
        {
            ar & v.w;
            ar & v.x;
            ar & v.y;
            ar & v.z;
            
        }
        
        template<class Archive>
        void serialize(Archive & ar, glm::vec2 & v, const unsigned int version)
        {
            static int myCont = 0;
            ar & v.x;
            ar & v.y;
            myCont++;
            
            cout << myCont << endl;
        }
        
        template<class Archive>
        void save(Archive & ar,const MeshVertex & mv, const unsigned int version)
        {
            //          string desc = "pos";
            //        ar & desc;
            ar & mv.position;
            //       desc = "uv";
            //       ar & desc;
            ar & mv.uv;
            //       desc = "normal";
            //       ar & desc;
            ar & mv.normal;
        }
        
        template<class Archive>
        void load(Archive & ar, MeshVertex & mv, const unsigned int version)
        {
            //           string desc;
            //         ar & desc;
            ar & mv.position;
            //       ar & desc;
            ar & mv.uv;
            //     ar & desc;
            ar & mv.normal;
            
            //MeshVertex m(mv);
            
            //std::cout << mv.position.x << " " << mv.position.y << " " << mv.position.z << endl;;// << " " << m.uv << " " << m.normal;
        }
        
        template <class Archive>
        void serialize(Archive & ar, MeshVertex & meshVertex, const unsigned int version)
        {
            boost::serialization::split_free(ar, meshVertex, version);
        }
        /** END STRUCTS SERIALIZATION **/
        
        
        
        /** ASSET SERIALIZATION **/
        
        template<class Archive>
        void save(Archive & ar, const Asset & asset, const unsigned int version)
        {
			unsigned int id = asset.getAssetID();
			ar & id;
        }
        template<class Archive>
        void load(Archive & ar, Asset & asset, const unsigned int version)
        {
			int assetID;
			ar & assetID;
			asset.setAssetID(assetID);
            
        }
        
        template <class Archive>
        void serialize(Archive & ar, Asset & asset, const unsigned int version)
        {
            
            boost::serialization::split_free(ar, asset, version);
            
        }
        
        
        template<class Archive>
        void load(Archive & ar, Mesh & mesh, const unsigned int version)
        {
			ar & boost::serialization::base_object<Asset>(mesh);
            ar & mesh.triangles;
            ar & mesh.meshVertices;
            ar & mesh.scaleFactor;
            ar & mesh.boundsMin;
            ar & mesh.boundsMax;
            ar & mesh.avgCenter;
            
            
            mesh.createBuffers();
        }
        template<class Archive>
        void save(Archive & ar,const Mesh & mesh, const unsigned int version)
        {
            
            ar & boost::serialization::base_object<Asset>(mesh);
            ar & mesh.triangles;
            ar & mesh.meshVertices;
            ar & mesh.scaleFactor;
            ar & mesh.boundsMin;
            ar & mesh.boundsMax;
            ar & mesh.avgCenter;
        }
        template <class Archive>
        void serialize(Archive & ar, Mesh & mesh, const unsigned int version)
        
        {
            
            boost::serialization::split_free(ar, mesh, version);
            
        }
        
        
        template<class Archive>
        void save(Archive & ar, const Shader & shader, const unsigned int version)
        {
            ar & boost::serialization::base_object<Asset>(shader);
            
            ar & shader.vsFilename;
            ar & shader.fsFilename;
        }
        template<class Archive>
        void load(Archive & ar, Shader & shader, const unsigned int version)
        {
            ar & boost::serialization::base_object<Asset>(shader);
            
            ar & shader.vsFilename;
            ar & shader.fsFilename;
            
            shader.LoadShaders();
        }
        
        template <class Archive>
        void serialize(Archive & ar, Shader & shader, const unsigned int version)
        {
            boost::serialization::split_free(ar, shader, version);
        }
        
        
        template<class Archive>
        void save(Archive & ar, const Material & mat, const unsigned int version)
        {
            ar & boost::serialization::base_object<Asset>(mat);
            
			unsigned int id = mat.getShader()->getAssetID();
            //ar & mat.shader->getAssetID();
			ar & id;
            
            
        }
        template<class Archive>
        void load(Archive & ar, Material & mat, const unsigned int version)
        {
            ar & boost::serialization::base_object<Asset>(mat);
            
            unsigned int shaderID;
            
            ar & shaderID;
            
            mat.setShader(AssetDatabase::getAsset<Shader>(shaderID));
        }
        template<class Archive>
        void serialize(Archive & ar, Material & mat, const unsigned int version)
        {
            boost::serialization::split_free(ar, mat, version);
        }
        
        
        template<class Archive>
        void save(Archive & ar, const Font & font, const unsigned int version)
        {
            ar & boost::serialization::base_object<Asset>(font);
            
   			unsigned int textureID = font.getFontTexture()->getAssetID();
            
			ar & textureID;
            
            
        }
        template<class Archive>
        void load(Archive & ar, Font & font, const unsigned int version)
        {
            ar & boost::serialization::base_object<Asset>(font);
            
   			unsigned int textureID;
            
            ar & textureID;
            
            font.setFontTexture(AssetDatabase::getAsset<Texture>(textureID));
            
        }
        template<class Archive>
        void serialize(Archive & ar, Font & font, const unsigned int version)
        {
            boost::serialization::split_free(ar, font, version);
        }
        /** END ASSET SERIALIZATION **/
        
        
        /** SERIALIZATION FROM DESCRIPTION **/
        template<class Archive>
        void serialize(Archive & ar, ActorDescription & actorDescription, const unsigned int version)
        {
            ar & actorDescription.name;
            
            ar & actorDescription.editorFlag;
            
            ar & actorDescription.isActive;
            
            ar & actorDescription.transform;
            
            ar & actorDescription.components;
            
            ar & actorDescription.children;
        }
        
        template<class Archive>
        void serialize(Archive & ar, TransformDescription & transformDescription, const unsigned int version)
        {
            
            ar & transformDescription.position;
            
            ar & transformDescription.scale;
            
            ar & transformDescription.rotation;
            
        }
        
        template<class Archive>
        void serialize(Archive & ar, ComponentDescription & componentDescription, const unsigned int version)
        {
            ar & componentDescription.type;
        }
        
        template<class Archive>
        void serialize(Archive & ar, MeshFilterDescription & meshFilterDesc, const unsigned int version)
        {
            
            ar & boost::serialization::base_object<ComponentDescription>(meshFilterDesc);
            ar & meshFilterDesc.meshID;
            
            
        }
        
        
        template<class Archive>
        void serialize(Archive & ar, MeshRendererDescription & meshRendererDesc, const unsigned int version)
        {
            ar & boost::serialization::base_object<ComponentDescription>(meshRendererDesc);
            ar & meshRendererDesc.materialID;
        }
        template<class Archive>
        void serialize(Archive & ar, CameraDescription & cameraDesc, const unsigned int version)
        {
            ar & boost::serialization::base_object<ComponentDescription>(cameraDesc);
            ar & cameraDesc.nearClipPlane;
            ar & cameraDesc.farClipPlane;
            ar & cameraDesc.ratio;
            ar & cameraDesc.fov;
        }
        template<class Archive>
        void serialize(Archive & ar, LightDescription & lightDesc, const unsigned int version)
        {
            ar & boost::serialization::base_object<ComponentDescription>(lightDesc);
            ar & lightDesc.color;
            
        }
        template<class Archive>
        void serialize(Archive & ar, RigidBodyDescription & rigidBodyDesc, const unsigned int version)
        {
            ar & boost::serialization::base_object<ComponentDescription>(rigidBodyDesc);
            ar & rigidBodyDesc.isKinematic;
            ar & rigidBodyDesc.lockConstraints;
            ar & rigidBodyDesc.gravityEnabled;
            
            
        }
        template<class Archive>
        void serialize(Archive & ar, RigidStaticDescription & rigidStaticDesc, const unsigned int version)
        {
            ar & boost::serialization::base_object<ComponentDescription>(rigidStaticDesc);
        }
        
        template<class Archive>
        void serialize(Archive & ar, ColliderDescription & col, const unsigned int version)
        {
            ar & col.center;
            ar & col.isTrigger;
            ar & col.isQueryOnly;
        }
        template<class Archive>
        void serialize(Archive & ar, BoxColliderDescription & boxColDesc, const unsigned int version)
        {
            ar & boost::serialization::base_object<ComponentDescription>(boxColDesc);
            ar & boxColDesc.halfExtent;
        }
        template<class Archive>
        void serialize(Archive & ar, SphereColliderDescription & sphereColDesc, const unsigned int version)
        {
            ar & boost::serialization::base_object<ComponentDescription>(sphereColDesc);
            ar & sphereColDesc.radius;
        }
        template<class Archive>
        void serialize(Archive & ar, CapsuleColliderDescription & capsuleColDesc, const unsigned int version)
        {
            ar & boost::serialization::base_object<ComponentDescription>(capsuleColDesc);
            ar & capsuleColDesc.halfHeight;
            ar & capsuleColDesc.radius;
        }
        template<class Archive>
        void serialize(Archive & ar, FontMeshDescription & fontMeshDesc, const unsigned int version)
        {
            ar & boost::serialization::base_object<ComponentDescription>(fontMeshDesc);
            ar & fontMeshDesc.text;
            ar & fontMeshDesc.fontID;
        }
        /** END SERIALIZATION FROM DESCRIPTION **/
        
        /** SERIALIZATION FROM POINTERS **/
        template<class Archive>
        void save(Archive & ar, const Actor & actor, const unsigned int version)
        {
            string name = actor.name;
            bool isActive = actor.getIsActive();
            bool editorFlag = actor.getEditorFlag();
		
            ar & name;
            ar & isActive;
            ar & editorFlag;
            ar & actor.transform;
            ar & actor.components;
            
        }
        template<class Archive>
        void load(Archive & ar, Actor & actor, const unsigned int version)
        {
            string name;
            bool isActive;
            bool editorFlag;
            ar & name;
		    ar & isActive;
            ar & editorFlag;
            ar & actor.transform;
            
//            vector<std::shared_ptr<Component>> components;
//            ar & components;
            ar & actor.components;
            

//            actor.setComponents(components);
            actor.name = name;
            actor.isActive = isActive;
            actor.editorFlag = editorFlag;
        }
        
        template <class Archive>
        void serialize(Archive & ar, Actor & actor, const unsigned int version)
        {
            
            boost::serialization::split_free(ar, actor, version);
            
        }
        
        template<class Archive>
        void save(Archive & ar, const Transform & transform, const unsigned int version)
        {
            
			ar & transform.position;
   			ar & transform.rotation;
   			ar & transform.scale;
            
            ar & transform.actor;
            
        }
        template<class Archive>
        void load(Archive & ar,  Transform & transform, const unsigned int version)
        {
            glm::vec3 position, scale;
            glm::quat rotation;
            
			ar & position;
            ar & rotation;
            ar & scale;
            
            transform.setPosition(position);
            transform.setRotation(rotation);
            transform.setScale(scale);
            
            ar & transform.actor;
        }
        
        template <class Archive>
        void serialize(Archive & ar,  Transform & transform, const unsigned int version)
        {
            
            boost::serialization::split_free(ar, transform, version);
            
        }
        
        template<class Archive>
        void save(Archive & ar, const Component & component, const unsigned int version)
        {
            ar & component.actor;
            
        }
        template<class Archive>
        void load(Archive & ar,  Component & component, const unsigned int version)
        {
            ar & component.actor;
            
            component.setCopyMode(true);
        }
        
        template <class Archive>
        void serialize(Archive & ar,  Component & component, const unsigned int version)
        {
            
            boost::serialization::split_free(ar, component, version);
            
        }
        
        
        template<class Archive>
        void save(Archive & ar, const MeshComponent & meshComponent, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(meshComponent);
            unsigned int id =meshComponent.getMesh()->getAssetID();
            ar & id;
            
        }
        template<class Archive>
        void load(Archive & ar,  MeshComponent & meshComponent, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(meshComponent);
            
            unsigned int id;
            ar & id;
            meshComponent.setMesh(AssetDatabase::getAsset<Mesh>(id));
        }
        
        template <class Archive>
        void serialize(Archive & ar,  MeshComponent & meshComponent, const unsigned int version)
        {
            boost::serialization::split_free(ar, meshComponent, version);
        }
        
        
        template<class Archive>
        void save(Archive & ar, const MeshFilter & meshFilter, const unsigned int version)
        {
            ar & boost::serialization::base_object<MeshComponent>(meshFilter);
            
            
        }
        template<class Archive>
        void load(Archive & ar,  MeshFilter & meshFilter, const unsigned int version)
        {
            
            ar & boost::serialization::base_object<MeshComponent>(meshFilter);
            
        }
        
        template <class Archive>
        void serialize(Archive & ar,  MeshFilter & meshFilter, const unsigned int version)
        {
            
            boost::serialization::split_free(ar, meshFilter, version);
            
        }
        
        template<class Archive>
        void save(Archive & ar, const MeshRenderer & meshRenderer, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(meshRenderer);
            unsigned int id =meshRenderer.getMaterial()->getAssetID();
            ar & id;
            
        }
        template<class Archive>
        void load(Archive & ar,  MeshRenderer & meshRenderer, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(meshRenderer);
            
            unsigned int id;
            ar & id;
            meshRenderer.setMaterial(AssetDatabase::getAsset<Material>(id));
        }
        
        template <class Archive>
        void serialize(Archive & ar,  MeshRenderer & meshRenderer, const unsigned int version)
        {
            boost::serialization::split_free(ar, meshRenderer, version);
        }
        
        
        
        
        
        
        
        
        template<class Archive>
        void save(Archive & ar, const Collider & collider, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(collider);
            unsigned int id = collider.getPhysicsMaterial()->getAssetID();
            bool isQueryOnly = collider.getQueryOnly();
            bool isTrigger = collider.getIsTrigger();
            PxVec3 center = collider.getCenter();
            
            
            ar & id;
            ar & isQueryOnly;
            ar & isTrigger;
            ar & center;
            
        }
        template<class Archive>
        void load(Archive & ar,  Collider & collider, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(collider);
            
            unsigned int id;
            bool isQueryOnly;
            bool isTrigger;
            PxVec3 center;
            
            ar & id;
            ar & isQueryOnly;
            ar & isTrigger;
            ar & center;
            
            collider.setPhysicsMaterial(AssetDatabase::getAsset<PhysicsMaterial>(id));
            collider.setIsTrigger(isTrigger);
            collider.setQueryOnly(isQueryOnly);
            collider.setCenter(center);
        }
        
        template <class Archive>
        void serialize(Archive & ar,  Collider & collider, const unsigned int version)
        {
            boost::serialization::split_free(ar, collider, version);
        }
        
        
        
        
        
        
        template<class Archive>
        void save(Archive & ar, const BoxCollider & boxCollider, const unsigned int version)
        {
            ar & boost::serialization::base_object<Collider>(boxCollider);
            
            PxVec3 halfExtent =boxCollider.getHalfExtent();
            
            ar & halfExtent;
            
        }
        template<class Archive>
        void load(Archive & ar,  BoxCollider & boxCollider, const unsigned int version)
        {
            ar & boost::serialization::base_object<Collider>(boxCollider);
            
            PxVec3 halfExtent;
            
            ar & halfExtent;
            
            boxCollider.setHalfExtent(halfExtent);
            
        }
        
        template <class Archive>
        void serialize(Archive & ar,  BoxCollider & boxCollider, const unsigned int version)
        {
            boost::serialization::split_free(ar, boxCollider, version);
        }
        
        
        
        
        
        
        template<class Archive>
        void save(Archive & ar, const SphereCollider & sphereCollider, const unsigned int version)
        {
            ar & boost::serialization::base_object<Collider>(sphereCollider);
            
            float radius = sphereCollider.getRadius();
            ar & radius;
            
        }
        template<class Archive>
        void load(Archive & ar,  SphereCollider & sphereCollider, const unsigned int version)
        {
            ar & boost::serialization::base_object<Collider>(sphereCollider);
            
            float radius;
            
            ar & radius;
            
            sphereCollider.setRadius(radius);
        }
        
        template <class Archive>
        void serialize(Archive & ar,  SphereCollider & sphereCollider, const unsigned int version)
        {
            boost::serialization::split_free(ar, sphereCollider, version);
        }
        
        
        
        
        
        
        template<class Archive>
        void save(Archive & ar, const CapsuleCollider & capsuleCollider, const unsigned int version)
        {
            ar & boost::serialization::base_object<Collider>(capsuleCollider);
            
            float height =capsuleCollider.getHeight();
            float radius = capsuleCollider.getRadius();
            RotateAxis axis = capsuleCollider.getOrientation();
            
            ar & height;
            ar & radius;
            ar & axis;
            
            
        }
        template<class Archive>
        void load(Archive & ar,  CapsuleCollider & capsuleCollider, const unsigned int version)
        {
            ar & boost::serialization::base_object<Collider>(capsuleCollider);
            
            float height;
            float radius;
            RotateAxis axis;
            
            ar & height;
            ar & radius;
            ar & axis;
            
            capsuleCollider.setHeight(height);
            capsuleCollider.setRadius(radius);
            capsuleCollider.setOrientation(axis);
        }
        
        template <class Archive>
        void serialize(Archive & ar,  CapsuleCollider & capsuleCollider, const unsigned int version)
        {
            boost::serialization::split_free(ar, capsuleCollider, version);
        }
        
        
        
        
        
        
        
        
        
        
        
        template<class Archive>
        void save(Archive & ar, const RigidBody & rigidBody, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(rigidBody);
            
            int lockConstraints  =rigidBody.getConstraintsFlags();
            bool isKinematic  =rigidBody.getKinematic();
            bool gravityEnabled  =rigidBody.getGravity();
            
            
            
            ar & lockConstraints;
            ar & isKinematic;
            ar & gravityEnabled;
            
            
        }
        template<class Archive>
        void load(Archive & ar,  RigidBody & rigidBody, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(rigidBody);
            
            int lockConstraints;
            bool isKinematic;
            bool gravityEnabled;
            
            ar & lockConstraints;
            ar & isKinematic;
            ar & gravityEnabled;
            
            rigidBody.setConstraintsFlags(lockConstraints);
            rigidBody.setKinematic(isKinematic);
            rigidBody.setGravity(gravityEnabled);
        }
        
        template <class Archive>
        void serialize(Archive & ar,  RigidBody & rigidBody, const unsigned int version)
        {
            boost::serialization::split_free(ar, rigidBody, version);
        }
        
        
        
        
        
        
        
        template<class Archive>
        void save(Archive & ar, const RigidStatic & rigidStatic, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(rigidStatic);
            
        }
        template<class Archive>
        void load(Archive & ar,  RigidStatic & rigidStatic, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(rigidStatic);
            
        }
        
        template <class Archive>
        void serialize(Archive & ar,  RigidStatic & rigidStatic, const unsigned int version)
        {
            boost::serialization::split_free(ar, rigidStatic, version);
        }
        
        
        
        
        template<class Archive>
        void save(Archive & ar, const Camera & camera, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(camera);
            
            float nearClipPlane = camera.getNearClip();
            float farClipPlane = camera.getFarClip();
            float fov = camera.getFOV();
            float ratio = camera.getScreenRatio();
            
            ar & nearClipPlane;
            ar & farClipPlane;
            ar & fov;
            ar & ratio;
            
        }
        template<class Archive>
        void load(Archive & ar,  Camera & camera, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(camera);
            
            float nearClipPlane;
            float farClipPlane;
            float fov;
            float ratio;
            
            ar & nearClipPlane;
            ar & farClipPlane;
            ar & fov;
            ar & ratio;
            
            
            camera.setNearClip(nearClipPlane);
            camera.setFarClip(farClipPlane);
            camera.setFOV(fov);
            camera.setScreenRatio(ratio);
        }
        
        template <class Archive>
        void serialize(Archive & ar,  Camera & camera, const unsigned int version)
        {
            boost::serialization::split_free(ar, camera, version);
        }
        
        
        
        
        
        
        
        template<class Archive>
        void save(Archive & ar, const FontMesh & fontMesh, const unsigned int version)
        {
            ar & boost::serialization::base_object<MeshComponent>(fontMesh);
            
            unsigned int fontID = fontMesh.getFont()->getAssetID();
            string text = fontMesh.getText();
            
            ar & fontID;
            ar & text;
            
        }
        template<class Archive>
        void load(Archive & ar,  FontMesh & fontMesh, const unsigned int version)
        {
            ar & boost::serialization::base_object<MeshComponent>(fontMesh);
            
            unsigned int fontID;
            string text;
            
            ar & fontID;
            ar & text;
            
            
            fontMesh.setFont(AssetDatabase::getAsset<Font>(fontID));
            fontMesh.setText(text);
            
            
        }
        
        template <class Archive>
        void serialize(Archive & ar,  FontMesh & fontMesh, const unsigned int version)
        {
            boost::serialization::split_free(ar, fontMesh, version);
        }
        
        
        
        template<class Archive>
        void save(Archive & ar, const Light & light, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(light);
            
            glm::vec3 color = light.getColor();
            
            ar & color;
            
        }
        template<class Archive>
        void load(Archive & ar,  Light & light, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(light);
            
            glm::vec3 color;
            
            ar & color;
            
            light.setColor(color);
            
        }
        
        template <class Archive>
        void serialize(Archive & ar,  Light & light, const unsigned int version)
        {
            boost::serialization::split_free(ar, light, version);
        }
        
        
        
        
        template<class Archive>
        void save(Archive & ar, const ScriptComponent & scriptComponent, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(scriptComponent);
            
            
        }
        template<class Archive>
        void load(Archive & ar,  ScriptComponent & scriptComponent, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(scriptComponent);
            
            
        }
        
        template <class Archive>
        void serialize(Archive & ar,  ScriptComponent & scriptComponent, const unsigned int version)
        {
            boost::serialization::split_free(ar, scriptComponent, version);
        }
        
        
        
        
        /** END SERIALIZATION FROM POINTERS **/
        
    } // namespace serialization
} // namespace boost
