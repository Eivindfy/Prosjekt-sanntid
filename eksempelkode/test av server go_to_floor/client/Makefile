# Compiler flags go here.
CFLAGS = -std=c99 -g -Wall -O2 -I . -MMD

# Linker flags go here.
LDFLAGS = -lpthread -g -lm

# list of sources
ELEVSRC = client.c clienttest.c

# program executable file name.
TARGET = test

# top-level rule, to compile everything.
all: $(TARGET)

# Define dependencies
DEPS = $(shell find -name "*.d")

# Define all object files.
ELEVOBJ = $(ELEVSRC:.c=.o)

# rule to link the program
$(TARGET): $(ELEVOBJ)
	gcc $^ -o $@ $(LDFLAGS)

# Compile: create object files from C source files.
%.o : %.c
	gcc $(CFLAGS) -c  $< -o $@ 

# Include dependencies, if any.
-include $(DEPS) foo

# rule for cleaning re-compilable files.
clean:
	rm -f $(TARGET) $(ELEVOBJ) $(DEPS)

rebuild:	clean all

# 
run: rebuild
	./$(TARGET)
	make clean


.PHONY: all rebuild clean run


#Martin Korsgaard, 2006
#Edited by Anders Petersen, 2014
