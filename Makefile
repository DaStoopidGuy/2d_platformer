BUILD_DIR := ./build
SRC_DIRS := ./src

ASSETS_PATH := \"resources/\"

TARGET_EXEC := $(BUILD_DIR)/2d_platformer

SRCS := $(wildcard $(SRC_DIRS)/*.c)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INC_FLAGS := -Iinclude
CFLAGS := $(INC_FLAGS) -MMD -MP -DASSETS_PATH=$(ASSETS_PATH)
LDFLAGS := -Llib -lraylib -lm

.PHONY: run
run: $(TARGET_EXEC)
	./$(TARGET_EXEC)

# The final build step.
$(TARGET_EXEC): $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

-include $(DEPS)
