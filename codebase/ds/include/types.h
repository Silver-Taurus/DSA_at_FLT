#ifndef __TYPES__
#define __TYPES__

// Providing aliases for the data types to be used in the program
typedef int INT;
typedef char CHAR;

// Creating macros for format specifiers to be used in program
#define CHAR_FS "%c"
#define INT_FS "%d"
#define STR_FS "%s"

/* ---------- Creating macros for constants to be used in program ---------- */
#define LEN 8

// Creating macros for functionality to be used in program
#define chout(ch) fprintf(stdout, CHAR_FS, ch)
#define strout(str) fprintf(stdout, STR_FS, str)
#define out(format, data) fprintf(stdout, format, data)
#define nl() fprintf(stdout, "\n")

// Creating a boolean enum
typedef enum boolen {
    false,
    true
} bool_t;

#endif