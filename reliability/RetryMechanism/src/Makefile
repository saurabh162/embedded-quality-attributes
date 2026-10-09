# ============================================================
# Retry Example - Makefile
# ============================================================

CXX := g++

# Compiler options
CXXFLAGS := -std=c++17 -Wall -Wextra -Wpedantic

# Directories
SRC_DIR := src
BUILD_DIR := build

# Target executable
TARGET := $(BUILD_DIR)/retry_example

# Source files
SOURCES := \
	$(SRC_DIR)/main.cpp \
	$(SRC_DIR)/TemperatureSensorService.cpp \
	$(SRC_DIR)/TemperatureMonitor.cpp

# Object files
OBJECTS := $(SOURCES:$(SRC_DIR)/%.cpp=$(BUILD_DIR)/%.o)


# ============================================================
# Default Target
# ============================================================

all: $(TARGET)


# ============================================================
# Link Executable
# ============================================================

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)


# ============================================================
# Compile Source Files
# ============================================================

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -I$(SRC_DIR) -c $< -o $@


# ============================================================
# Run
# ============================================================

run: $(TARGET)
	./$(TARGET)


# ============================================================
# Debug Build
# ============================================================

debug: CXXFLAGS += -g -O0
debug: clean $(TARGET)


# ============================================================
# Release Build
# ============================================================

release: CXXFLAGS += -O2 -DNDEBUG
release: clean $(TARGET)


# ============================================================
# Clean
# ============================================================

clean:
	rm -rf $(BUILD_DIR)


# ============================================================
# Help
# ============================================================

help:
	@echo "Available targets:"
	@echo "  make          Build the example"
	@echo "  make run      Build and run"
	@echo "  make debug    Build with debug information"
	@echo "  make release  Build optimized version"
	@echo "  make clean    Remove generated files"
	@echo "  make help     Show available targets"


.PHONY: all run debug release clean help