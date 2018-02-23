# compiler
CC                  := gcc

# name of target file
TARGET              := main_bin
TEST_TARGET         := test_harness_bin

# directories and file info
INCDIR              := inc
SRCDIR              := src
TARGETDIR           := bin
OBJDIR              := obj
LIBDIR              := lib
TESTDIR             := tests
SRCEXT              := c
OBJEXT              := o
LIBS                :=

# flags and libraries
CFLAGS              += -Wall -O3 -I $(INCDIR)
LDFLAGS             += $(foreach librarydir, $(LIBDIR), -L$(librarydir))
LDFLAGS             += $(foreach library, $(LIBS), -l$(library))

# Want a project structure like:
#
# root
#   ---- README
#   ---- LICENSE
#   ---- MAKEFILE
#   ---- .gitignore
#   ---- src
#           ---- main.c
#           ---- source1.c
#           ---- ...
#           ---- sourceN.c
#   ---- tests
#           ---- test_main.c
#           ---- inc
#               ---- test1.h
#           --- test1.c
#           ---- ...
#           --- testN.c
#   ---- inc
#           ---- header1.h
#           ---- ...
#           ---- headerN.h
#   ---- bin
#           ---- executable
#   ---- obj
#           ---- obj1.o
#           ---- ...
#           ---- objN.o
#

# find all src files that aren't in the root of the src directory
SOURCES             := $(shell find $(SRCDIR) -type f -name '*.$(SRCEXT)')

# find all src files that aren't in the root of the tests directory
TEST_SOURCES        := $(shell find $(TESTDIR)/$(SRCDIR) -type f -name '*.$(SRCEXT)')

# name the object files
OBJECTS             := $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.$(SRCEXT)=.$(OBJEXT))))
TEST_OBJECTS        := $(addprefix $(OBJDIR)/,$(notdir $(TEST_SOURCES:.$(SRCEXT)=.$(OBJEXT))))

# compile target
all: dirs $(TARGET)

# default to all
default: all

# create obj and bin directories if they don't exist
dirs:
    mkdir -p $(TARGETDIR) 
    mkdir -p $(OBJDIR)
    mkdir -p $(TESTDIR)/$(TARGETDIR) 
    mkdir -p $(TESTDIR)/$(OBJDIR)

# the main program relies on the file containing main under src and the objects
# link the object files into the executable
$(TARGET): $(OBJECTS)
    @echo "Nothing to do here"
    @# $(CC) -o $(TARGETDIR)/$@ $^ $(LDFLAGS)

# compile source files under the subdirectories of src into .o object files
$(OBJDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
    @echo "Compiling"
    $(CC) $(CFLAGS) -c -o $@ $^

# for test, need additional flags and objects
$(TEST_TARGET): CFLAGS +=  -I $(TESTDIR)/$(INCDIR)
$(TEST_TARGET): OBJECTS += $(TEST_OBJECTS)

# the test program relies on the file containing main under tests/src and the objects
# link the object files into the executable
$(TEST_TARGET): $(OBJECTS) $(TEST_OBJECTS)
    @echo "Linking tests"
    $(CC) -o $(TARGETDIR)/$@ $^ $(LDFLAGS)

# compile test source files under the subdirectories of tests/src into .o object files
$(OBJDIR)/%.$(OBJEXT): $(TESTDIR)/$(SRCDIR)/%.$(SRCEXT)
    @echo "Compiling tests"
    $(CC) $(CFLAGS) -c -o $@ $^

# build the tests
test: dirs $(TEST_TARGET)
    $(TARGETDIR)/$(TEST_TARGET)

# useful to debug makefile, see what variables eval to 
vars:
    @echo "CFLAGS:          $(CFLAGS)"
    @echo "OBJDIR:          $(OBJDIR)"
    @echo "TARGETDIR:       $(TARGETDIR)"
    @echo "TESTDIR:     $(TESTDIR)"
    @echo "SOURCES:     $(SOURCES)"
    @echo "OBJECTS:     $(OBJECTS)"
    @echo "TEST_SOURCES:        $(TEST_SOURCES)"    
    @echo "TEST_OBJECTS:        $(TEST_OBJECTS)"

# remove obj and bin
clean:
    @echo "Cleaning..."
    rm -rf $(OBJDIR)
    rm -rf $(TARGETDIR)

.PHONY: clean vars test all