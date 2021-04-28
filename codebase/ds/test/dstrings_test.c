#include "dstrings.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>

#define print_header(msg) printf("%s: ", msg)

#define case_check(expr) if (expr) pass++
#define result() if (pass == cases) p_success(); else p_failure(); count()

#define p_success() printf("SUCCESS... ")
#define p_failure() printf("FAILURE... ")
#define count() printf("%d / %d cases passed.\n\n", pass, cases)

/*
    Main driver code (must include)
        - int pass
        - int cases
*/
INT main (void) {
    // Variable to check on
    str_t *string;

    // Other header msgs
    CHAR *msgs[] = {
        "Check for case - create_string"
    };

    // Check pass counter
    INT pass, cases;

    /* ----- Check for create_string ----- */
    pass = 0, cases = 2;
    print_header(msgs[0]);
    string = create_string();
    case_check(string->cap == STR_LEN);
    case_check(string->length == 0);
    result();
    

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

    /* ----- Check for append_string ----- */
    append_string(string, "\nCreated by Silver...\n");
    display_string(string);
    nl();

    return 0;
}
