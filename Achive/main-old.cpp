// #define CATCH_CONFIG_MAIN
// #include <catch.hpp>


#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <cmath>
#include "GL/GLsystem.h"
#include "GL/Shader.h"

#include "Core/Window.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

int main()
{

    /*
    *   Try out our new window class
    */
    Window window;

    
    Shader ourShader("GL/Shaders/VertexShaderSource.glsl", "GL/Shaders/FragmentShaderSource.glsl");

    std::vector<float> vertices = createIcoVertices();
    std::vector<unsigned int> indices = createIcoIndices();

    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(float) * indices.size(), indices.data(), GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // tell opengl for each sampler to which texture unit it belongs to (only has to be done once)
    // -------------------------------------------------------------------------------------------
    ourShader.use();
    ourShader.setInt("texture1", 0);
    ourShader.setInt("texture2", 1);

    // Here we define our projection transformation
    glm::mat4 proj = projMatrix(16.0f, 1.0f, 1.0f, 3.0f);
    ourShader.use();
    unsigned int projLoc = glGetUniformLocation(ourShader.ID, "proj");
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(proj));

    // render loop
    // -----------
    while (!window.shouldClose())
    {
        // input
        // -----
        window.processInput();

        // render
        // ------
        window.clear();
        
        // Here we define our view transform
        glm::mat4 view = viewChange(
            glm::vec3(4.0 * glm::cos((float)glfwGetTime()), 4.0 * glm::sin((float)glfwGetTime()), 3.0f), 
            glm::vec3(0.0f, 0.0f, 0.0f), 
            glm::vec3(0.0f, 0.0f, 1.0f)
            );

        ourShader.use();
        unsigned int viewLoc = glGetUniformLocation(ourShader.ID, "view");
        glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view));


        /*
        *   Render the wireFrame
        */ 
        // offset the drawing
        glPolygonOffset(-1.0f, -10.0f);
        glEnable(GL_POLYGON_OFFSET_LINE);

        // antialias the lines
        glEnable(GL_LINE_SMOOTH);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Draw the black wirefram
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glLineWidth(2.5f);
        ourShader.use();
        glDrawElements(GL_TRIANGLES, 80, GL_UNSIGNED_INT, 0);

        // put everythig back the way we found it
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        glDisable(GL_POLYGON_OFFSET_LINE);
        glLineWidth(1.0f);
        glDisable(GL_BLEND);
        glDisable(GL_LINE_SMOOTH);

        

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        window.swapBuffers();
        window.pollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

