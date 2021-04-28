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
#define str_cap(str) (sizeof(CHAR) * str->cap)
#define calc_content_len(content, len) while (content[len++] != '\0');
#define display_string(str) strout(str->content)
#define c_is_Alpha(c) (c >= 'A' && c <= 'Z')
#define c_is_alpha(c) (c >= 'a' && c <= 'z')
#define sc_is_Alpha(str, index) c_is_Alpha(str->content[index])
#define sc_is_alpha(str, index) c_is_alpha(str->content[index])
#define c_to_Index(c) (c - 'A')
#define c_to_index(c) (c - 'a')
#define sc_to_Index(str, index) c_to_Index(string->content[index]) 
#define sc_to_index(str, index) c_to_index(string->content[index])

/* ---------- Function Prototypes ---------- */
// Function to create a new dynamic string
str_t* create_string ();

// Function to extend a dynamic string
void extend_string (str_t *string);

// Function to take input in a dynamic string
void input_string (str_t *string);

// Function to append data in a dynamic string
void append_string (str_t *string, CHAR *content);

// Function to set content of dynamic string
void set_string (str_t *string, CHAR *content);

// Function to create a new dynamic string with content
str_t *create_string_wd (CHAR *content);

// Function to check whether a string is a "Pangram"
bool_t check_pangram (str_t *string);

// Function to flush the stdin
void flush_stdin ();

#endif