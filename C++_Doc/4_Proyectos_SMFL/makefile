# Nombre del ejecutable
TARGET = onda

# Archivos fuente
SRC = _1_Introduccion_SMFL/1_prueba.cpp

# Compilador
CXX = g++

# Flags de compilación
CXXFLAGS = -std=c++17 -Wall

# Rutas de SFML (Homebrew en macOS)
SFML_INC = -I/opt/homebrew/include
SFML_LIB = -L/opt/homebrew/lib

# Librerías SFML
SFML_FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Regla por defecto
all: $(TARGET)

$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET) $(SFML_INC) $(SFML_LIB) $(SFML_FLAGS)

clean:
	rm -f $(TARGET)