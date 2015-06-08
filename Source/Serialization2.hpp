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

#include <iostream>

#include "SerializationStructs.hpp"

namespace boost {
    namespace serialization {
        
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
            
            mat.setShader(dynamic_pointer_cast<Shader>(AssetDatabase::getAsset(shaderID)));
        }
        template<class Archive>
        void serialize(Archive & ar, Material & mat, const unsigned int version)
        {
            boost::serialization::split_free(ar, mat, version);
        }

        template<class Archive>
        void serialize(Archive & ar, ActorDescription & actorDescription, const unsigned int version)
        {
            ar & actorDescription.name;
            
            ar & actorDescription.editorFlag;
            
            ar & actorDescription.isActive;
            
            ar & actorDescription.transform;
        }

        template<class Archive>
        void serialize(Archive & ar, TransformDescription & transformDescription, const unsigned int version)
        {
            
            ar & transformDescription.position;
            
            ar & transformDescription.scale;
            
            ar & transformDescription.rotation;
            //boost::serialization::split_free(ar, rigidBody, version);
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
