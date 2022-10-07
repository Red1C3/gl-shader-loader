project('gl-shader-loader','cpp')
src_assembler=run_command('./srcAssembler.py',check:true)
sources=src_assembler.stdout().strip().split('\n')
include_dir='./include'
shader_loader=library('gl-shader-loader',sources,include_directories:[include_dir],dependencies:[])


pkg=import('pkgconfig')
pkg.generate(shader_loader,install_dir:'/usr/local')