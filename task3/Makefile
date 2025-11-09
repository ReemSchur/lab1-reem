# Compiler
CC := gcc

# Compiler flags (same as before, but without -m32 for Windows)
CFLAGS := -Wall -Wextra -std=c11 -O0 -g

# Our single target program
TARGET := menu_map

# The default rule
all: $(TARGET)

# Rule to build the target
$(TARGET): $(TARGET).c
	$(CC) $(CFLAGS) -o $(TARGET) $(TARGET).c

# Rule to clean up
clean:
	rm -f *.o $(TARGET) $(TARGET).exe

.PHONY: all clean