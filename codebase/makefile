# ---------- Command related variables ----------
# Define the C compiler to be used
CC 				=	gcc

# Define the commands to be used
RM				= 	rm -f
MV				=	mv

# Define any compile time flags
CFLAGS			=	-Wall -g

# Define any directories containing header files
INCLUDES		=	-I./include/

# Define any library paths
LDFLAGS			=

# Define any library to link
LIBS			=

# Define fix part of execution command
EXEC			= 	$(CC) $(CFLAGS) $(INCLUDES) $(LDFLAGS) $(LIBS) -o


# ---------- Source file related varaibles ----------
# Define the C source files
COM_SRCS		=	src/unit_test.c
DSTRING_SRC		=	src/dstring.c
DINTARR_SRC		=	src/dintarr.c

# Define the C source files collecatably
ALL_SRCS		=	$(COM_SRCS)			\
					$(DSTRING_SRC)		\
					$(DINTARR_SRC)

# Define the C object files for the source files
# Also, creates object files from the source due to the
# predefined .c.o functionality of GNU make which can be
# overridden as done below
OBJS			=	$(ALL_SRCS:.c=.o)


# ---------- Test files related variables ----------
# Define the C test files
DSTRING_TSRC	=	test/dstring_test.c
DINTARR_TSRC 	= 	test/dintarr_test.c

# Define the executable test files
DSTRING_TNAME	=	run/dstring_test
DINTARR_TNAME	=	run/dintarr_test

# Create required object files of source for test file
DSTRING_TSOBJS	=	$(COM_SRCS:.c=.o)			\
					$(DSTRING_SRC:.c=.o)		\
					$(DINTARR_SRC:.c=.o)

DINTARR_TSOBJS	=	$(COM_SRCS:.c=.o)			\
					$(DINTARR_SRC:.c=.o)

# Define the new object file locations for test files
DSTRING_TOBJS	=	$(DSTRING_TSOBJS:src/%.o=obj/%.o)
DINTARR_TOBJS	=	$(DINTARR_TSOBJS:src/%.o=obj/%.o)



# ---------- Compile and Lib. functionality ----------
# Additional suffix replacement functionality from .c to .o
# providing cflags and includes to the compile command as well as
# move the object files to obj directory
.c.o:
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	$(MV) $@ obj/

# Create only object files for the source files
src_run: $(OBJS)


# ---------- Exec. file functionality ----------
run_dstring_test: $(DSTRING_TSOBJS) $(DSTRING_TOBJS)
	$(EXEC) $(DSTRING_TNAME) $(DSTRING_TSRC) $(DSTRING_TOBJS)

run_dintarr_test: $(DINTARR_TSOBJS) $(DINTARR_TOBJS)
	$(EXEC) $(DINTARR_TNAME) $(DINTARR_TSRC) $(DINTARR_TOBJS)


# ---------- Clean functionality ----------
# Clean all machine code files
clean_all_files: clean_run clean_obj

# Clean test run files
clean_run:
	$(RM) run/*

# Clean the source obj files
clean_obj:
	$(RM) obj/*
