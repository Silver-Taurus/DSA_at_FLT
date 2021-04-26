#include "dstrings.h"
#include <stdio.h>
#include <assert.h>

INT main (void) {
    str_t *string;

    /* ----- Check for create_string ----- */
    string = create_string();
    assert(string->cap == STR_LEN);
    assert(string->length == 0);
    assert(sizeof(string->content) == (sizeof(CHAR) * STR_LEN));

    /* ----- Check for extend_string ----- */
    extend_string(string);
    assert(string->cap == (STR_LEN * 2));
    out(INT_FS, string->length);
    //assert(string->length == STR_LEN-1);
    //assert(sizeof(string->content) == (sizeof(CHAR) * STR_LEN * 2));

    /* ----- Check for input_string ----- */
    strout("Enter a string: ");
    input_string(string);   
    strout("Your input: "); 
    display_string(string);
    nl();

    return 0;
}
