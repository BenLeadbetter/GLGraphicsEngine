#ifndef GUARD_MESH_HPP
#define GUARD_MESH_HPP

#include <memory>
#include "ObjectData.hpp"

enum class MeshID {
    CUBE,
    SPHERE,
    ICOSAHEDRON
    };

class Mesh
{
    public:

        // factory method
        static std::unique_ptr<Mesh> createMesh(MeshID);
        
        //
        virtual ObjectData createObjectData() = 0;
};

class Cube : public Mesh
{
    ObjectData createObjectData();
};


class Sphere : public Mesh
{
    ObjectData createObjectData();
};


class Icosahedron : public Mesh
{
    ObjectData createObjectData();
};

#endif