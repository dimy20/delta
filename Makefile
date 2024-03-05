EXEC=main
CC=clang++

SRC_DIR=src
INCLUDE_DIR=include
BUILD_DIR=build

CFLAGS = -Wall -Werror -g -std=c++20 -I$(INCLUDE_DIR)
LIBS = -lraylib

SRC_FILES = $(wildcard $(SRC_DIR)/*.cpp)
OBJS = $(patsubst $(SRC_DIR)/%.cpp, $(BUILD_DIR)/%.o, $(SRC_FILES))

all: main create_dir

main: $(OBJS)
	$(CC) -o $@ $^ $(LIBS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) -c $^ -o $@

create_dir:
	mkdir -p $(BUILD_DIR)

.PHONY: clean create_dir

clean:
		rm -rf $(BUILD_DIR)/*o $(EXEC)
