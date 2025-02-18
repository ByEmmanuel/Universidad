cmake_minimum_required(VERSION 3.30)
project(C_Doc C)

set(CMAKE_C_STANDARD 11)

add_executable(
        C_Doc main.c
        LogicaNegocio.h
        LogicaNegocio.c
        NegocioDTO.c
        NegocioDTO.h
)

