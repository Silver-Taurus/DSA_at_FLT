// Include files
#include "types.h"
#include "dintarr.h"

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

/* ---------- Creating macros for functionality to be used in program ---------- */
#define str_cap_size(str) (sizeof(CHAR) * str->cap)

#define calc_content_len(content, len) while (content[len] != '\0') len++
#define set_str_cap(str, len) while (str->cap <= len) str->cap *= 2

#define check_substr_pos(str, pos) (pos >= 0 && pos < str->length)
#define check_insert_pos(str, pos) (pos >= 0 && pos <= str->length + 1)

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

// Function to create a new dynamic string with content
str_t* create_string_wc (CHAR *content);

// Function to extend a dynamic string
void extend_string (str_t *string);

// Function to take input in a dynamic string
void input_string (str_t *string);

// Function to append data in a dynamic string
void append_string (str_t *string, CHAR *content);

// Function to set content of dynamic string
void set_string (str_t *string, CHAR *content);

// Function to get substr between a start pos and end pos including the end pos in a dynamic string
str_t* substr_btw_string (str_t *string, INT start_pos, INT end_pos);

// Function to get substr from a start positon in a dynamic string
str_t* substr_from_string (str_t *string, INT start_pos);

// Function to find the start pos of first occurence of substr in a dynamic string and also
// check for the case
INT substr_in_string (str_t *string, str_t *substr, bool_t check_case);

// Function to find the start pos of all the occurences of substr in  a dynamic string
iarr_t* substr_all_in_string (str_t *string, str_t *substr, bool_t check_case);

// Function to insert data at some position in a dynamic string
bool_t insert_at_string (str_t *string, INT pos, CHAR *content);

// Function to replace all character occurences with a new character in a dynamic string and also
// check for the case
void replace_ch_string (str_t *string, CHAR ch, CHAR new_ch, bool_t check_case);

// Function to remove all character occurences in a dynamic string and also check for the case
void remove_ch_string (str_t *string, CHAR ch, bool_t check_case);

// Function to remove between a start pos and end pos including the end pos in a dynamic string
bool_t remove_btw_string (str_t *string, INT start_pos, INT end_pos);

// Function to remove from a start position in a dynamic string
bool_t remove_from_string (str_t *string, INT pos);

// Function to remove a character at a position in a dynamic string
bool_t remove_at_string (str_t *string, INT pos);

// Function to remove first occurence of substr in a dynamic string and also check for the case
void remove_in_string (str_t *string, str_t *substr, bool_t check_case); 

// Function to remove all the occurences of substr in a dynamic string and also check the case
void remove_all_in_string (str_t *string, str_t *substr, bool_t check_case);

// Function to check whether a string is a "Pangram" or "holoalphabetic" as well as a
// "pangrammatic liporgram" and print the missing alphabets if asked
INT check_pangram_lipogram (str_t *string, bool_t check_lipogram, bool_t print_missing);

// Function to flush the stdin
void flush_stdin ();

#endif