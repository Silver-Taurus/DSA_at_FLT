#include "dstrings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

str_t* create_string () {
    // Creating a new string
    str_t *new_string = (str_t *) malloc(sizeof(str_t));
    
    // Initializing the fields
    new_string->cap = STR_LEN;
    new_string->length = 0;
    
    // Creating the content field amd then initialize it
    new_string->content = (CHAR *) malloc(sizeof(CHAR) * new_string->cap);
    memset(new_string->content, 0, sizeof(CHAR) * new_string->cap);

    return new_string;
}

void extend_string (str_t *string) {
    // Decalaring new content, to be replaced with content field of string
    CHAR *new_content;

    // Update the string cap field to the twice the current cap
    string->cap *= 2;

    // Creating a new content and initialize it
    new_content = (CHAR *) malloc(sizeof(CHAR) * string->cap);

    memset(new_content, 0, sizeof(CHAR) * string->cap);

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

void flush_stdin () {
    //Declare the input character
    CHAR input;

    // Flush the data remaining in the stdin input buffer
    do { input = getchar(); } while (input != '\n');
}
