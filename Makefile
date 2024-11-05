# Compiler
CC = gcc



# Executable name
TARGET = interfacc

# Source files (all .c files in the current directory)
SRCS = $(wildcard *.c)



# Rule to build the target executable
$(TARGET): 
	$(CC)  -o $(TARGET) $(SRCS) 
	./$(TARGET)



# Clean up build files
clean:
	rm -f $(OBJS) $(TARGET)
