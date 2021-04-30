#include "dstring.h"
#include "dintarr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

str_t* create_string () {
    str_t *new_string = (str_t *) malloc(sizeof(str_t));
    
    // Initializing the fields
    new_string->cap = LEN;
    new_string->length = 0;
    
    // Creating the content field amd then initialize it
    new_string->content = (CHAR *) malloc(str_cap_size(new_string));
    memset(new_string->content, 0, str_cap_size(new_string));

    return new_string;
}

str_t* create_string_wc (CHAR *content) {
    // Create the string to store the given content
    str_t *new_string = (str_t *) malloc(sizeof(str_t));

    // Initialize the new string length field
    new_string->length = 0;
    
    // set the content
    set_string(new_string, content);

    return new_string;
}

void extend_string (str_t *string) {
    CHAR *new_content;

    // Update the string cap field to the twice the current cap
    string->cap *= 2;

    // Creating a new content and initialize it
    new_content = (CHAR *) malloc(str_cap_size(string));
    memset(new_content, 0, str_cap_size(string));

    // Copy the data of content field of string to new content
    for (INT index = 0; index < string->length; index++)
        new_content[index] = string->content[index];

    // Free the original content data and set new content to the field
    free(string->content);
    string->content = new_content;
}

void input_string (str_t *string) {
    CHAR input;

    // Take input from the console till a newline is hit
    // and if the length reaches cap, extend the string
    do {
        input = getchar();

        if (input == '\n')
            string->content[string->length] = '\0';
        else
            string->content[string->length++] = input;

        if (string->length == string->cap)
            extend_string(string);
    } while (input != '\n');
}

void append_string (str_t *string, CHAR *content) {
    INT index, length = 0;
    CHAR *new_content;

    // Find the length of the content
    calc_content_len(content, length);

    if (length > 0) {
        // Change the cap size to the required size
        set_str_cap(string, string->length + length + 1);

        // Create new content based on new string cap
        new_content = (CHAR *) malloc(str_cap_size(string));

        // Copy the contents of the string
        for (index = 0; index < string->length; index++)
            new_content[index] = string->content[index];

        // Free the old content and set the new content
        free(string->content);
        string->content = new_content;

        // Append the further content
        for (index = 0; index < length; index++)
            string->content[string->length++] = content[index];
        
        string->content[string->length] = '\0';
    }
}

void set_string (str_t *string, CHAR *content) {
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
    string->cap = LEN;

    // Change the cap size to the required size
    set_str_cap(string, length);
    
    // Create a new content
    string->content = (CHAR *) malloc(str_cap_size(string));

    // Initialize it with 0
    memset(string->content, 0, str_cap_size(string));
        
    // Now set the content to the string's content
    for (index = 0; index < length; index++)
        string->content[string->length++] = content[index];
    
    string->content[string->length] = '\0';
}

str_t* substr_btw_string (str_t *string, INT start_pos, INT end_pos) {
    INT index, length = 0;
    str_t *substr; 
   
    // Check for the valid start position, if not return NULL
    if (!check_substr_pos(string, start_pos))
        return NULL;

    // Check for the valid end position, if not return NULL
    if (!check_substr_pos(string, end_pos))
        return NULL;

    // Check for start and end position
    if (start_pos > end_pos)
        return NULL;

    // If positions are valid find the length of substr
    length = end_pos - start_pos + 1;

    // Create empty substr and initialize fields
    substr = (str_t *) malloc(sizeof(str_t));
    substr->length = 0;
    substr->cap = LEN;

    // Change the substr cap size to the required size
    set_str_cap(substr, length + 1);

    // Create and initialize content field
    substr->content = (CHAR *) malloc(str_cap_size(substr));

    // Fill the substr content
    for (index = 0; index < length; index++)
        substr->content[substr->length++] = string->content[start_pos + index];

    substr->content[substr->length] = '\0';

    return substr;
}

str_t* substr_from_string (str_t *string, INT start_pos) {
    // Get the substr_from using the substr_btw
    return substr_btw_string(string, start_pos, string->length - 1);
}


INT substr_in_string (str_t *string, str_t *substr, bool_t check_case) {
    INT index1, index2, pos = -1;

    // Find the substr in string and record the start position of substr in string
    for (index1 = 0, index2 = 0; index1 < string->length && index2 < substr->length; index1++) {
        // Check for the case
        if (check_case) {
            // If any match occurs start the substr index counter
            if (string->content[index1] == substr->content[index2]) {
                index2++;

                // Set the position to mark the start of substr in string if initially -1
                if (pos == -1)
                    pos = index1;           
            }

            // Reset the substr counter if any mismatch occurs and also reset the position
            else {
                index2 = 0;
                pos = -1;
            }    
        }

        // Irrespective of case
        else {
            // If any match occurs start the substr index counter
            if (tolower(string->content[index1]) == tolower(substr->content[index2])) {
                index2++;

                // Set the position to mark the start of substr in string if initially -1
                if (pos == -1)
                    pos = index1;
            }

            // Reset the substr counter if any mismatch occurs and also reset the position
            else {
                index2 = 0;
                pos = -1;
            }    
        }
    }

    // Check for position if the index1 is over and index2 is not over
    if (index2 != substr->length)
        pos = -1;

    return pos;
}

iarr_t* substr_all_in_string (str_t *string, str_t *substr, bool_t check_case) {
    INT index1, index2, pos = -1;
    iarr_t *int_arr = create_iarray();
    
    // Find the substr in string and record the start position of substr in string
    for (index1 = 0, index2 = 0; index1 < string->length; index1++) {
        // Check for the case
        if (check_case) {
            // If any match occurs start the substr index counter
            if (string->content[index1] == substr->content[index2]) {
                index2++;

                // Set the position to mark the start of substr in string if initially -1
                if (pos == -1)
                    pos = index1;          

                // If one occurence is recorded, reset for finding next occurence
                if (index2 == substr->length) {
                    append_iarray(int_arr, pos);
                    index2 = 0;
                    pos = -1;
                }
            }

            // Reset the substr counter if any mismatch occurs and also reset the position
            else {
                index2 = 0;
                pos = -1;
            }    
        }

        // Irrespective of case
        else {
            // If any match occurs start the substr index counter
            if (tolower(string->content[index1]) == tolower(substr->content[index2])) {
                index2++;

                // Set the position to mark the start of substr in string if initially -1
                if (pos == -1)
                    pos = index1;

                // If one occurence is recorded, reset for finding next occurence
                if (index2 == substr->length) {
                    append_iarray(int_arr, pos);
                    index2 = 0;
                    pos = -1;
                }
            }

            // Reset the substr counter if any mismatch occurs and also reset the position
            else {
                index2 = 0;
                pos = -1;
            }    
        }
    }

    // Check for the empty case
    if (!int_arr->length)
        return NULL;

    return int_arr;
}

bool_t insert_at_string (str_t *string, INT pos, CHAR *content) {
    INT index, length = 0;
    str_t *substr;
    CHAR *new_content;

    // Check for the valid postion value, if not return false
    if (!check_insert_pos(string, pos))
        return false;

    // If position is last - use append_string
    if (pos == string->length)
        append_string(string, content);

    // Proceed with the insertion of content
    else {
        // If the position is valid find the length of the content
        calc_content_len(content, length);

        // Perform the insertion if content is not empty
        if (length > 0) {
            // Get the temp string
            substr = substr_from_string(string, pos);

            // Change the cap size to the required size
            set_str_cap(string, string->length + length + 1);

            // Create new content
            new_content = (CHAR *) malloc(str_cap_size(string));

            // Form the new content before pos
            for (index = 0; index < pos; index++)
                new_content[index] = string->content[index];

            // Free the old content and store the new content and update length
            free(string->content);
            string->content = new_content;
            string->length = pos;

            // Form the new content from pos using given content
            for (index = 0; index < length; index++)
                string->content[string->length++] = content[index];

            // Form the new content for the previous remaining substr
            for (index = 0; index < substr->length; index++)
                string->content[string->length++] = substr->content[index];

            string->content[string->length] = '\0';
        }
    }

    return true;
}

void replace_ch_string (str_t *string, CHAR ch, CHAR new_ch, bool_t check_case) {
    INT index;

    // Replace all the occurences of a given character with a new character
    for (index = 0; index < string->length; index++) {
        // Check the case
        if (check_case) {
            if (string->content[index] == ch)
                string->content[index] = new_ch;
        }

        // Irrespective of case
        else {
            if (tolower(string->content[index]) == tolower(ch))
                string->content[index] = new_ch;
        }
    }
}

void remove_ch_string (str_t *string, CHAR ch, bool_t check_case) {
    INT index, length = 0;
    CHAR *new_content;

    // Create new content based on string's content
    new_content = (CHAR *) malloc(str_cap_size(string));

    // Store the content to new content after removing the given character
    for (index = 0; index < string->length; index++) {
        // Check the case
        if (check_case) {
            if (string->content[index] != ch)
                new_content[length++] = string->content[index];
        }

        // Irrespective of case
        else {
            if (tolower(string->content[index]) != tolower(ch))
                new_content[length++] = string->content[index];
        }
    }

    new_content[length] = '\0';

    // Free the old content and store the new content, also update the length
    free(string->content);
    string->content = new_content;
    string->length = length;
}

bool_t remove_btw_string (str_t *string, INT start_pos, INT end_pos) {
    INT index, length = 0;
    CHAR *new_content;

    // Check for the valid start position, if not return false
    if (!check_substr_pos(string, start_pos))
        return false;

    // Check for the valid end position, if not return false
    if (!check_substr_pos(string, end_pos))
        return false;

    // Check for start and end position
    if (start_pos > end_pos)
        return false;

    // Create new content to store removed string and initialize it
    new_content = (CHAR *) malloc(str_cap_size(string));
    memset(new_content, 0, str_cap_size(string));

    // Copy the required content to the new content
    for (index = 0; index < string->length; index++)
        if (!(index >= start_pos && index <= end_pos))
            new_content[length++] = string->content[index];

    new_content[length] = '\0';

    // Free the old content and store the new content, also update the length
    free(string->content);
    string->content = new_content;
    string->length = length;

    return true;
}

bool_t remove_from_string (str_t *string, INT pos) {
    // Perform remove_from using the remove_btw
    return remove_btw_string(string, pos, string->length - 1);
}

bool_t remove_at_string (str_t *string, INT pos) {
    INT index;
    CHAR *new_content;

    
}

void remove_in_string (str_t *string, str_t *substr, bool_t check_case) {
    INT pos, index, length = 0;
    CHAR *new_content;

    // Create new content based on string's content
    new_content = (CHAR *) malloc(str_cap_size(string));

    // Get the start position of substr in string
    pos = substr_in_string(string, substr, check_case);

    // Check for the case - if substr is not found in string
    if (pos == -1)
        return;

    // If the position is found make a new content with the removed substr
    for (index = 0; index < string->length; index++) {
        if (!(index >= pos && index < substr->length + pos))
            new_content[length++] = string->content[index];
    }

    new_content[length] = '\0';

    // Free the old content and store the new content
    free(string->content);
    string->content = new_content;
}

// void remove_all_in_string (str_t *string, str_t *substr, bool_t check_case);

INT check_pangram_lipogram (str_t *string, bool_t check_lipogram, bool_t print_missing) {
    // Declare the character mapping to mark the presence of each alphabet
    // and set it to false (0)
    bool_t mark[26] = {false};

    // Declare for indexing mark and lipogram check count
    INT index, count = 0;

    // Traverse string to set bytes for the occured alphabets
    for (index = 0; index < string->length; index++) {
        if (sc_is_Alpha(string, index))
            mark[sc_to_Index(string, index)] = true;

        else if (sc_is_alpha(string, index))
            mark[sc_to_index(string, index)] = true;
    }

    // Check for pangram and print if needed
    for (index = 0; index < 26; index++)
        if (!mark[index]) {
            count++;

            if (print_missing)
                chout('a' + index);
        }
    
    // Pangrammatic lipogram
    if (check_lipogram && count == 1)
        return 2;
    
    // Pangram
    if (!count)
        return 1;

    // Lipogram
    return 0;
}

void flush_stdin () {
    //Declare the input character
    CHAR input;

    // Flush the data remaining in the stdin input buffer
    do { input = getchar(); } while (input != '\n');
}
