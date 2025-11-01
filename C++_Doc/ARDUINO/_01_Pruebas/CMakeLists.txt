cmake_minimum_required(VERSION 3.5)
project(Blink C CXX ASM)

# Toolchain
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/toolchain-avr.cmake)

# Paths del SDK de Arduino
set(ARDUINO_SDK_PATH /Users/byemmanuel/Library/Arduino15/packages/arduino/hardware/avr/1.8.6)
set(ARDUINO_CORE_PATH ${ARDUINO_SDK_PATH}/cores/arduino)
set(ARDUINO_VARIANTS_PATH ${ARDUINO_SDK_PATH}/variants/standard)

# Depuración: Mostrar las rutas
message("ARDUINO_SDK_PATH: ${ARDUINO_SDK_PATH}")
message("ARDUINO_CORE_PATH: ${ARDUINO_CORE_PATH}")
message("ARDUINO_VARIANTS_PATH: ${ARDUINO_VARIANTS_PATH}")

# Archivos del core Arduino
file(GLOB ARDUINO_CORE_SRC
        "${ARDUINO_CORE_PATH}/*.c"
        "${ARDUINO_CORE_PATH}/*.cpp"
        "${ARDUINO_VARIANTS_PATH}/*.c"
        "${ARDUINO_VARIANTS_PATH}/*.cpp"
        "${ARDUINO_CORE_PATH}/*.S"  # Incluir archivos de ensamblador
)

# Depuración: Mostrar los archivos encontrados
message("Archivos del core Arduino: ${ARDUINO_CORE_SRC}")

# Verificar si ARDUINO_CORE_SRC está vacío
if(NOT ARDUINO_CORE_SRC)
    message(FATAL_ERROR "No se encontraron archivos en ${ARDUINO_CORE_PATH} o ${ARDUINO_VARIANTS_PATH}. Verifica las rutas del SDK.")
endif()

# Crear una biblioteca estática para el núcleo de Arduino
add_library(arduino_core STATIC ${ARDUINO_CORE_SRC})

# Incluir directorios para la biblioteca arduino_core
target_include_directories(arduino_core PRIVATE
        ${ARDUINO_CORE_PATH}
        ${ARDUINO_VARIANTS_PATH}
)

# Definiciones para la biblioteca arduino_core
target_compile_definitions(arduino_core PRIVATE
        -DF_CPU=16000000UL
        -DARDUINO=10813
        -DARDUINO_AVR_UNO
        -DARDUINO_ARCH_AVR
        -DARDUINO_VARIANT="standard"
)

# Archivos del proyecto
set(PROJECT_SOURCES
        main.cpp
        Blink.cpp
        blink.h
)

# Ejecutable
add_executable(Blink ${PROJECT_SOURCES})

# Incluir directorios para el ejecutable
target_include_directories(Blink PRIVATE
        ${ARDUINO_CORE_PATH}
        ${ARDUINO_VARIANTS_PATH}
)

# Definiciones para la placa
target_compile_definitions(Blink PRIVATE
        -DF_CPU=16000000UL
        -DARDUINO=10813
        -DARDUINO_AVR_UNO
        -DARDUINO_ARCH_AVR
        -DARDUINO_VARIANT="standard"
)

# Opciones de compilación
target_compile_options(Blink PRIVATE
        -mmcu=atmega328p
        -Os
        -fno-exceptions
        -ffunction-sections
        -fdata-sections
)

target_compile_options(arduino_core PRIVATE
        -mmcu=atmega328p
        -Os
        -fno-exceptions
        -ffunction-sections
        -fdata-sections
)

# Vincular el núcleo de Arduino
target_link_libraries(Blink PRIVATE arduino_core)

# Opciones de vinculación
target_link_options(Blink PRIVATE
        -mmcu=atmega328p
        -Wl,--gc-sections
)

# Regla para generar el archivo .hex
add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Blink.hex
        COMMAND avr-objcopy -O ihex -R .eeprom ${CMAKE_CURRENT_BINARY_DIR}/Blink ${CMAKE_CURRENT_BINARY_DIR}/Blink.hex
        DEPENDS Blink
)

# Regla para subir al Arduino
add_custom_target(upload
        COMMAND avrdude -v -patmega328p -carduino -P/dev/ttyACM0 -b115200 -Uflash:w:${CMAKE_CURRENT_BINARY_DIR}/Blink.hex:i
        DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/Blink.hex
)