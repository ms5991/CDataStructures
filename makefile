# compiler
CC					:= gcc

# name of target file
TARGET 				:= main_bin
TEST_TARGET			:= test_bin

# directories and file info
INCDIR 				:= inc
SRCDIR				:= src
TARGETDIR 			:= bin
OBJDIR 				:= $(TARGETDIR)/obj
TESTDIR				:= tests
SRCEXT 				:= c
OBJEXT				:= o

# flags and libraries
CFLAGS 				:= -Wall -O3 -I $(INCDIR)
CFLAGS_TEST			:= -Wall -O3 -I $(INCDIR) -I $(TESTDIR)/$(INCDIR)
LIB 				:= -lm

# Want a project structure like:
#
# root
#	---- README
#	---- LICENSE
#	---- MAKEFILE
#	---- .gitignore
#	---- src
#			---- main.c
#			---- dir1
#				---- source1.c
#			---- ...
#			---- dirN
#				---- sourceN.c
#	---- tests
#			---- test_main.c
#			---- tests1
#				---- test1.c
#			---- ...
#			---- testsN
#				---- testN.c
#			---- bin
#				---- test_executable
#				---- obj
#					---- test_obj1.o
#					---- ...
#					---- test_objN.o
#	---- inc
#			---- header1.h
#			---- ...
#			---- headerN.h
#	---- bin
#			---- executable
#			---- obj
#				---- obj1.o
#				---- ...
#				---- objN.o
#

# find all src files that aren't in the root of the src directory
SOURCES 			:= $(shell find $(SRCDIR) -mindepth 2 -type f -name '*.$(SRCEXT)')

# find all src files that aren't in the root of the tests directory
TEST_SOURCES		:= $(shell find $(TESTDIR)/$(SRCDIR) -mindepth 2 -type f -name '*.$(SRCEXT)')

# find the src file that is in the root of the src directory -- will contain main
MAIN_SOURCE			:= $(shell find $(SRCDIR) -maxdepth 1 -type f -name '*.$(SRCEXT)')

# find the src file that is in the root of the tests directory -- will contain main for tests
TEST_MAIN_SOURCE	:= $(shell find $(TESTDIR)/$(SRCDIR) -maxdepth 1 -type f -name '*.$(SRCEXT)')

# name the object files
OBJECTS 			:= $(addprefix $(OBJDIR)/,$(notdir $(SOURCES:.$(SRCEXT)=.$(OBJEXT))))
TEST_OBJECTS		:= $(addprefix $(TESTDIR)/$(OBJDIR)/,$(notdir $(TEST_SOURCES:.$(SRCEXT)=.$(OBJEXT))))
TRY := $(OBJDIR)/%.$(OBJEXT)
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
$(TARGET): $(OBJECTS) $(MAIN_SOURCE)
	@echo "Linking..."
	$(CC) -o $(TARGETDIR)/$@ $^ $(LIB)

# compile source files under the subdirectories of src into .o object files
$(OBJDIR)/%.$(OBJEXT): $(SRCDIR)/%.$(SRCEXT)
	@echo "Compiling..."
	$(CC) $(CFLAGS) -c -o $@ $^

# the test program relies on the file containing main under tests/src and the objects
# link the object files into the executable
$(TEST_TARGET): $(OBJECTS) $(TEST_OBJECTS) $(TEST_MAIN_SOURCE)
	@echo "Linking tests..."
	$(CC) -o $(TARGETDIR)/$@ $^ $(LIB)

# compile test source files under the subdirectories of tests/src into .o object files
$(TESTDIR)/$(OBJDIR)/%.$(OBJEXT): $(TESTDIR)/$(SRCDIR)/%.$(SRCEXT)
	@echo "Compiling tests..."
	$(CC) $(CFLAGS_TEST) -c -o $@ $^

# build the tests
test: dirs $(TEST_TARGET)
	$(TARGETDIR)/$(TEST_TARGET)

# useful to debug makefile, see what variables eval to 
vars:
	@echo "CFLAGS:			$(CFLAGS)"
	@echo "CFLAGS_TEST:		$(CFLAGS_TEST)"
	@echo "OBJDIR:			$(OBJDIR)"
	@echo "TESTDIR:		$(TESTDIR)"
	@echo "SOURCES:		$(SOURCES)"
	@echo "MAIN_SOURCE:		$(MAIN_SOURCE)"
	@echo "OBJECTS:		$(OBJECTS)"
	@echo "TEST_SOURCES:		$(TEST_SOURCES)"
	@echo "TEST_MAIN_SOURCE:	$(TEST_MAIN_SOURCE)"
	@echo "TEST_OBJECTS:		$(TEST_OBJECTS)"
	@echo "TRY:		$(TRY)"

# remove obj and bin
clean:
	@echo "Cleaning..."
	rm -rf $(OBJDIR)
	rm -rf $(TARGETDIR)
	rm -rf $(TESTDIR)/$(TARGETDIR) 
	rm -rf $(TESTDIR)/$(OBJDIR)

.PHONY: clean