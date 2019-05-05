/**
 *  Source file for the BufferData class header
*/

#include "BufferData.hpp"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../GL/GLCheckError.hpp"
#define glCheckError() glCheckError_(__FILE__, __LINE__)

void BufferData::createVertexArray()
{
    glGenVertexArrays(1, &VertexArrayID);
    glCheckError();
}

template<typename T>
void BufferData::createElementBuffer(T&& data)
{
    glBindVertexArray(VertexArrayID);
    glGenBuffers(1, &ElementBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ElementBufferID);
    glBufferData(
        GL_ELEMENT_ARRAY_BUFFER,
        sizeof(float) * data.indices.size(),
        std::forward<T>(data).indices.data(),
        GL_STATIC_DRAW
    );

    NumberOfIndices = data.indices.size();

    glCheckError();
}

template void BufferData::createElementBuffer(ObjectData&&);
template void BufferData::createElementBuffer(ObjectData&);

template<typename T>
void BufferData::createVertexBuffer(T&& data)
{
    glBindVertexArray(VertexArrayID);
    glGenBuffers(1, &VertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, VertexBufferID);
    glBufferData(
        GL_ARRAY_BUFFER, 
        sizeof(float) * data.vertices.size(), 
        std::forward<T>(data).vertices.data(),
        GL_STATIC_DRAW
        );
    
    glCheckError();
}

template void BufferData::createVertexBuffer(ObjectData&& data);
template void BufferData::createVertexBuffer(ObjectData& data);

void BufferData::enablePositionAttribPointer()
{
    glBindVertexArray(VertexArrayID);
    glVertexAttribPointer(
        0, 
        3, 
        GL_FLOAT, 
        GL_FALSE, 
        3 * sizeof(float),
        (void*)0
    );
    glEnableVertexAttribArray(0);

    glCheckError();
}

void BufferData::releaseAllBuffers()
{
    glDeleteBuffers(1, &VertexBufferID);
    glDeleteBuffers(1, &ElementBufferID);

    glCheckError();
}

void BufferData::deleteVertexArray()
{
    glDeleteVertexArrays(1, &VertexArrayID);

    glCheckError();
}

template<typename T>
BufferData::BufferData(T&& objectData)
{
    createVertexArray();
    createVertexBuffer(objectData);
    createElementBuffer(std::forward<ObjectData>(objectData));
    enablePositionAttribPointer();
}

template BufferData::BufferData(ObjectData&);
template BufferData::BufferData(ObjectData&&);

BufferData::~BufferData()
{
    releaseAllBuffers();
    deleteVertexArray();
}

unsigned int BufferData::getVertexArrayID() const
{
    return VertexArrayID;
}

unsigned int BufferData::getVertexBufferID() const
{
    return VertexBufferID;
}

unsigned int BufferData::getElementBufferID() const
{
    return ElementBufferID;
}

unsigned int BufferData::getNumberOfIndices() const
{
    return NumberOfIndices;
}
