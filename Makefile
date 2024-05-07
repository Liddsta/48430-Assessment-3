# Variables
CC=gcc
CFLAGS=-Wall -Werror -ansi
SRC_DIR=./src/
OBJ_DIR=./build/
EXE_DIR=./build/
SRC_FILE=$(SRC_DIR)main.c
OBJ_FILE=$(OBJ_DIR)$(notdir $(SRC_FILE:.c=.o))
EXE_FILE=$(EXE_DIR)main

# Default target
all: $(OBJ_DIR) $(EXE_FILE)

# Ensure the object directory exists
$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

# Compilation and Linking rule
$(EXE_FILE): $(OBJ_FILE)
	$(CC) $(CFLAGS) $< -o $@

# Compile to object file
$(OBJ_FILE): $(SRC_FILE)
	$(CC) $(CFLAGS) -c $< -o $@

# Clean rule
clean:
	rm -rf $(OBJ_DIR)

# Phony targets
.PHONY: all clean
