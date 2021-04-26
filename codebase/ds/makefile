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
OBJS		=	$(SRCS:.c=.o)

# Define the C test files
TEST_SRCS	=	test/dstrings_test.c

# Create object files for test files
TEST_OBJS	=	$(TEST_SRCS:.c=.o)	

# Define the executable file names (test files)
TEST_NAMES	=	run/dstrings

# Define soruce object files location
SRC_OBJ_LOC	=	obj/	


# ----- Functionality -----
# Additional suffix replacement functionality from .c to .o
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Create executables for test files
test_run: src_run $(TEST_NAMES)

# Create only object files for the source files
src_run: $(OBJS) $(GRP_OBJS)

$(GRP_OBJS): $(OBJS)
	$(MV) src/*.o obj/

# Make executables for each test file
$(TEST_NAMES) : $(TEST_OBJS)
	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(LIBS) -o $(TEST_NAMES) $(TEST_OBJS) $(GRP_OBJS)
