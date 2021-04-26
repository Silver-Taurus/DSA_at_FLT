// Include files
#include "types.h"

#ifndef __DSTRING__
#define __DSTRING__

/*
    Structure for the dynamic string type
*/
typedef struct dstrings {
    CHAR *content;
    INT cap;
    INT length;
} str_t;

// Creating macros for constants to be used in program
#define STR_LEN 8

// Creating macros for functionality to be used in program
#define display_string(str) strout(str->content)

/* ---------- Function Prototypes ---------- */
// Function to create a new dynamic string
str_t* create_string ();

// Function to extend a dynamic string
void extend_string (str_t *string);

// Function to take input in a dynamic string
void input_string (str_t *string);

// Function to flush the stdin
void flush_stdin ();

#endif