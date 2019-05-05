
/*
*       Source file for the Drawable class
*/

#include "Drawable.hpp"



Drawable::Drawable():
    Color(std::array<float, 4>{1.0f, 1.0f, 1.0f, 1.0f}),   // default is white
    transform(glm::mat4(1.0f)),
    active(false),
    GLdata(nullptr),
    renderMode(RenderMode::LINE)
{};

Drawable::Drawable(std::shared_ptr<BufferData> dataPtr):
    Color(std::array<float, 4>{1.0f, 1.0f, 1.0f, 1.0f}),   // default is white
    transform(glm::mat4(1.0f)),
    active(false),
    GLdata(dataPtr),
    renderMode(RenderMode::LINE)
{};


Drawable::~Drawable()
{};

Drawable::Drawable(const Drawable& drawable)
{
    Color = drawable.Color;
    active = false;         // object will be created INACTIVE
    renderMode = drawable.renderMode;
    GLdata = drawable.GLdata;

}

Drawable& Drawable::operator=(const Drawable& rhs)
{
    // replace the simple data
    Color = rhs.Color;
    active = false;         // again, will be created INACTIVE
    renderMode = rhs.renderMode;
    GLdata = rhs.GLdata;

    return *this;
}

// interface
std::array<float, 4> Drawable::getColor() const
{
    return Color;
}

bool Drawable::isActive() const
{
    return active;
}

void Drawable::setRenderMode(RenderMode mode)
{
    renderMode = mode;   
}

void Drawable::setColor(const float& r, const float& g, const float& b, const float& a)
{
    Color = std::array<float, 4>{r, g, b, a};
}

DrawData Drawable::getDrawData() const
{
    DrawData ret;
    ret.VertexArrayID = GLdata->getVertexArrayID();
    ret.VertexBufferID = GLdata->getVertexBufferID();
    ret.ElementBufferID = GLdata->getElementBufferID();
    ret.NumberOfIndices = GLdata->getNumberOfIndices();
    ret.renderMode = renderMode;
    ret.WorldTransform = transform;

    return ret;
}

// update
