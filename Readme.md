# gl-shader-loader

An OpenGL shader loader

## Support
So far it only provides a vertex-fragment shaders support, so it is safe to say that is supports 3.3 onwards, it should work with C++11 onwards compilers too.

## Usage
The library has a single class that provides static methods for loading, the methods recieve the paths of the shaders and return a shader program handle, the loader expects an existant OpenGL context, otherwise it will fail.

Any Error will throw a runtime_error exception with a message.

## Installtion
On Unix-based systems, it's easier to use Meson for installation, Windows users will have to compile and move the compiled files to a suitable location.

## Motivation
I've written shader loading code many times and just decided to create a loader instead !