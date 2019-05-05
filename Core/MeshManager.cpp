/**
 *  Source file for the MeshManager class header
*/

#include "MeshManager.hpp"
#include <assert.h>

MeshManager::MeshManager()
{
    // insist only one instance
    static bool instantiated = false;

    assert(!instantiated);

    instantiated = true;
}

ObjectData getObjectData(MeshID meshID)
{
    auto meshPtr = Mesh::createMesh(meshID);
    return meshPtr->createObjectData();
}

std::shared_ptr<BufferData> MeshManager::getMesh(MeshID meshID)
{
    if(meshes.find(meshID) == meshes.end())
    {
        auto ret = std::make_shared<BufferData>(getObjectData(meshID));
        std::weak_ptr<BufferData> weakBufferPtr = ret;
        meshes[meshID] = weakBufferPtr;
        return ret;
    }
    else
    {
        return meshes[meshID].lock();
    }   
}