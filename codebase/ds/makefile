# Define the C compiler to be used
CC 			=	gcc

# Define the commands to be used
RM			= 	rm -f
MV			=	mv

# Define any compile time flags
CFLAGS		=	-Wall -g

# Define any directories containing header files
INCLUDES	=	-I./include/

# Define any library paths
LDFLAGS		=

# Define any library to link
LIBS		=

# Define the C source files
SRCS		=	src/dstrings.c

# Create object files for source files
SRC_OBJS	=	$(SRCS:.c=.o)
OBJS		=	obj/dstrings.o

# Define the C test files
TEST_SRCS	=	test/dstrings_test.c

# Create object files for test files
TEST_OBJS	=	$(TEST_SRCS:.c=.o)	

# Define the executable file names (test files)
TEST_NAMES	=	run/dstrings


# ----- Functionality -----
# Additional suffix replacement functionality from .c to .o
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create executables for test files and clean test objs
clean_test_run: clean_all_files test_run 

# Create executables for test files
test_run: src_run $(TEST_NAMES) clean_test_objs

# Create only object files for the source files
src_run: $(SRC_OBJS) move_src_objs

# Move source object files to obj directory
move_src_objs:
	$(MV) src/*.o obj/

# Make executables for each test file
$(TEST_NAMES) : $(TEST_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(LIBS) -o $(TEST_NAMES) $(TEST_OBJS) $(OBJS)

# Clean all machine code files
clean_all_files: clean_test_runs clean_src_objs clean_test_objs

# Clean test run files
clean_test_runs:
	$(RM) run/*

# Clean test obj files
clean_test_objs:
	$(RM) test/*.o

# Clean the source obj files
clean_src_objs:
	$(RM) obj/*
