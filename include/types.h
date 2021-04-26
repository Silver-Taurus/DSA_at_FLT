#ifndef __TYPES__
#define __TYPES__

// Providing aliases for the data types to be used in the program
typedef int INT;
typedef char CHAR;

// Creating macros for format specifiers to be used in program
#define CHAR_FS "%c"
#define INT_FS "%d"
#define STR_FS "%s"

// Creating macros for functionality to be used in program
#define STROUT(str) fprintf(stdout, str)
#define OUT(format, data) fprintf(stdout, format, data)

#endif