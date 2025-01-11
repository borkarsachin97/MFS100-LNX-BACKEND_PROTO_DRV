# Makefile

# Compiler
CC = gcc

# Compiler flags
CFLAGS = `pkg-config --cflags gtk+-3.0`
LIBS = `pkg-config --libs gtk+-3.0 libusb-1.0`

# Source files
SRC = mfs100.c usbComm.c usbComm.h


# Object files
OBJ = $(SRC:.c=.o)

# Executable name
TARGET = mfs100

# Default target: compile the program
all: $(TARGET)

# Rule to build the target executable
$(TARGET): $(OBJ)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJ) $(LIBS)

# Rule to compile source files into object files
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Clean up the build (object files and executable)
clean:
	rm -f $(OBJ) $(TARGET)

run: $(TARGET)
	sudo ./mfs100

# Phony targets
.PHONY: all clean


