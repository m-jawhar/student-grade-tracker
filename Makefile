# Student Grade Tracker - Makefile

# Compiler and flags
CC = gcc
CFLAGS = -Wall -Wextra -Iinclude
LDFLAGS =

# Directories
SRC_DIR = src
BUILD_DIR = build
BIN_DIR = bin
INCLUDE_DIR = include
DATA_DIR = data

# Target executable
TARGET = $(BIN_DIR)/studentSystem.exe

# Source files
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRCS))

# Default target
.PHONY: all
all: $(TARGET)

# Create necessary directories and build
$(TARGET): | directories
$(TARGET): $(OBJS)
	$(CC) $(OBJS) -o $(TARGET) $(LDFLAGS)
	@echo Build complete: $(TARGET)

# Create directories (MSYS2 compatible)
.PHONY: directories
directories:
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(DATA_DIR)

# Compile source files to object files
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | directories
	$(CC) $(CFLAGS) -c $< -o $@

# Run the program
.PHONY: run
run: all
	@$(TARGET)

# Clean build artifacts (MSYS2 compatible)
.PHONY: clean
clean:
	@rm -rf $(BUILD_DIR) $(BIN_DIR)
	@echo Clean complete

# Clean and rebuild
.PHONY: rebuild
rebuild: clean all

# Help target
.PHONY: help
help:
	@echo Available targets:
	@echo   all      - Build the project (default)
	@echo   run      - Build and run the program
	@echo   clean    - Remove build artifacts
	@echo   rebuild  - Clean and rebuild
	@echo   help     - Show this help message

# Dependencies
$(BUILD_DIR)/main.o: $(INCLUDE_DIR)/student.h $(INCLUDE_DIR)/fileio.h $(INCLUDE_DIR)/display.h $(INCLUDE_DIR)/operations.h $(INCLUDE_DIR)/statistics.h
$(BUILD_DIR)/grading.o: $(INCLUDE_DIR)/student.h $(INCLUDE_DIR)/grading.h
$(BUILD_DIR)/fileio.o: $(INCLUDE_DIR)/student.h $(INCLUDE_DIR)/fileio.h $(INCLUDE_DIR)/grading.h
$(BUILD_DIR)/display.o: $(INCLUDE_DIR)/student.h $(INCLUDE_DIR)/display.h $(INCLUDE_DIR)/grading.h
$(BUILD_DIR)/operations.o: $(INCLUDE_DIR)/student.h $(INCLUDE_DIR)/operations.h $(INCLUDE_DIR)/grading.h $(INCLUDE_DIR)/fileio.h
$(BUILD_DIR)/statistics.o: $(INCLUDE_DIR)/student.h $(INCLUDE_DIR)/statistics.h $(INCLUDE_DIR)/display.h
