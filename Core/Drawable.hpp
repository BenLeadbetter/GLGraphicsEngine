#ifndef GUARD_DRAWABLE_HPP
#define GUARD_DRAWABLE_HPP

/*
*   Header file for the Drawable class
*/

#include "BufferData.hpp"
#include <glm/glm.hpp>
#include <memory>
#include <array>

enum class RenderMode {LINE, FILL};

struct DrawData
{
    unsigned int VertexArrayID;
    unsigned int VertexBufferID;
    unsigned int ElementBufferID;
    unsigned int NumberOfIndices;
    RenderMode renderMode;
    glm::mat4 WorldTransform;
};

class Drawable
{
    public:
        
        //
        Drawable();
        Drawable(std::shared_ptr<BufferData> dataPtr);
        virtual ~Drawable();
        Drawable(const Drawable&);
        Drawable& operator=(const Drawable&);

        // interface
        std::array<float, 4> getColor() const;
        DrawData getDrawData() const;
        
        bool isActive() const; 
        
        template<typename T> void setData(T&& data);
        void setColor(const float&, const float&, const float&, const float&);
        void setRenderMode(RenderMode mode);
 
        //
        virtual void update() {};

    private:

        //
        std::array<float, 4> Color;
        glm::mat4 transform;
        bool active;
        std::shared_ptr<BufferData> GLdata;
        RenderMode renderMode;
};

#endif