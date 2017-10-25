CXX      := g++
CXXFLAGS := -Wall -Wextra -Werror -pedantic -ansi -std=c++14
LDFLAGS  := -L/usr/lib -lstdc++ -lm
BUILD    := build
OBJ_DIR  := $(BUILD)
TARGET   := huffman
INCLUDE  := -I$(shell pwd)
SRC      :=                     \
   $(wildcard src/node.cpp)	\
   $(wildcard src/encoder.cpp)	\
   $(wildcard src/main.cpp)	\

OBJECTS := $(SRC:%.cpp=$(OBJ_DIR)/%.o)

all: build $(TARGET)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) -o $@ -c $<

$(TARGET): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(INCLUDE) $(LDFLAGS) -o $(TARGET) $(OBJECTS)

.PHONY: all build clean

build:
	@mkdir -p $(OBJ_DIR)

clean:
	rm -rf build/*