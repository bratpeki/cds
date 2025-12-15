
CC = gcc
FLAGS = -Wall -Wextra -Wpedantic -Werror
SRC_DIR = src
BIN_DIR = bin

# Taken from the Make docs
# 4.4.3 The Function wildcard
SOURCE = $(wildcard $(SRC_DIR)/*.c)

# Taken from the Make docs
# 8.2 Functions for String Substitution and Analysis
TARGETS = $(patsubst $(SRC_DIR)/%.c, $(BIN_DIR)/%.out, $(SOURCE))

.PHONY: all clean

all: $(TARGETS)

$(BIN_DIR):
	mkdir -p $(BIN_DIR)

# The pipe symbol is a separator to the order-only prerequisites.
# Quoting the docs @ 4.3 Types of Prerequisites:
#   Occasionally you may want to ensure that a prerequisite is built before a target,
#   but without forcing the target to be updated if the prerequisite is updated.
#   Order-only prerequisites are used to create this type of relationship.
#   Order-only prerequisites can be specified by placing a pipe symbol in the prerequisites list:
#   any prerequisites to the left of the pipe symbol are normal;
#   any prerequisites to the right are order-only.
$(BIN_DIR)/%.out: $(SRC_DIR)/%.c | $(BIN_DIR)
	$(CC) $(FLAGS) $< -o $@

# As for the hyphen, I'm quoting the docs @ 5.5 Errors in Recipes:
#   To ignore errors in a recipe line, write a ‘-’ at the beginning of the line’s text.
#   This causes make to continue even if rm is unable to remove a file.
clean:
	-rm -rf $(BIN_DIR)

