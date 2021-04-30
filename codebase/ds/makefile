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
SRCS		=	src/dstring.c		\
				src/dintarr.c

# Define the C object files for the source files
# Also, creates object files from the source due to the
# predefined .c.o functionality of GNU make which can be
# overridden as done below
SRC_OBJS	=	$(SRCS:.c=.o)

# Define the C object files in a different location
OBJS 		= 	$(SRC_OBJS:src/%.o=obj/%.o)

# Define the C test files
TEST_SRCS	=	test/dstring_test.c

# Create object files for test files
TEST_OBJS	=	$(TEST_SRCS:.c=.o)	

# Define the executable file names (test files) based on test
# soruce files
TEST_NAMES	=	run/dstring_test


# ----- Functionality -----
# Additional suffix replacement functionality from .c to .o
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create object files from source files as well as make
# executable for test files
all_run: src_run test_run

# Create executables for test files
test_run: $(TEST_NAMES) clean_test_objs

# Create only object files for the source files
src_run: $(SRC_OBJS) $(OBJS) $(TEST_NAMES)

# Create object files in the obj folder - perform move operation 
$(OBJS):
	$(MV) src/*.o obj/

# Make executables for each test source file
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
