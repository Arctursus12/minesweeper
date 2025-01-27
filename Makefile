# Compiler
CXX = g++

# Compiler flags
CXXFLAGS = -Wall -Iinclude

# Directories
SRC_DIR = src
UI_DIR = $(SRC_DIR)/game_ui
ARRAY_DIR = $(SRC_DIR)/array_setup

# Files
SRCS = $(UI_DIR)/window.cpp $(ARRAY_DIR)/array_grid_math.cpp
OBJS = $(SRCS:.cpp=.o)

# Output
TARGET = minesweeper

# Default rule
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) -o $@ $^ -lncurses

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Clean up
clean:
	rm -f $(OBJS) $(TARGET)