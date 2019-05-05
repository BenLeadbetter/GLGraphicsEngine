#ifndef GUARD_DRAWER_HPP
#define GUARD_DRAWER_HPP

/**
 * 
 *  Header file for the Drawer class
 * 
 *  This class will be responsible for Drawing Drawables
 *  and for managing the shader and camera positions etc.
 * 
 * 
*/

#include "../GL/Shader.h"
#include "Drawable.hpp"
#include <glm/glm.hpp>

struct ViewData
{
    ViewData(glm::vec3 EyeIn, glm::vec3 AtIn, glm::vec3 UpIn):
    Eye(EyeIn),
    At(AtIn),
    Up(UpIn)
    {};

    glm::vec3 Eye;
    glm::vec3 At;
    glm::vec3 Up;
};

struct ProjectionData
{
    ProjectionData(float DistIn, float AspectIn, float NearIn, float FarIn):
    Dist(DistIn),
    Aspect(AspectIn),
    Near(NearIn),
    Far(FarIn)
    {};

    float Dist;
    float Aspect;
    float Near;
    float Far;
};

class Drawer
{
    public:

        //
        Drawer();

        //
        void setView(const ViewData&);
        void setProjection(const ProjectionData&);
        //TODO void moveAt(vector);
        //TODO void rotateEye();
        void updateShader();

        //
        void draw(const Drawable&);

    private:
        
        //
        void loadShader();
        void drawSolidPolygon(const Drawable&);
        void drawWireFramePolygon(const Drawable&);

        //
        glm::mat4   viewChangeMatrix;
        glm::mat4   projectionMatirx;
        
        //
        Shader      shader;

        //
        // float cameraSpeed;
};

#endif