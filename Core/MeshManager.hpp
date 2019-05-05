#ifndef GUARD_MESH_MANAGER_HPP
#define GUARD_MESH_MANAGER_HPP

#include <memory>
#include <unordered_map>
#include "Mesh.hpp"
#include "BufferData.hpp"

class MeshManager
{
    public:

        MeshManager();
        std::shared_ptr<BufferData> getMesh(MeshID);
    
    private:

        std::unordered_map<MeshID, std::weak_ptr<BufferData>> meshes;
        
};

#endif