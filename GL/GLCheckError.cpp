/**
 * 
 *  Source file for the GLCheckError functions
 * 
*/

#include "GLCheckError.hpp"


void glCheckError_(const char *p_file, int p_line) {
    GLenum error_code;
    while ((error_code = glGetError()) != GL_NO_ERROR)
    {
        std::string error;
        switch (error_code)
        {
            case GL_INVALID_ENUM:                  error = "INVALID_ENUM"; break;
            case GL_INVALID_VALUE:                 error = "INVALID_VALUE"; break;
            case GL_INVALID_OPERATION:             error = "INVALID_OPERATION"; break;
            case GL_OUT_OF_MEMORY:                 error = "OUT_OF_MEMORY"; break;
            case GL_INVALID_FRAMEBUFFER_OPERATION: error = "INVALID_FRAMEBUFFER_OPERATION"; break;
        }
        std::cout << error << " | " << p_file << " (" << p_line << ")" << std::endl;
    }
}
