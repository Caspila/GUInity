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
#include "Actor.hpp"
#include "Component.hpp"
#include "Transform.hpp"
#include "Mesh.hpp"
#include "MeshFilter.hpp"
#include "MeshRenderer.hpp"
#include "Shader.hpp"
#include "Material.hpp"

#include <iostream>



namespace boost {
    namespace serialization {
        
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
        void serialize(Archive & ar, Component & c, const unsigned int version)
        {
            ar & c.actor;
        }
        
        template<class Archive>
        void serialize(Archive & ar, Actor & a, const unsigned int version)
        {
            ar & a.isActive;
            
            ar & a.editorFlag;
            
            ar & a.components;
            
            ar & a.transform;
            
            ar & a.name;
            
            ar & a.parent;
            
            ar & a.children;
            
        }
        
        template<class Archive>
        void serialize(Archive & ar, MeshFilter & mFilter, const unsigned int version)
        {
            ar & mFilter.mesh;
            
        }
        
        template<class Archive>
        void serialize(Archive & ar, MeshRenderer & mRenderer, const unsigned int version)
        {
            ar & mRenderer.material;
            ar & mRenderer.meshFilter;
        }
        
        template<class Archive>
        void save(Archive & ar, const Material & mat, const unsigned int version)
        {
            ar & boost::serialization::base_object<Asset>(mat);

            ar & mat.shader;
        }
        template<class Archive>
        void load(Archive & ar, Material & mat, const unsigned int version)
        {
            ar & boost::serialization::base_object<Asset>(mat);

            ar & mat.shader;
        }
        template<class Archive>
        void serialize(Archive & ar, Material & mat, const unsigned int version)
        {
            boost::serialization::split_free(ar, mat, version);
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
        
        
    } // namespace serialization
} // namespace boost
