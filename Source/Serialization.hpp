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
#include <boost/serialization/shared_ptr_helper.hpp>
#include <boost/serialization/shared_ptr_132.hpp>
//#include <boost/serialization/
#include "Actor.hpp"
#include "Component.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"
#include "MeshFilter.hpp"
#include "MeshRenderer.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include "AssetDatabase.hpp"
#include "Factory.hpp"
#include "RigidBody.hpp"
#include "World.hpp"
#include <memory>

#include <iostream>

//Extra to make shared_from_this available inside the saving code
//This works by asking the archive to handle (and therefore create) a shared_ptr for the data
//before the main serialization code runs.
#define ALLOW_SHARED_THIS(type) \
template<class Archive> inline void load_construct_data(Archive &ar, type *obj, const unsigned int file_version) { \
shared_ptr<type> sharedPtr; \
::new(obj)type();/* create instance */ \
ar.reset(sharedPtr, obj); /* Tell the archive to start managing a shared_ptr */ \
}

namespace boost {
    namespace serialization {
        
        template<class Archive>
        void save(Archive & ar, const Asset & asset, const unsigned int version)
        {
            
            ar & asset.assetID;
        }
        template<class Archive>
        void load(Archive & ar, Asset & asset, const unsigned int version)
        {
            ar & asset.assetID;
            
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
            
            mesh.createBuffers3();
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
            ar & v.x;
            ar & v.y;
            
        }
        
        template<class Archive>
        void serialize(Archive & ar, MeshVertex & mv, const unsigned int version)
        {
            ar & mv.position;
            ar & mv.uv;
            ar & mv.normal;
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
        void save(Archive & ar, const AssetDatabase & assetDB, const unsigned int version)
        {
            ar & assetDB.currentID;
            ar & assetDB.idToAsset;
        }
        template<class Archive>
        void load(Archive & ar, AssetDatabase & assetDB, const unsigned int version)
        {
            ar & assetDB.currentID;
            ar & assetDB.idToAsset;
        }
        
        template <class Archive>
        void serialize(Archive & ar, AssetDatabase & assetDB, const unsigned int version)
        {
            boost::serialization::split_free(ar, assetDB, version);
        }
        
        template<class Archive>
        void save(Archive & ar, const Material & mat, const unsigned int version)
        {
            ar & boost::serialization::base_object<Asset>(mat);
            
            ar & mat.shader->assetID;
            
            
        }
        template<class Archive>
        void load(Archive & ar, Material & mat, const unsigned int version)
        {
            ar & boost::serialization::base_object<Asset>(mat);
            
            unsigned int shaderID;
            
            ar & shaderID;
            
            mat.setShader(dynamic_pointer_cast<Shader>(AssetDatabase::idToAsset[shaderID]));
        }
        template<class Archive>
        void serialize(Archive & ar, Material & mat, const unsigned int version)
        {
            boost::serialization::split_free(ar, mat, version);
        }

        
        
        
        template<class Archive>
        void serialize(Archive & ar, Component & c, const unsigned int version)
        {
            ar & c.actor;
        }
        
        template<class Archive>
        void load(Archive & ar, Actor & a, const unsigned int version)
        {
            ar & a.isActive;
            
            ar & a.editorFlag;
            
            ar & a.name;
            
            ar & a.transform;
            
            
            //BOOST_SERIALIZATION_NVP(a.components);
            
            ar & a.components;
            
            ar & a.parent;
            
            ar & a.children;
            
            a.initComponents();
            //actor.notifyNewActorCreated();
            //Factory::CreateReferenceActor(a);
        }
        template<class Archive>
        void save(Archive & ar, const Actor & a, const unsigned int version)
        {
            ar & a.isActive;
            
            ar & a.editorFlag;
            
            ar & a.name;
            
            ar & a.transform;
            
            //BOOST_SERIALIZATION_NVP(a.components);
            
            ar & a.components;
            
            ar & a.parent;
            
            ar & a.children;
            
        }
        template<class Archive>
        void serialize(Archive & ar, Actor & a, const unsigned int version)
        {
            boost::serialization::split_free(ar, a, version);
            
        }
        
        template<class Archive>
        void serialize(Archive & ar, MeshFilter & mFilter, const unsigned int version)
        {
            boost::serialization::split_free(ar, mFilter, version);
            
        }
        template<class Archive>
        void save(Archive & ar, const MeshFilter & mFilter, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(mFilter);
            ar & mFilter.mesh->assetID;
            
        }
        template<class Archive>
        void load(Archive & ar, MeshFilter & mFilter, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(mFilter);
            
            unsigned int assetID;
            
            ar & assetID;
            
            mFilter.setMesh(dynamic_pointer_cast<Mesh>(AssetDatabase::idToAsset[assetID]));
        }
        
        template<class Archive>
        void serialize(Archive & ar, MeshRenderer & mRenderer, const unsigned int version)
        {
            boost::serialization::split_free(ar, mRenderer, version);
        }
        template<class Archive>
        void save(Archive & ar, const MeshRenderer & mRenderer, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(mRenderer);
            
            ar & mRenderer.material;
            
            //std::shared_ptr<Material> myMat =mRenderer.material;
            
            //cout << myMat->assetID;
            
            //ar & mRenderer.material->assetID;
            //ar & mFilter.mesh->assetID;
            
        }
        template<class Archive>
        void load(Archive & ar, MeshRenderer & mRenderer, const unsigned int version)
        {
            ar & boost::serialization::base_object<Component>(mRenderer);
            
            ar & mRenderer.material;
            
//            unsigned int materialID;
//            
//            ar & materialID;
//            
//            mRenderer.setMaterial(dynamic_pointer_cast<Material>(AssetDatabase::idToAsset[materialID]));
        }
        
        
        template<class Archive>
        void serialize(Archive & ar, Transform & transform, const unsigned int version)
        {
            ar & transform.actor;
            ar & transform.position;
            ar & transform.rotationQuat;
            ar & transform.scale;
        }
        
        
        template<class Archive>
        void serialize(Archive & ar, RigidBody & rigidBody, const unsigned int version)
        {
            
            ar & boost::serialization::base_object<Component>(rigidBody);
            //boost::serialization::split_free(ar, rigidBody, version);
        }
        
        template<class Archive>
        void serialize(Archive & ar, World & world, const unsigned int version)
        {
            
            ar & world.actors;
            ar & world.newActors;
            //boost::serialization::split_free(ar, rigidBody, version);
        }
//        template<class Archive>
//        void save(Archive & ar, const RigidBody & rigidBody, const unsigned int version)
//        {
//            ar & boost::serialization::base_object<Component>(rigidBody);
//        }
//        template<class Archive>
//        void load(Archive & ar, RigidBody & rigidBody, const unsigned int version)
//        {
//            ar & boost::serialization::base_object<Component>(rigidBody);            
//            
//        }
        
        
    } // namespace serialization
} // namespace boost
