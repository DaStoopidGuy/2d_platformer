TARGET_EXEC := 2d_platformer
SRC_DIRS := ./src

CC = gcc
INC_FLAGS = -Iinclude
CFLAGS = $(INC_FLAGS) -std=c99

# detect OS
ifeq ($(OS),Windows_NT)
	detected_OS := Windows
else
	detected_OS := $(shell sh -c 'uname 2>/dev/null || echo Unknown')
endif

$(info Detected OS: $(detected_OS))

ifeq ($(detected_OS),Windows)
	LDFLAGS := -Llib -lraylib -lopengl32 -lgdi32 -lwinmm
endif
ifeq ($(detected_OS),Linux)
	LDFLAGS := -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

$(TARGET_EXEC): main.o player.o tile.o
	$(CC) $^ -o $(TARGET_EXEC) $(LDFLAGS)

%.o: $(SRC_DIRS)/%.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean run all
clean:
	rm -f *.o $(TARGET_EXEC)

run: $(TARGET_EXEC)
	./$(TARGET_EXEC)

all: clean run
