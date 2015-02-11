# Which compiler to use
CC = gcc

# Compiler flags go here.
CFLAGS = -g -Wall 

# Linker flags go here.
LDFLAGS = -lm 
#-lcomedi -lm

# list of sources
SOURCE = testelev.c test.c queue.c hwAndIo.c  timer.c 

# program executable file name.
TARGET = test

# top-level rule, to compile everything.
all: $(TARGET)

# Define all object files.
OBJECTS = $(SOURCE:.c=.o)

# Compile: create object files from C source files.
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ 

# rule to link the program
$(TARGET): $(OBJECTS)
	$(CC)  $(SOURCE)  -o test -std=c99
#$(LDFLAGS) $(CFLAGS)
# Compile: create object files from C source files.
%.o : %.c
	$(CC) $(CFLAGS) -c $< -o $@ -std=c99

# rule for cleaning re-compilable files.
clean:
	rm -f $(TARGET) $(OBJECTS)

rebuild:	clean all

.PHONY: all rebuild clean


#Martin Korsgaard, 2006
