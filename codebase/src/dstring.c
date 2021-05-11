#include "dstring.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/* ---------- Main Functions ---------- */
str_t* create_string () {
    str_t *new_string = (str_t *) malloc(sizeof(str_t));
    
    // Initializing the fields
    new_string->cap = LEN;
    new_string->length = 0;
    new_string->content = __create_content(str_cap_size(new_string));

    return new_string;
}

str_t* create_string_wc (CHAR *content) {
    // Create the string to store the given content
    str_t *new_string = (str_t *) malloc(sizeof(str_t));

    // Initialize the new string length field and set the content
    new_string->length = 0;
    set_string(new_string, content);

    return new_string;
}

void extend_string (str_t *string) {
    CHAR *new_content;

    // Update the cap, create and fill new_content and save in string
    string->cap *= 2;
    new_content = __create_content(str_cap_size(string));
    __copy_to_new_content(new_content, string);
    __save_content_str(string, new_content, -1);
}

void input_string (str_t *string) {
    CHAR input;

    // Take input from the console till a newline is hit and if the
    // length reaches cap, extend the string
    do {
        input = getchar();

        if (input == '\n')
            set_str_end(string);
        else
            string->content[string->length++] = input;

        if (string->length == string->cap)
            extend_string(string);
    } while (input != '\n');
}

void append_string (str_t *string, CHAR *content) {
    INT length = 0;
    CHAR *new_content;

    // Find the length of the content
    calc_content_len(content, length);

    if (length > 0) {
        // Set cap to req. size, create and fill content and save in string
        set_str_cap(string, string->length + length + 1);
        new_content = __create_content(str_cap_size(string));
        __copy_to_new_content(new_content, string);
        __save_content_str(string, new_content, -1);
        
        // Copy remaining content to string
        __copy_content_to_string(string, content, length);       
        set_str_end(string);
    }
}

void set_string (str_t *string, CHAR *content) {
    INT length = 0;

    // Find the length of the content
    calc_content_len(content, length);

    // Check if string is empty or not, if not empty it and reset length
    if (string->length > 0) {
        free(string->content);
        string->length = 0;
    }

    // Initialize the cap size and set req. cap
    string->cap = LEN;
    set_str_cap(string, length);
    
    // Create a new content and set the content to string's content
    string->content = __create_content(str_cap_size(string));
    __copy_content_to_string(string, content, length);    
    set_str_end(string);;
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

    // Set the req. cap size and create content
    set_str_cap(substr, length);
    substr->content = __create_content(str_cap_size(substr));

    // Fill the substr content
    for (index = 0; index < length; index++)
        substr->content[substr->length++] = string->content[start_pos + index];

    set_str_end(substr);
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
    iarr_t *iarray = create_iarray();
    
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

                // If one occurrences is recorded, reset for finding next occurrences
                if (index2 == substr->length) {
                    append_val_iarray(iarray, pos);
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

                // If one occurrences is recorded, reset for finding next occurrences
                if (index2 == substr->length) {
                    append_val_iarray(iarray, pos);
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
    if (!iarray->length)
        return NULL;

    return iarray;
}

bool_t insert_at_string (str_t *string, INT pos, CHAR *content) {
    INT length = 0;
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

            // Set the req. cap size and create new_content
            set_str_cap(string, string->length + length);
            new_content = __create_content(str_cap_size(string));
            
            // Form the new content before pos and save it in string
            __copy_l_to_new_content(new_content, string, pos);
            __save_content_str(string, new_content, pos);

            // Form the content from given content and reamining substr
            __copy_content_to_string(string, content, length);
            __copy_string_to_string(string, substr);
            set_str_end(string);

            // Free the substr
            free(substr);
        }
    }

    return true;
}

void replace_ch_string (str_t *string, CHAR ch, CHAR new_ch, bool_t check_case) {
    INT index;

    // Replace all the occurrences of a given character with a new character
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

void replace_string (str_t *string, str_t *substr, str_t *new_string, bool_t check_case) {
    iarr_t *positions;
    INT index1, index2, index3, length = 0;
    CHAR *new_content;

    // Check for non empty substr and new_string
    if (substr->length > 0 && new_string->length > 0)
        positions = substr_all_in_string(string, substr, check_case);

    else
        return;

    // Check if found any match for substr in string, if not return
    if (positions == NULL)
        return;

    // Calculate the content length and update cap
    if (new_string->length > substr->length) {
        set_str_cap(string, string->length + (positions->length * (new_string->length - substr->length)));
    }

    // Create new content
    new_content = __create_content(str_cap_size(string));
    
    // Proceed with replacing all occurrences
    for (index1 = 0, index2 = 0; index1 < string->length; ) {
        // Copy string's content to new content
        if (index1 != positions->array[index2])
            new_content[length++] = string->content[index1++];
        
        // Content to be replaced
        else {
            for (index3 = 0; index3 < new_string->length; index3++)
                new_content[length++] = new_string->content[index3];
            
            index1 += substr->length;
            index2++;
        }
    }

    // Save the content to string and update length
    __save_content_str(string, new_content, length);
    set_str_end(string);
}

void remove_ch_string (str_t *string, CHAR ch, bool_t check_case) {
    INT index, length = 0;
    CHAR *new_content;

    // Create new content based on string's content
    new_content = __create_content(str_cap_size(string));

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

    // Save the new content with new length
    __save_content_str(string, new_content, length);
    set_str_end(string);
}

bool_t remove_btw_string (str_t *string, INT start_pos, INT end_pos) {
    INT length = 0;
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

    // Create new content, copy the req. content
    new_content = __create_content(str_cap_size(string));
    __copy_lrem_to_new_content(new_content, string, &length, start_pos, end_pos);

    // Save the new content with new length
    __save_content_str(string, new_content, length);
    set_str_end(string);

    return true;
}

bool_t remove_from_string (str_t *string, INT start_pos) {
    // Perform remove_from using the remove_btw
    return remove_btw_string(string, start_pos, string->length - 1);
}

bool_t remove_at_string (str_t *string, INT pos) {
    // Perform remove_at using the remove_btw
    return remove_btw_string(string, pos, pos);
}

void remove_in_string (str_t *string, str_t *substr, bool_t check_case) {
    INT pos, length = 0;
    CHAR *new_content;

    // Get the start position of substr in string
    pos = substr_in_string(string, substr, check_case);

    // Check for the case - if substr is not found in string
    if (pos == -1)
        return;

    // Create new content based on string's content
    new_content = __create_content(str_cap_size(string));

    // If the position is found fill new content and keep track of length
    __copy_lrem_to_new_content(new_content, string, &length, pos, substr->length + pos - 1);

    // Save the new content with new length
    __save_content_str(string, new_content, length);
    set_str_end(string);
}

void remove_all_in_string (str_t *string, str_t *substr, bool_t check_case) {
    iarr_t *positions;
    INT index1, length = 0, index2;
    CHAR *new_content;

    // Get the start position of substr in string
    positions = substr_all_in_string(string, substr, check_case);

    // Check for the case - if substr is not found in string
    if (positions == NULL)
        return;

    // Create new content based on string's content
    new_content = __create_content(str_cap_size(string));

    // If the position is found make a new content with the removed substr
    for (index1 = 0, index2 = 0; index1 < string->length; ) {
        // If the position not matches copt the string's content
        if (index1 != positions->array[index2])
            new_content[length++] = string->content[index1++];

        // If the position matches skip the substr
        else {
            index1 += substr->length;
            index2++;
        }
    }

    // Save the new content with new length
    __save_content_str(string, new_content, length);
    set_str_end(string);
}

INT count_uc_string (str_t *string) {
    INT index, count = 0;

    // Count for uppercase characters
    for (index = 0; index < string->length; index++)
        if (isupper(string->content[index]))
            count++;

    return count;
}

INT count_lc_string (str_t *string) {
    INT index, count = 0;

    // Count for lowercase characters
    for (index = 0; index < string->length; index++)
        if (islower(string->content[index]))
            count++;

    return count;
}

INT count_num_string (str_t *string) {
    INT index, count = 0;

    // Count for number characters
    for (index = 0; index < string->length; index++)
        if (isdigit(string->content[index]))
            count++;

    return count;
}

INT count_spc_string (str_t *string) {
    INT index, count = 0;

    // Count for special characters
    for (index = 0; index < string->length; index++)
        if (
            (string->content[index] >= 32 && string->content[index] <=47) 
            || (string->content[index] >= 58 && string->content[index] <= 64)
            || (string->content[index] >= 91 && string->content[index] <= 96)
            || (string->content[index] >= 123 && string->content[index] <= 126)
        )
            count++;

    return count;
}

// INT check_pangram_lipogram (str_t *string, bool_t check_lipogram, bool_t print_missing) {
//     // Declare the character mapping to mark the presence of each alphabet
//     // and set it to false (0)
//     bool_t mark[26] = {false};

//     // Declare for indexing mark and lipogram check count
//     INT index, count = 0;

//     // Traverse string to set bytes for the occured alphabets
//     for (index = 0; index < string->length; index++) {
//         if (sc_is_Alpha(string, index))
//             mark[sc_to_Index(string, index)] = true;

//         else if (sc_is_alpha(string, index))
//             mark[sc_to_index(string, index)] = true;
//     }

//     // Check for pangram and print if needed
//     for (index = 0; index < 26; index++)
//         if (!mark[index]) {
//             count++;

//             if (print_missing)
//                 chout('a' + index);
//         }
    
//     // Pangrammatic lipogram
//     if (check_lipogram && count == 1)
//         return 2;
    
//     // Pangram
//     if (!count)
//         return 1;

//     // Lipogram
//     return 0;
// }

// str_t* min_window_substr (str_t *string, str_t *pattern) {
//     INT hash_pat[256] = {0}, hash_str[256] = {0}, index, count = 0;
//     INT pos = 0, win_len,  min_len = INT_MAX, start = -1;

//     // If pattern is longer than the string, return NULL
//     if (string->length < pattern->length)
//         return NULL;

//     // Record the character occurrences in pattern
//     for (index = 0; index < pattern->length; index++)
//         hash_pat[(int) pattern->content[index]]++;

//     // Traverse the string, record characters, match the pattern and then minimize window
//     for (index = 0; index < string->length; index++) {
//         // Record the character occurence in string
//         hash_str[(int) string->content[index]]++;

//         // Check if the character of string is there in pattern and count of character
//         // occurred in string hash is less than or equal to that of pattern hash with
//         // the current has count, if so increase the substr count
//         if (hash_str[(int) string->content[index]] <= hash_pat[(int) string->content[index]])
//             count++;

//         // If the characters hash count are matched
//         if (count == pattern->length) {
//             // Try to minimize the window
//             while (
//                 (hash_str[(int) string->content[pos]] > hash_pat[(int) string->content[pos]])
//                 || (hash_str[(int) string->content[pos]] == 0)
//             ) {
//                 // If the character in string exists in pattern and its count is more than required
//                 if (hash_str[(int) string->content[pos]] > hash_pat[(int) string->content[pos]])
//                     hash_str[(int) string->content[pos]]--;

//                 pos++;
//             }

//             // Update the window length
//             win_len = index - pos + 1;
//             if (win_len < min_len) {
//                 min_len = win_len;
//                 start = pos;
//             }
//         }
//     }

//     // Get and reutrn the substr based on the start position of the min. window
//     return substr_btw_string(string, start, start + min_len - 1);
// }


/* ---------- Utility Functions ---------- */
CHAR* __create_content (size_t size) {
    CHAR *new_content = (CHAR *) malloc(size);
    memset(new_content, 0, size);

    return new_content;
}

void __copy_to_new_content (CHAR *new_content, str_t *string) {
    INT index;

    for (index = 0; index < string->length; index++)
        new_content[index] = string->content[index];
}

void __copy_l_to_new_content (CHAR *new_content, str_t *string, INT length) {
    INT index;

    for (index = 0; index < length; index++)
        new_content[index] = string->content[index];
}

void __copy_lrem_to_new_content (CHAR *new_content, str_t *string, INT *length, INT start_pos, INT end_pos) {
    INT index;
    
    for (index = 0; index < string->length; index++)
        if (!(index >= start_pos && index <= end_pos))
            new_content[(*length)++] = string->content[index];
}

void __copy_content_to_string (str_t *string, CHAR *content, INT length) {
    INT index;

    for (index = 0; index < length; index++)
        string->content[string->length++] = content[index]; 
}

void __copy_string_to_string (str_t *dest_string, str_t *src_string) {
    INT index;

    for (index = 0; index < src_string->length; index++)
        dest_string->content[dest_string->length++] = src_string->content[index];
}

void __save_content_str (str_t *string, CHAR *new_content, INT length) {
    free(string->content);
    string->content = new_content;

    if (length != -1)
        string->length = length;
}
