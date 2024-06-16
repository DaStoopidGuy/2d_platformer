TARGET_EXEC := 2d_platformer
SRC_DIRS := ./src

# get source files and corresponding .o files automatically
SRCS := $(wildcard $(SRC_DIRS)/*.c)
OBJS := $(SRCS:.c=.o)
OBJS := $(notdir $(OBJS))

CC = gcc
INC_FLAGS = -Iinclude
CFLAGS = $(INC_FLAGS) -std=c99 -ggdb

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
ifeq ($(detected_OS),Darwin) # TODO: needs to be tested on OSX, might not work
	CC = clang
	LDFLAGS := -lraylib -framework OpenGL -framework Cocoa -framework IOKit -framework CoreAudio -framework CoreVideo
endif

# this is what runs when typing only "make"
.PHONY: default
default: run

# TODO: also rebuild when a corresponding header file is modified, currently make does not track header files

$(TARGET_EXEC): $(OBJS)
	$(CC) $^ -o $(TARGET_EXEC) $(LDFLAGS)

%.o: $(SRC_DIRS)/%.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean run

clean:
	rm -f *.o $(TARGET_EXEC)

run: $(TARGET_EXEC)
	./$(TARGET_EXEC)

debug: $(TARGET_EXEC)
	gf2 $(TARGET_EXEC)

# HACK just hardcoded windows cross compilation on linux
windows-cross:
	x86_64-w64-mingw32-gcc src/*.c -o 2d_platformer.exe -Iinclude -Llib -lraylib -lopengl32 -lgdi32 -lwinmm
