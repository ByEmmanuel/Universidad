cmake_minimum_required(VERSION 3.30)
project(C_Doc C)

set(CMAKE_C_STANDARD 11)

add_executable(C_Doc

        ProyectoPE/main.c
        ProyectoPE/LogicaNegocio.h
        ProyectoPE/LogicaNegocio.c
        ProyectoPE/UsuarioDTO.c
        ProyectoPE/UsuarioDTO.h
        ProyectoPE/Util.c
        ProyectoPE/Util.h
)

