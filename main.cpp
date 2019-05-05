// #define CATCH_CONFIG_MAIN
// #include <catch.hpp>

#include "Core/Window.hpp"
#include "Core/Drawer.hpp"
#include "Core/MeshManager.hpp"

#include <cmath>

int main()
{
    /*
    *   Try out our new classes
    */
    Window window;
    Drawer drawer;
    MeshManager meshManager;

    Drawable cube(meshManager.getMesh(MeshID::CUBE));
    cube.setRenderMode(RenderMode::LINE);
    cube.setColor(0.6f, 0.7f, 0.6f, 0.8);

    // render loop
    // -----------
    while (!window.shouldClose())
    {
        /*
         *  Input 
         */ 
        
        window.processInput();
        window.pollEvents();        

        /*
         *  Update
         */ 
        
            
        drawer.setView(
            ViewData(
                glm::vec3(3.0 * std::sin((float)glfwGetTime()), 3.0 * std::cos((float)glfwGetTime()), 2.0f),
                glm::vec3(0.0f, 0.0f, 0.0f),
                glm::vec3(0.0f, 0.0f, 1.0f)
            )
        );
        drawer.updateShader();

        /*
        *   Render 
        */ 

        window.clear();
        drawer.draw(cube);

        /*
        *   Display 
        */ 

        window.swapBuffers();

        assert(glGetError() == GL_NO_ERROR);
    }

    return 0;
}

