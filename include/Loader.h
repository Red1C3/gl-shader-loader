#pragma once
namespace glshaderloader
{
    class Loader
    {
        Loader();

    public:
        static unsigned int loadvf(const char *vertexShaderPath, const char *fragmentShaderPath);
    };
}