/**
 * 
 *  Source file for the Window.hpp class header
 * 
*/

#include "Window.hpp"
#include <assert.h>
#include <iostream>


#include "../GL/GLCheckError.hpp"
#define glCheckError() glCheckError_(__FILE__, __LINE__)


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void Window::initializeGLFW() const
{
    
    // initialize glfw
    glfwInit();
    // insist that the system is running version 3.30
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // set the profile to core - we don't need any of the fancy stuff
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    #ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    #endif
      
}

void Window::loadGLAD() const
{
    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        //throw std::string("Failed to initialize GLAD");
        std::cout << "Failed to initialize GLAD" << std::endl;
    }
}

void Window::createWindow()
{
    // create the unique pointer to the window
    window = glfwCreateWindow(800, 800, "GraphicsEngine", nullptr, nullptr);
    // window = std::make_unique<GLFWwindow>(rawPtr);

    // check for success
    if(!window)
    {
        //throw std::string("Failed to create GLW window");
        std::cout << "Failed to create GLW window" << std::endl;
        glfwTerminate();
        return;
    }

    glfwMakeContextCurrent(window);
    // glViewport(0, 0, 1000, 1000);
}

Window::Window()
{
    // assert only one instance
    static bool instantiated = false;
    assert(instantiated == false);

    initializeGLFW();
    createWindow();
    loadGLAD();

    // assign our callback function 
    // for window resizing
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    instantiated = true;

    glCheckError();
}

Window::~Window()
{
    // terminate glfw
    glfwTerminate();
}

bool Window::shouldClose() const
{
    return glfwWindowShouldClose(window);
}

void Window::processInput() const
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

void Window::swapBuffers() const
{
    glfwSwapBuffers(window);
}

void Window::pollEvents() const
{
    glfwPollEvents();
}

void Window::clear() const
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);    
}

