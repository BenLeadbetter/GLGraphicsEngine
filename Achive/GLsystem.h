#ifndef GUARD__SYSTEM_H
#define GUARD__SYSTEM_H
// header for system functions

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <vector>
#include <glm/glm.hpp>


// void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);
unsigned int loadTexture(const std::string& fileName);

// creating data for an icohasedron
std::vector<float> createIcoVertices();
std::vector<unsigned int> createIcoIndices();

// matrices for viewing icosahedron
glm::mat4 viewChange(glm::vec3 Eye, glm::vec3 At, glm::vec3 Up);
glm::mat4 projMatrix(float Dist, float Aspect, float Near, float Far);


#endif
