set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR avr)

# Herramientas
find_program(AVR_GCC avr-gcc)
find_program(AVR_GXX avr-g++)
find_program(AVR_OBJCOPY avr-objcopy)
find_program(AVR_SIZE avr-size)
find_program(AVR_UPLOAD avrdude)

set(CMAKE_C_COMPILER ${AVR_GCC})
set(CMAKE_CXX_COMPILER ${AVR_GXX})

# Opciones globales
set(CMAKE_C_FLAGS "-mmcu=atmega328p -Os -Wall -ffunction-sections -fdata-sections")
set(CMAKE_CXX_FLAGS "-mmcu=atmega328p -Os -Wall -fno-exceptions -ffunction-sections -fdata-sections")
set(CMAKE_EXE_LINKER_FLAGS "-mmcu=atmega328p -Wl,--gc-sections")