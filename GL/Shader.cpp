// source file for the Shader.h class header

#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(const GLchar* vertextPath, const GLchar* fragmentPath)
{

    /* 
    *     1. retrieve the vertext / fragment source from file path
    */

    // 
    std::string vertCode;
    std::string fragCode;
    std::ifstream vertShaderFile;
    std::ifstream fragShaderFile;

    // ensure the ifstream objects will throw exceptions
    vertShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);
    fragShaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

    try {
        // open the files
        vertShaderFile.open(vertextPath);
        fragShaderFile.open(fragmentPath);
        std::stringstream vertShaderStream, fragShaderStream;
        
        // read the buffer contents onto the string streams
        vertShaderStream << vertShaderFile.rdbuf();
        fragShaderStream << fragShaderFile.rdbuf();

        // close the file handlers
        vertShaderFile.close();
        fragShaderFile.close();

        // convert the streams to strings
        vertCode = vertShaderStream.str();
        fragCode = fragShaderStream.str();
    }
    catch (std::ifstream::failure e)
    {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
    }

    // assign the code the c-style strings
    const char* vertShaderCode = vertCode.c_str();
    const char* fragShaderCode = fragCode.c_str();

    /* 
    *    2. compile the shaders
    */

    unsigned int vertex, fragment;
    int success;
    char infoLog[512];

    // vertex shader first
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vertShaderCode, nullptr);
    glCompileShader(vertex);

    // print compile errors, if any
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        glGetShaderInfoLog(vertex, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" 
        << infoLog << std::endl;
    }

    // now fragment shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fragShaderCode, nullptr);
    glCompileShader(fragment);

    // print any errors
    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if(!success)
    {
        // get the problem from the system
        glGetShaderInfoLog(fragment, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
        << infoLog << std::endl;
    }

    // shader program
    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);

    // prind linking errors if any
    glGetProgramiv(ID, GL_LINK_STATUS, &success);
    if(!success)
    {
        // get the problem 
        glGetProgramInfoLog(ID, 512, nullptr, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
        << infoLog << std::endl;
    }

    // delete the newly created shaders (they are copied to the system)
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::use()
{
    glUseProgram(ID);
}

void Shader::setBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void Shader::setInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void Shader::setFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value); 
}

void Shader::setMat4(const std::string& name, glm::mat4 value) const
{
    unsigned int matrixLocation = glGetUniformLocation(ID, name.c_str());
    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, glm::value_ptr(value));
}

void Shader::setVec4(const std::string& name, float x, float y, float z, float w) const
{
    unsigned int vecLocation = glGetUniformLocation(ID, name.c_str());
    glUniform4f(vecLocation, x, y, z, w);
}

