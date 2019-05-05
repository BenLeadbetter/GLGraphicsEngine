#ifndef GUARD_BUFFER_DATA_HPP
#define GUARD_BUFFER_DATA_HPP

#include "ObjectData.hpp"

class BufferData
{
    public:

        template<typename T> BufferData(T&& objectData);
        ~BufferData();
        BufferData(const BufferData&) = delete;
        BufferData operator=(const BufferData&) = delete;

        //
        unsigned int getVertexArrayID() const;
        unsigned int getVertexBufferID() const;
        unsigned int getElementBufferID() const;
        unsigned int getNumberOfIndices() const;

    private:

        void createVertexArray();
        template<typename T> void createVertexBuffer(T&& objectData);
        template<typename T> void createElementBuffer(T&& objectData);
        void enablePositionAttribPointer();
        void releaseAllBuffers();
        void deleteVertexArray();

        unsigned int    VertexArrayID;
        unsigned int    VertexBufferID;
        unsigned int    ElementBufferID;
        unsigned int    NumberOfIndices;
};

#endif
