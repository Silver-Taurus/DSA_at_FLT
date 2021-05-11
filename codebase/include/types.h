#ifndef __TYPES__
#define __TYPES__

// Providing aliases for the data types to be used in the program
typedef int INT;
typedef char CHAR;

// Creating macros for format specifiers to be used in program
#define CHAR_FS "%c"
#define INT_FS "%d"
#define STR_FS "%s"
#define CHAR_FSS "%c "
#define INT_FSS "%d "
#define STR_FSS "%s "

/* ---------- Creating macros for constants to be used in program ---------- */
#define LEN 8

// Creating macros for functionality to be used in program
#define intout(val) fprintf(stdout, INT_FSS, val)
#define strout(str) fprintf(stdout, STR_FSS, str)
#define out(format, data) fprintf(stdout, format, data)
#define nl() fprintf(stdout, "\n")
#define flush_stdin() CHAR ip; do { ip = getchar(); } while (ip != '\n')

/* 
    Creating a boolean enum
*/
typedef enum boolen {
    false,
    true
} bool_t;

#endif