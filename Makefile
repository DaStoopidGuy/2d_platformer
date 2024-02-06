TARGET_EXEC := 2d_platformer
SRC_DIRS := ./src

CC = gcc
LDFLAGS = -Llib -lraylib -lopengl32 -lgdi32 -lwinmm
INC_FLAGS = -Iinclude
CFLAGS = $(INC_FLAGS)

$(TARGET_EXEC): main.o
	$(CC) $^ -o $(TARGET_EXEC) $(LDFLAGS)

%.o: $(SRC_DIRS)/%.c
	$(CC) $(CFLAGS) -c $<

.PHONY: clean run
clean:
	rm -f *.o $(TARGET_EXEC)

run: $(TARGET_EXEC)
	./$(TARGET_EXEC)