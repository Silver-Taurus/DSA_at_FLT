#include "dstrings.h"
#include <stdio.h>
#include <assert.h>

INT main (void) {
    str_t *string;

    /* ----- Check for create_string ----- */
    string = create_string();
    assert(string->cap == STR_LEN);
    assert(string->length == 0);
    
    /* ----- Check for extend_string ----- */
    extend_string(string);
    assert(string->cap == (STR_LEN * 2));
    assert(string->length == 0);
    
    /* ----- Check for input_string ----- */
    strout("Enter a string: ");
    input_string(string);   
    strout("Your input: "); 
    display_string(string);
    nl();

    /* ----- Check for check_pangram ----- */
    

    return 0;
}
