/**
 *  Source file for the shapeData function header
*/

#include "shapeData.hpp"

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


