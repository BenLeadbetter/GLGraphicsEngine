#ifndef GUARD_OBJECT_DATA_HPP
#define GUARD_OBJECT_DATA_HPP

/*
*       Header file for the object data struct
*/

#include <vector>

struct ObjectData
{
    std::vector<float>  vertices;
    std::vector<unsigned int>    indices;
};



#endif