# Compiler and flags
CXX := g++
CXXFLAGS += -std=c++11

FLAGS += -MMD
FLAGS += -MP
FLAGS += -g
FLAGS += -D_DEBUG
FLAGS += -Wall
FLAGS += -Wextra
FLAGS += -fPIC

CXXFLAGS += $(FLAGS)

# Directories
INCLUDE_DIR = include
SRC_DIR = src
MAIN_SRC_DIR = test
BUILD_DIR = build
OBJ_DIR = $(BUILD_DIR)
BIN_DIR = $(BUILD_DIR)/bin

# Source files and object files
SRCS = $(MAIN_SRC_DIR)/main.cpp $(SRC_DIR)/stoneydsp/stoneydsp.cpp
OBJS = $(OBJ_DIR)/test/main.o $(OBJ_DIR)/src/stoneydsp/stoneydsp.o

# Target executable
TARGET = $(BIN_DIR)/main

# Default target
all: $(TARGET)

# Link the target executable
$(TARGET): $(OBJS) | $(BIN_DIR)
	$(CXX) $(OBJS) -o $(TARGET)

# Compile source files into object files
$(OBJ_DIR)/test/main.o: $(MAIN_SRC_DIR)/main.cpp | $(OBJ_DIR)/test
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $(MAIN_SRC_DIR)/main.cpp -o $(OBJ_DIR)/test/main.o

$(OBJ_DIR)/src/stoneydsp/stoneydsp.o: $(SRC_DIR)/stoneydsp/stoneydsp.cpp | $(OBJ_DIR)/src/stoneydsp
	$(CXX) $(CXXFLAGS) -I$(INCLUDE_DIR) -c $(SRC_DIR)/stoneydsp/stoneydsp.cpp -o $(OBJ_DIR)/src/stoneydsp/stoneydsp.o

# Create object directory if it doesn't exist
$(OBJ_DIR)/src/stoneydsp:
	mkdir -p $(OBJ_DIR)/src/stoneydsp

$(OBJ_DIR)/test:
	mkdir -p $(OBJ_DIR)/test

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Create bin directory if it doesn't exist
$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# Clean up build files
clean:
	rm -rvf $(OBJ_DIR)/*.o $(OBJ_DIR)/**/*.o $(OBJ_DIR)/**/**/*.o $(TARGET)

# Run all targets
all: $(OBJ_DIR) $(BIN_DIR) $(TARGET)

run: $(TARGET)
	$(TARGET) $(ARGS)

.PHONY: all clean run
