#include "dstrings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

str_t* create_string () {
    // Creating a new string
    str_t *new_string = (str_t *) malloc(sizeof(str_t));
    
    // Initializing the fields
    new_string->cap = STR_LEN;
    new_string->length = 0;
    
    // Creating the content field amd then initialize it
    new_string->content = (CHAR *) malloc(str_cap(new_string));
    memset(new_string->content, 0, str_cap(new_string));

    return new_string;
}

void extend_string (str_t *string) {
    // Decalaring new content, to be replaced with content field of string
    CHAR *new_content;

    // Update the string cap field to the twice the current cap
    string->cap *= 2;

    // Creating a new content and initialize it
    new_content = (CHAR *) malloc(str_cap(string));
    memset(new_content, 0, str_cap(string));

    // Copy the data of content field of string to new content
    for (INT index = 0; index < string->length; index++)
        new_content[index] = string->content[index];

    // Free the original content data and set new content to the field
    free(string->content);
    string->content = new_content;
}

void input_string (str_t *string) {
    // Declare the input character
    CHAR input;

    // Take input from the console till a newline is hit
    // and if the length reaches cap, extend the string
    do {
        input = getchar();

        if (input == '\n')
            string->content[string->length++] = '\0';
        else
            string->content[string->length++] = input;

        if (string->length == string->cap)
            extend_string(string);
    } while (input != '\n');
}

void append_string (str_t *string, CHAR *content) {
    // Declare the content index and content length
    INT index, length = 0;

    // Find the length of the content
    calc_content_len(content, length);

    // Check if the string needs to be extended
    if (string->length + length >= string->cap)
        extend_string(string);

    // Now append the content to the string's content
    if (string->length > 0)
        string->length -= 1;

    for (index = 0; index < length; index++)
        string->content[string->length++] = content[index];
}

void set_string (str_t *string, CHAR *content) {
    // Declare the content length tracker and content index
    INT length = 0, index;

    // Find the length of the content
    calc_content_len(content, length);

    // Check whether the string is empty or not, if not empty it
    if (string->length > 0) {
        free(string->content);

        // Initialize the length
        string->length = 0;
    }

    // Initialize the cap size for cap calculation
    string->cap = STR_LEN;

    // Change the cap size to the required size
    while (string->cap < length)
        string->cap *= 2;
    
    // Create a new content
    string->content = (CHAR *) malloc(str_cap(string));

    // Initialize it with 0
    memset(string->content, 0, str_cap(string));
        
    // Now set the content to the string's content
    for (index = 0; index < length; index++)
        string->content[index] = content[index];
}

str_t* create_string_wd (CHAR *content) {
    // Create the string with the given content
    str_t *new_string = (str_t *) malloc(sizeof(str_t));

    // Initialize the new string length field
    new_string->length = 0;

    // set the content
    set_string(new_string, content);

    return new_string;
}

bool_t check_pangram (str_t *string) {
    // Declare the character mapping to mark the presence of each alphabet
    // and set it to false (0)
    bool_t mark[26] = {false};

    // Declare for indexing mark
    INT index;

    // Traverse string to set bytes for the occured alphabets
    for (index = 0; index < string->length; index++) {
        if (sc_is_Alpha(string, index))
            mark[sc_to_Index(string, index)] = true;

        else if (sc_is_alpha(string, index))
            mark[sc_to_index(string, index)] = true;
    }

    // Check for pangram
    for (index = 0; index < 26; index++)
        if (!mark[index])
            return false;
    
    return true;
}

void flush_stdin () {
    //Declare the input character
    CHAR input;

    // Flush the data remaining in the stdin input buffer
    do { input = getchar(); } while (input != '\n');
}
