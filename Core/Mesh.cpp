/**
 *  Source file for the Mesh class header
*/

#include "Mesh.hpp"
#include <cmath>

std::vector<float> createCubeVertices()
{
    return std::vector<float> {
        1.0f,   -1.0f,  -1.0f,
        -1.0f,  -1.0f,  -1.0f,
        -1.0f,  -1.0f,  1.0f,
        1.0f,   -1.0f,  1.0f,
        1.0f,   1.0f,   -1.0f,
        -1.0f,  1.0f,   -1.0f,
        -1.0f,  1.0f,   1.0f,
        1.0f,   1.0f,   1.0f
    };
}

std::vector<unsigned int> createCubeIndices()
{
    return std::vector<unsigned int> {
        0,  2,  1,
        0,  3,  2,
        3,  7,  2,
        7,  6,  2,
        0,  7,  3,
        4,  7,  0,
        4,  6,  7,
        4,  5,  6,
        0,  5,  4,
        1,  5,  0,
        1,  6,  5,
        1,  2,  6
    };
}

ObjectData createCube()
{
    ObjectData ret;
    ret.indices = createCubeIndices();
    ret.vertices = createCubeVertices();

    return ret;
}

// functions for creating a sphere
// *** TODO - not working yet

void appendTierOfVertices(std::vector<float>& vertices, float altitudeAngle, float offset)
{
    float dAngle = 3.141592 / 12;

    for(float angle = offset; angle < 2 * 3.14158 + offset; angle += dAngle)
    {
        vertices.push_back(std::sin(altitudeAngle) * std::cos(angle));
        vertices.push_back(std::sin(altitudeAngle) * std::sin(angle));
        vertices.push_back(std::cos(altitudeAngle));
    }
}

void appendBottomVertex(std::vector<float>& vertices)
{
    vertices.push_back(0.0f);
    vertices.push_back(0.0f);
    vertices.push_back(-1.0f);
}

std::vector<float> createSphereVertices()
{
    float dAngle = 3.141592 / 12;
    std::vector<float> ret;

    float angle = 0.0f;
    while(angle < 3.14158)
    {
        appendTierOfVertices(ret, angle, 0.0f);
        angle += dAngle;
        appendTierOfVertices(ret, angle, 3.14159 / 2);
        angle += dAngle;
    }
    
    appendBottomVertex(ret);

    return ret;
}

std::vector<unsigned int> createTopSphereIndexTier()
{
    std::vector<unsigned int> ret;

    for(unsigned int i = 0; i != 12; ++i)
    {
        ret.push_back(i + 1);
        ret.push_back(i == 11 ? 1 : i + 2);
        ret.push_back(0);
    }

    return ret;
}

std::vector<unsigned int> createBottomSphereIndexTier()
{
    std::vector<unsigned int> ret;

    for(unsigned int i = 0; i != 12; ++i)
    {
        ret.push_back(145);
        ret.push_back(133 + i);
        ret.push_back(i == 11 ? 133 : 134 + i);
    }

    return ret;
}

std::vector<unsigned int> createSphereIndexTierAt(unsigned int tier)
{
    unsigned int first = 12*tier + 13;
    std::vector<unsigned int> ret;

    for(unsigned int i = 0; i != 12; ++i)
    {
        ret.push_back(first + i);
        ret.push_back(first + 1 + i);
        ret.push_back(first - 12 + i);
    }
    
    return ret;
}

std::vector<unsigned int> createSphereIndexTier(unsigned int tier)
{
    std::vector<unsigned int> ret;

    if(tier == 0)
    {
        ret = createTopSphereIndexTier();
    }
    else if(tier == 11)
    {
        ret = createBottomSphereIndexTier();
    }
    else if (tier < 11 && tier > 0)
    {
        ret = createSphereIndexTierAt(tier);
    }

    return ret;
}

std::vector<unsigned int> createSphereIndices()
{
    std::vector<unsigned int> ret;

    for(unsigned int i = 0; i != 12; ++i)
    {
        std::vector<unsigned int> indices = createSphereIndexTier(i);
        std::copy(indices.begin(), indices.end(), std::back_inserter(ret));
    }

    return ret;
}

ObjectData createSphere()
{
    ObjectData ret;
    ret.indices = createSphereIndices();
    ret.vertices = createSphereVertices();
    
    return ret;
}

// create icosahedron

std::vector<float> createIcoVertices()
{

    // define the vertices for an icosahedron
    std::vector<float> vertices(12*3, 0.0f);
    // top vertex
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 1.0f;
    // bottom vertex
    vertices[33] = 0.0f;
    vertices[34] = 0.0f;
    vertices[35] = -1.0f;
    // and the rest
    static float dAngle = 2 * 3.14159 / 5;
    size_t vertexIndex = 3;     // start filling from 3rd vertex
    for(size_t i = 0; i != 5; ++i)
    {
        vertices[vertexIndex] = std::cos(dAngle * i) * std::sin(dAngle);
        vertices[vertexIndex + 15] = std::cos(dAngle * (i + 0.5)) * std::sin(dAngle);
        ++vertexIndex;
        vertices[vertexIndex] = std::sin(dAngle * i) * std::sin(dAngle);
        vertices[vertexIndex + 15] = std::sin(dAngle * (i + 0.5)) * std::sin(dAngle);
        ++vertexIndex;
        vertices[vertexIndex] = 1.0 - std::cos(dAngle);
        vertices[vertexIndex + 15] = - 1.0 + std::cos(dAngle);;
        ++vertexIndex;
    }

    return vertices;
}

std::vector<unsigned int> createIcoIndices()
{
    // now fill the indices
    std::vector<unsigned int> indices(20 * 3, 0);
    size_t triangleIndex = 0;   // counts the number of triangles filled so far
    // top five
    for(size_t i = 0; i != 5; ++i)
    {
        indices[3 * triangleIndex] = 0;
        indices[3 * triangleIndex + 1] = i + 1;
        indices[3 * triangleIndex + 2] = i != 4 ? i + 2 : 1;        // hacky :-/
        ++triangleIndex;
    }
    // middle stip
    for(size_t i = 0; i != 5; ++i)
    {
        indices[3 * triangleIndex] = i + 1;
        indices[3 * triangleIndex + 1] = i != 4 ? i + 2 : 1;
        indices[3 * triangleIndex + 2] = 6 + i;
        ++triangleIndex;
        indices[3 * triangleIndex] = i == 0 ? 10 : i + 5;
        indices[3 * triangleIndex + 1] = i + 6;
        indices[3 * triangleIndex + 2] = i + 1;
        ++triangleIndex;
    }
    //bottom
    for(size_t i = 0; i != 5; ++i)
    {
        indices[3 * triangleIndex] = 11;
        indices[3 * triangleIndex + 1] = i + 6;
        indices[3 * triangleIndex + 2] = i != 4 ? i + 7 : 6;        // hacky :-/
        ++triangleIndex;
    }

    return indices;
}

ObjectData createIcosahedron()
{
    ObjectData ret;
    ret.indices = createIcoIndices();
    ret.vertices = createIcoVertices();

    return ret;
}

std::unique_ptr<Mesh> Mesh::createMesh(MeshID meshID)
{
    std::unique_ptr<Mesh> ret = nullptr;

    switch(meshID)
    {
        case MeshID::CUBE:
            ret = std::unique_ptr<Mesh>(new Cube);
            break;
        
        case MeshID::SPHERE:
            ret = std::unique_ptr<Mesh>(new Sphere);
            break;
        
        case MeshID::ICOSAHEDRON:
            ret = std::unique_ptr<Mesh>(new Icosahedron);
            break;
    }

    return ret;
}

ObjectData Sphere::createObjectData()
{
    return createSphere();
}


ObjectData Cube::createObjectData()
{
    return createCube();
}


ObjectData Icosahedron::createObjectData()
{
    return createIcosahedron();
}

