// source file for system.cpp

#include "GLsystem.h"
#include <iostream>
#include <fstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

/*
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}
*/

void processInput(GLFWwindow* window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

unsigned int loadTexture(const std::string& filename)
{
    unsigned int ret;

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(filename.c_str(), &width, &height, &nrChannels, 0);

    if(data)
    {
        // create and assign a texture object
        glGenTextures(1, &ret);
        glBindTexture(GL_TEXTURE_2D, ret);

        // set the wrapping parameters
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // assign the loaded data
        if(nrChannels == 3)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        } 
        else if(nrChannels == 4)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }   
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }

    stbi_image_free(data);
    
    return ret;
    
}

std::vector<float> createIcoVertices()
{

    // define the vertices for an icosahedron
    std::vector<float> vertices(12*3, 0.0f);
    // top vertex
    vertices[0] = 0.0f;
    vertices[1] = 0.0f;
    vertices[2] = 0.5f;
    // bottom vertex
    vertices[33] = 0.0f;
    vertices[34] = 0.0f;
    vertices[35] = -0.5f;
    // and the rest
    static float dAngle = 2 * 3.14159 / 5;
    size_t vertexIndex = 3;     // start filling from 3rd vertex
    for(size_t i = 0; i != 5; ++i)
    {
        vertices[vertexIndex] = 0.5 * glm::cos(dAngle * i) * glm::sin(dAngle);
        vertices[vertexIndex + 15] = 0.5 * glm::cos(dAngle * (i + 0.5)) * glm::sin(dAngle);
        ++vertexIndex;
        vertices[vertexIndex] = 0.5 * glm::sin(dAngle * i) * glm::sin(dAngle);
        vertices[vertexIndex + 15] = 0.5 * glm::sin(dAngle * (i + 0.5)) * glm::sin(dAngle);
        ++vertexIndex;
        vertices[vertexIndex] = 0.5 - glm::cos(dAngle);
        vertices[vertexIndex + 15] = - 0.5 + glm::cos(dAngle);;
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

// view change matrix
glm::mat4 viewChange(glm::vec3 Eye, glm::vec3 At, glm::vec3 Up)
{
    // create new view-basis
    glm::vec3 n = glm::normalize(Eye - At);
    glm::vec3 u = glm::normalize(glm::cross(Up, n));
    glm::vec3 v = glm::cross(n, u);

    glm::mat4 ret(
        u.x, v.x, n.x, 0.0f,
        u.y, v.y, n.y, 0.0f,
        u.z, v.z, n.z, 0.0f,
        -glm::dot(Eye, u), -glm::dot(Eye, v), -glm::dot(Eye,n), 1.0f
    );

    return ret;
}

// projection matrix
glm::mat4 projMatrix(float Dist, float Aspect, float Near, float Far)
{
    return glm::mat4(
        Dist / Aspect,      0.0f,       0.0f,                           0.0f,
        0.0f,               Dist,       0.0f,                           0.0f,
        0.0f,               0.0f,       -(Far + Near) / (Far - Near),   -2 * Near * Far / (Far - Near),
        0.0f,               0.0f,       -1.0f,                          0.0f
    );
}


