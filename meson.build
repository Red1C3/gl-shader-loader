project('gl-shader-loader','cpp',
    version:'0.1.0',
    default_options:['buildtype=release'])
src_assembler=run_command('./srcAssembler.py',check:true)
sources=src_assembler.stdout().strip().split('\n')
include_dir='./include'
glbinding=dependency('glbinding')
shader_loader=library('gl-shader-loader',sources,include_directories:[include_dir],dependencies:[glbinding]
    ,install:true)


pkg=import('pkgconfig')
pkg.generate(shader_loader,install_dir:'/usr/local/pkgconfig')
install_headers('include/Loader.h',subdir:'gl-shader-loader')