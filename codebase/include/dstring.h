// Include files
#include "types.h"
#include "dintarr.h"
#include <stddef.h>

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
#define display_string(str) strout(str->content)

#define str_cap_size(str) (sizeof(CHAR) * str->cap)
#define set_str_cap(str, len) while (str->cap <= len) str->cap *= 2
#define set_str_end(str) str->content[str->length] = '\0'
#define calc_content_len(content, len) while (content[len] != '\0') len++
#define check_substr_pos(str, pos) (pos >= 0 && pos < str->length)
#define check_insert_pos(str, pos) (pos >= 0 && pos <= str->length + 1)

#define c_is_Alpha(c) (c >= 'A' && c <= 'Z')
#define c_is_alpha(c) (c >= 'a' && c <= 'z')
#define sc_is_Alpha(str, index) c_is_Alpha(str->content[index])
#define sc_is_alpha(str, index) c_is_alpha(str->content[index])

#define c_to_Index(c) (c - 'A')
#define c_to_index(c) (c - 'a')
#define sc_to_Index(str, index) c_to_Index(string->content[index]) 
#define sc_to_index(str, index) c_to_index(string->content[index])


/* ---------- Main Function Prototypes ---------- */
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

// Function to find the start pos of first occurrence of substr in a dynamic string and also
// check for the case
INT substr_in_string (str_t *string, str_t *substr, bool_t check_case);

// Function to find the start pos of all the occurrences of substr in  a dynamic string
iarr_t* substr_all_in_string (str_t *string, str_t *substr, bool_t check_case);

// Function to insert data at some position in a dynamic string
bool_t insert_at_string (str_t *string, INT pos, CHAR *content);

// Function to replace all character occurrences with a new character in a dynamic string and also
// check for the case
void replace_ch_string (str_t *string, CHAR ch, CHAR new_ch, bool_t check_case);

// Function to replace all occurences of substr in a dynamic string and also check for the case
void replace_string (str_t *string, str_t* substr, str_t* new_string, bool_t check_case);

// Function to remove all character occurrences in a dynamic string and also check for the case
void remove_ch_string (str_t *string, CHAR ch, bool_t check_case);

// Function to remove between a start pos and end pos including the end pos in a dynamic string
bool_t remove_btw_string (str_t *string, INT start_pos, INT end_pos);

// Function to remove from a start position in a dynamic string
bool_t remove_from_string (str_t *string, INT start_pos);

// Function to remove a character at a position in a dynamic string
bool_t remove_at_string (str_t *string, INT pos);

// Function to remove first occurrence of substr in a dynamic string and also check for the case
void remove_in_string (str_t *string, str_t *substr, bool_t check_case); 

// Function to remove all the occurrences of substr in a dynamic string and also check the case
void remove_all_in_string (str_t *string, str_t *substr, bool_t check_case);

// Function to count uppercase characters in string
INT count_uc_string (str_t *string);

// Function to count lowercase characters in string
INT count_lc_string (str_t *string);

// Function to count number characters in string
INT count_num_string (str_t *string);

// Function to count special characters in string
INT count_spc_string (str_t *string);


/* ---------- Utility Function Prototypes ---------- */
// Function to create and initialize the content to 0
CHAR* __create_content (size_t size);

// Function to copy the content of string to a new content
void __copy_to_new_content (CHAR *new_content, str_t *string);

// Function to copy the content of string to a new content upto a length
void __copy_l_to_new_content (CHAR *new_content, str_t *string, INT length);

// Function to copy the content of string to a new content except a ceratin length portion
// between start_pos and end_pos and also record the length of new content
void __copy_lrem_to_new_content (CHAR *new_content, str_t *string, INT *length, INT start_pos, INT end_pos);

// Function to copy the content to a string's content
void __copy_content_to_string (str_t *string, CHAR *content, INT length);

// Function to copy string to another string
void __copy_string_to_string (str_t *dest_string, str_t *src_string);

// Function to free the old content and save the new content to string and update length
void __save_content_str (str_t *string, CHAR *new_content, INT length);

#endif