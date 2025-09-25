# Nome do executável
TARGET = build/jogo

# Compilador
CC = gcc

# Diretórios
SRC_DIR = src
INC_DIR = include
BUILD_DIR = build

# Flags
CFLAGS = -Wall -I$(INC_DIR)

# Bibliotecas SDL
LIBS = -lSDL2 -lSDL2_gfx -lSDL2_image -lSDL2_ttf

# Fontes
SRC = $(wildcard $(SRC_DIR)/*.c)

# Regras
all: $(TARGET)

$(TARGET): $(SRC)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(SRC) $(CFLAGS) -o $(TARGET) $(LIBS)

clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

run: all
	./$(TARGET)

