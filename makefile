# compiler
CC			:= gcc

# name of target file
TARGET 		:= main
TEST_TARGET	:= test

# directories and file info
INCDIR 		:= ./inc
SRCDIR		:= ./src
OBJDIR 		:= ./obj
TARGETDIR 	:= ./bin
SRCEXT 		:= c
OBJEXT		:= o

# flags and libraries
CFLAGS 		:= -Wall -O3 -I $(INCDIR)
LIB 		:= -lm

# find all src files
SOURCES 	:= $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')

# name the object files
OBJECTS 	:= $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SOURCES:.$(SRCEXT)=.$(OBJEXT)))

# compile target
all: dirs $(TARGET)

# default to all
default: all

# create obj and bin directories if they don't exist
dirs:
	mkdir -p $(TARGETDIR) 
	mkdir -p $(OBJDIR)

$(TARGET): $(OBJECTS)
	$(CC) -o $(TARGETDIR)/$@ $^ $(LIB)

$(OBJDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	$(CC) $(CFLAGS) -c -o $@ $^

test: dirs $(TEST_TARGET)
	$(TARGETDIR)/$(TEST_TARGET)

vars:
	echo "OBJECTS: $(OBJECTS)"
	echo "SOURCES: $(SOURCES)"

clean:
	-rm -rf $(OBJDIR)
	-rm -rf $(TARGETDIR)

.PHONY: clean