#include <Loader.h>
#include <fstream>
#include <vector>
#include <exception>
#include <iostream>
#include <glbinding/gl/gl.h>
using namespace std;
using namespace glshaderloader;
using namespace gl;
unsigned int Loader::loadvf(const char *vsPath, const char *fsPath)
{
    fstream fileStream(vsPath, ios::ate | ios::binary | ios::in);
    vector<char> vertexShaderCode;
    if (fileStream.is_open())
    {
        vertexShaderCode.resize(fileStream.tellg());
        fileStream.seekg(0, ios::beg);
        fileStream.read(vertexShaderCode.data(), vertexShaderCode.size());
    }
    else
    {
        throw runtime_error(string("Unable to open " + string(vsPath)));
    }
    fstream fileStream2(fsPath, ios::ate | ios::binary | ios::in);
    vector<char> fragmentShaderCode;
    if (fileStream2.is_open())
    {
        fragmentShaderCode.resize(fileStream2.tellg());
        fileStream2.seekg(0, ios::beg);
        fileStream2.read(fragmentShaderCode.data(), fragmentShaderCode.size());
    }
    else
    {
        throw runtime_error(string("Unable to open " + string(fsPath)));
    }
    fileStream.flush();
    fileStream.close();
    fileStream2.flush();
    fileStream2.close();

    GLuint program = glCreateProgram();
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    char *vsData = vertexShaderCode.data();
    int vsSize = vertexShaderCode.size();
    glShaderSource(vertexShader, 1, &vsData, &vsSize);
    glCompileShader(vertexShader);
    int infoLogLen;
    vector<char> infoLog;
    GLboolean status;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &infoLogLen);
        infoLog.resize(infoLogLen);
        glGetShaderInfoLog(vertexShader, infoLogLen, nullptr, infoLog.data());
        glDeleteShader(vertexShader);
        cout << "Unable to compile shader at " << vsPath << "\n";
        cout << infoLog.data() << "\n";
        throw runtime_error(string("Failed to compile shader " +
                                   string(vsPath) +
                                   "\nInfo log:\n" +
                                   infoLog.data()));
    }
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    char *fsData = fragmentShaderCode.data();
    int fsSize = fragmentShaderCode.size();
    glShaderSource(fragmentShader, 1, &fsData, &fsSize);
    glCompileShader(fragmentShader);
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &status);
    if (status == GL_FALSE)
    {
        glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &infoLogLen);
        infoLog.resize(infoLogLen);
        glGetShaderInfoLog(fragmentShader, infoLogLen, nullptr, infoLog.data());
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        cout << "Unable to compile shader at " << fsPath << "\n";
        cout << infoLog.data() << "\n";
        throw runtime_error(string("Failed to compile shader " +
                                   string(fsPath) +
                                   "\nInfo log:\n" +
                                   infoLog.data()));
    }
    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);
    glLinkProgram(program);
    glGetProgramiv(program, GL_LINK_STATUS, &status);
    if (status == GL_FALSE)
    {
        glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLogLen);
        infoLog.resize(infoLogLen);
        glGetProgramInfoLog(program, infoLogLen, nullptr, infoLog.data());
        glDetachShader(program, vertexShader);
        glDetachShader(program, fragmentShader);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(program);
        cout << "Unable to link shaders " << vsPath << " and " << fsPath << "\n";
        cout << infoLog.data() << "\n";
        throw runtime_error(string("Failed to link shaders " +
                                   string(vsPath) + " " +
                                   string(fsPath) +
                                   "\nInfoLog:\n" +
                                   infoLog.data()));
    }
    glDetachShader(program, vertexShader);
    glDetachShader(program, fragmentShader);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    return program;
}
