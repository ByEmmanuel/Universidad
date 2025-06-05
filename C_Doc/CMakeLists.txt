cmake_minimum_required(VERSION 3.30)
project(C_Doc C)

set(CMAKE_C_STANDARD 11)

# Buscar la librería ncurses
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
# Enlazar la librería ncurses

add_executable(C_Doc

        ProyectoPE/main.c
        #ProyectoPE/LogicaNegocio.h
        ProyectoPE/LogicaNegocio.c
        ProyectoPE/UsuarioDTO.c
        #ProyectoPE/UsuarioDTO.h
        ProyectoPE/Util.c
        #ProyectoPE/Util.h
        ProyectoPE/UserInterface.c
        #ProyectoPE/UserInterface.h
        ProyectoPE/Pago.c
        ProyectoPE/Clientes.c
        #ProyectoPE/ConstantesMotores.h
        ProyectoPE/RegistrarMotor.c
        ProyectoPE/Testing.c
        #ProyectoPE/Testing.h
        ProyectoPE/Almacen.c
        ProyectoPE/UsuarioDAO.c
        ProyectoPE/ApartadoOtros.c
        ProyectoPE/ConstantesMotores.c
        ProyectoPE/SystemLogs.c
        ProyectoPE/reloj.c
        #ProyectoPE/reloj.h
)

target_link_libraries(C_Doc ${CURSES_LIBRARIES})