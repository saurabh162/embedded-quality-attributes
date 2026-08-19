# Compiler
CXX := g++

# Compiler flags
CXXFLAGS := -std=c++17 -Wall -Wextra -pedantic

# Directories
SRC_DIR := src
BUILD_DIR := build

# Target
TARGET := $(BUILD_DIR)/temperature_monitor

# Source files
SRCS := $(SRC_DIR)/main.cpp

# Default target
all: $(TARGET)

# Create build directory and build executable
$(TARGET): $(SRCS)
	mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET)

# Run application
run: $(TARGET)
	./$(TARGET)

# Remove build artifacts
clean:
	rm -rf $(BUILD_DIR)

.PHONY: all run clean