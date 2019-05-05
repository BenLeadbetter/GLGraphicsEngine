#ifndef GUARD_GL_CHECK_ERROR_HPP
#define GUARD_GL_CHECK_ERROR_HPP

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>
#include <iostream>

void glCheckError_(const char *p_file, int p_line);

#endif