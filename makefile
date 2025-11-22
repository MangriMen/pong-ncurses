CC := gcc
CFLAGS := -Wall -Wextra -pedantic -std=c99
DEBUG_FLAGS := -g -O0
RELEASE_FLAGS := -O2 -DNDEBUG

LIBS := -lncursesw -DNCURSES_STATIC

ifdef WIN32
    PLATFORM := windows
    CFLAGS += -D_WIN32_WINNT=0x0600
else ifdef WINDIR
    PLATFORM := windows
    CFLAGS += -D_WIN32_WINNT=0x0600
endif

SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
TARGET_DIR := bin
TARGET := $(TARGET_DIR)/pong

SRC_FILES := $(wildcard $(SRC_DIR)/*.c)
OBJ_FILES := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC_FILES))
DEP_FILES := $(OBJ_FILES:.o=.d)

INC_FLAGS := -I$(INC_DIR)

all: $(TARGET)

$(TARGET): $(OBJ_FILES) | $(TARGET_DIR)
	$(CC) $(OBJ_FILES) -o $@ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) $(INC_FLAGS) -MMD -MP -c $< -o $@

# Dependencies
-include $(DEP_FILES)

# Directories creation
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(TARGET_DIR):
	mkdir -p $(TARGET_DIR)

# Builds
debug: CFLAGS += $(DEBUG_FLAGS)
debug: all

release: CFLAGS += $(RELEASE_FLAGS)
release: all

# Utilities
clean:
	rm -rf $(BUILD_DIR) $(TARGET_DIR)

run: $(TARGET)
	./$(TARGET)

.PHONY: all debug release clean run info