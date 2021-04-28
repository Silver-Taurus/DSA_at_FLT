#include "dstrings.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define print_header(msg) printf("Case - %s: ", msg)

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
        "create_string",
        "extend_string",
        "input_string",
        "append_string",
        "set_string",
        "create_string_wd",
        "check_pangram"
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
    pass = 0, cases = 2;
    print_header(msgs[1]);
    extend_string(string);
    case_check(string->cap == (STR_LEN * 2));
    case_check(string->length == 0);
    result();
    
    /* ----- Check for input_string ----- */
    print_header(msgs[2]);
    nl();
    strout("Enter a string: ");
    input_string(string);   
    strout("Your input: "); 
    display_string(string);
    nl(); nl();

    /* ----- Check for append_string ----- */
    CHAR as[] = " Created by Silver...\n";
    print_header(msgs[3]);
    nl();
    strout("String to append: ");
    strout(as);
    strout("Appended string: ");
    append_string(string, " Created by Silver...\n");
    display_string(string);
    nl();

    /* ----- Check for set_string ----- */
    pass = 0, cases = 1;
    CHAR s[] = "Set the string";
    print_header(msgs[4]);
    set_string(string, s);
    case_check(strcmp(string->content, s) == 0);
    result();

    /* ----- Check for create_string_wd ----- */
    pass = 0; cases = 3;
    print_header(msgs[5]);
    free(string);
    string = create_string_wd(s);
    case_check(strcmp(string->content, s) == 0);
    case_check(string->cap == 16);
    case_check(string->length == 15);
    result();

    /* ----- Check for check_pangram ----- */
    pass = 0; cases = 2;
    print_header(msgs[6]);
    char ps[] = "The quick brown fox jumps over the lazy dog";
    case_check(check_pangram(string) == false);
    free(string);
    string = create_string_wd(ps);
    case_check(check_pangram(string) == true);
    result();

    return 0;
}
