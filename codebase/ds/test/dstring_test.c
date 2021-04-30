#include "dstring.h"
#include "dintarr.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* ---------- Macros to define the constants to be used ---------- */
#define TCASES 8
#define COLOR_NRM "\x1B[0m"
#define COLOR_ERR "\x1B[31m"
#define COLOR_OK "\x1B[32m"

/* ---------- Global Variables ---------- */
INT cases, pass, idx;
CHAR failed_cases[8];

/* ---------- Macros to define functionalities to be used ---------- */
#define print_header(msg) fprintf(stdout, "Case - %-20s: ", msg)
#define fc_init() bzero(failed_cases, TCASES)
#define test_case(expr, idx) if (expr) pass++; else failed_cases[idx] = 1; idx++

#define p_success() fprintf(stdout, "%s%20s%s", COLOR_OK, "SUCCESS... ", COLOR_NRM)
#define p_failure() fprintf(stdout, "%s%20s%s", COLOR_ERR, "FAILURE... ", COLOR_NRM)
#define count() fprintf(stdout, "%d / %d cases passed.", pass, cases)


/* ---------- Utility Functions for testing ---------- */
void show_fail_status () {
    out("%10s", "Case ");

    for (int i = 0; i < cases; i++)
        if (failed_cases[i])
            fprintf(stdout, "%s%d%s ", COLOR_ERR, i + 1, COLOR_NRM);
    
    strout("failed.");
    nl(); nl();
}

void show_result () {
    if (pass == cases) {
        p_success();
        count();
        nl(); nl();
    }

    else {
        p_failure();
        count();
        show_fail_status();
    }
}

/*
    Main driver code (must include)

        Note: Maximum test cases for any function is taken as 8.
*/
INT main (void) {
    // Variable to check on
    str_t *string;

    // Other header msgs
    CHAR *msgs[] = {
        "create_string",
        "create_string_wc",
        "extend_string",
        "input_string",
        "append_string",
        "set_string",
        "substr_btw_string",
        "substr_from_string",
        "substr_in_string",
        "substr_all_in_string",
        "insert_at_string",
        "replace_ch_string",
        "remove_ch_string",
        "remove_btw_string",
        "remove_from_string",
        "remove_in_string",
        "check_pangram_lipogram"
    };


    /* ----- Check for create_string ----- */
    pass = 0, cases = 2, idx = 0;
    fc_init();
    print_header(msgs[0]);

    string = create_string();
    
    test_case(string->cap == LEN, idx);                         // case-1
    test_case(string->length == 0, idx);                        // case-2
    show_result();


    /* ----- Check for create_string_wd ----- */
    pass = 0; cases = 3, idx = 0;
    print_header(msgs[1]);
    
    CHAR s1[] = "Set the string";
    free(string);
    string = create_string_wc(s1);
    
    test_case(strcmp(string->content, s1) == 0, idx);           // case-1
    test_case(string->cap == 16, idx);                          // case-2
    test_case(string->length == 14, idx);                       // case-3
    show_result();


    /* ----- Check for extend_string ----- */
    pass = 0, cases = 2, idx = 0;
    print_header(msgs[2]);

    INT cap = string->cap, len = string->length;
    extend_string(string);
    
    test_case(string->cap == cap * 2, idx);                     // case-1
    test_case(string->length == len, idx);                      // case-2
    show_result();
    

    /* ----- Check for input_string ----- */
    print_header(msgs[3]);

    free(string);
    string = create_string();
    nl();

    strout("Enter a string: ");
    input_string(string);   

    strout("Your input: "); 
    display_string(string);
    nl(); nl();


    /* ----- Check for append_string ----- */
    print_header(msgs[4]);

    CHAR as[] = " Created by Silver...\n";

    nl();
    strout("String to append: ");
    strout(as);

    append_string(string, as);

    strout("Appended string: ");
    display_string(string);
    nl();


    /* ----- Check for set_string ----- */
    pass = 0, cases = 3, idx = 0;
    print_header(msgs[5]);

    CHAR s2[] = "Testing set string";
    set_string(string, s2);

    test_case(strcmp(string->content, s2) == 0, idx);           // case-1
    test_case(string->cap == 32, idx);                          // case-2
    test_case(string->length == 18, idx);                       // case-3
    show_result();


    /* ----- Check for substr_btw_string ----- */
    pass = 0; cases = 6, idx = 0;
    print_header(msgs[6]);

    CHAR s3[] = "ing set str", s4[] = "t";
    str_t *substr = substr_btw_string(string, -1, 8);
    test_case(substr == NULL, idx);                             // case-1

    free(substr);
    substr = substr_btw_string(string, 0, 19);
    test_case(substr == NULL, idx);                             // case-2

    free(substr);
    substr = substr_btw_string(string, 4, 3);
    test_case(substr == NULL, idx);                             // case-3

    free(substr);
    substr = substr_btw_string(string, 4, 14);
    test_case(strcmp(substr->content, s3) == 0, idx);           // case-4

    free(substr);
    substr = substr_btw_string(string, 0, 17);
    test_case(strcmp(substr->content, s2) == 0, idx);           // case-5

    free(substr);
    substr = substr_btw_string(string, 3, 3);
    test_case(strcmp(substr->content, s4) == 0, idx);           // case-6
    show_result();


    /* ----- Check for substr_from_string ----- */
    pass = 0; cases = 6, idx = 0;
    print_header(msgs[7]);

    CHAR s5[] = "g";

    free(substr);
    substr = substr_from_string(string, 0); 
    test_case(strcmp(substr->content, s2) == 0, idx);           // case-1
    test_case(substr->length == 18, idx);                       // case-2

    free(substr);
    substr = substr_from_string(string, -1);
    test_case(substr == NULL, idx);                             // case-3

    free(substr);
    substr = substr_from_string(string, 18);
    test_case(substr == NULL, idx);                             // case-4
    
    free(substr);
    substr = substr_from_string(string, 17);
    test_case(strcmp(substr->content, s5) == 0, idx);           // case-5
    test_case(substr->length == 1, idx);                        // case-6
    show_result();


    /* ----- Check for substr_in_string ----- */
    pass = 0; cases = 4, idx = 0;
    print_header(msgs[8]);

    INT pos;    
    CHAR s6[] = "Set the new string finally";

    free(string);
    free(substr);
    string = create_string_wc(s6);
    substr = create_string_wc("new");
    pos = substr_in_string(string, substr, true);
    test_case(pos == 8, idx);                                   // case-1
    
    free(substr);
    substr = create_string_wc("set");
    pos = substr_in_string(string, substr, false);
    test_case(pos == 0, idx);                                   // case-2
    
    pos = substr_in_string(string, substr, true);
    test_case(pos == -1, idx);                                  // case-3
    
    free(substr);
    substr = create_string_wc("llys");
    pos = substr_in_string(string, substr, false);
    test_case(pos == -1, idx);                                  // case-4
    show_result();


    /* ----- Check for substr_all_in_string ----- */
    pass = 0; cases = 8, idx = 0;
    print_header(msgs[9]);

    iarr_t *positions;
    free(substr);
    substr = create_string_wc("in");
    positions = substr_all_in_string(string, substr, true);
    test_case(positions->length == 2, idx);                     // case-1
    test_case(positions->cap == LEN, idx);                      // case-2
    test_case(positions->arr[0] == 15, idx);                    // case-3
    test_case(positions->arr[1] == 20, idx);                    // case-4
    
    free(substr);
    substr = create_string_wc("set");
    positions = substr_all_in_string(string, substr, false);
    test_case(positions->length == 1, idx);                     // case-5
    test_case(positions->arr[0] == 0, idx);                     // case-6

    positions = substr_all_in_string(string, substr, true);
    test_case(positions == NULL, idx);                          // case-7
    
    free(substr);
    substr = create_string_wc("llys");
    positions = substr_all_in_string(string, substr, false);
    test_case(positions == NULL, idx);                          // case-8
    
    free(substr);
    show_result();


    /* ----- Check for insert_at_string ----- */
    pass = 0; cases = 6, idx = 0;
    print_header(msgs[10]);

    CHAR s7[] = "Set the string";
    CHAR s8[] = "new ";
    CHAR s9[] = "Set the new string";
    CHAR s10[] = " finally";

    free(string);
    string = create_string_wc(s7);

    test_case(insert_at_string(string, 8, s8) == true, idx);    // case-1
    test_case(strcmp(string->content, s9) == 0, idx);           // case-2
    test_case(string->length == 18, idx);                       // case-3

    test_case(insert_at_string(string, 18, s10) == true, idx);  // case-4
    test_case(strcmp(string->content, s6) == 0, idx);           // case-5
    test_case(string->length == 26, idx);                       // case-6
    show_result();


    /* ----- Check for replace_ch_string ----- */
    pass = 0; cases = 6, idx = 0;
    print_header(msgs[11]);
    
    CHAR s11[] = "Set the new gtring finally";
    CHAR s12[] = "Get the new gtring finally";
    CHAR s13[] = "Het the new HtrinH finally";
    CHAR c1 = 's', c2 = 'g', c3 = 'G', c4 = 'G', c5 = 'H';
   
    replace_ch_string(string, c1, c2, true);
    test_case(strcmp(string->content, s11) == 0, idx);          // case-1
    test_case(string->length == 26, idx);                       // case-2
    
    replace_ch_string(string, c1, c3, false);
    test_case(strcmp(string->content, s12) == 0, idx);          // case-3
    test_case(string->length == 26, idx);                       // case-4

    replace_ch_string(string, c4, c5, false);
    test_case(strcmp(string->content, s13) == 0, idx);          // case-5
    test_case(string->length == 26, idx);                       // case-6
    show_result();


    /* ----- Check for remove_ch_string ----- */
    pass = 0; cases = 6, idx = 0;
    print_header(msgs[12]);
    
    CHAR s14[] = "et the new trin finally";
    CHAR s15[] = "et te new trin finally";

    remove_ch_string(string, c5, true);
    test_case(strcmp(string->content, s14) == 0, idx);          // case-1
    test_case(string->length == 23, idx);                       // case-2

    remove_ch_string(string, c5, false);
    test_case(strcmp(string->content, s15) == 0, idx);          // case-3
    test_case(string->length == 22, idx);                       // case-4

    remove_ch_string(string, 'x', false);
    test_case(strcmp(string->content, s15) == 0, idx);          // case-5
    test_case(string->length == 22, idx);                       // case-6
    show_result();


    /* ----- Check for remove_btw_string ----- */
    pass = 0; cases = 8, idx = 0;
    print_header(msgs[13]);
    
    CHAR s16[] = "new trin finally";
    CHAR s17[] = "new tin finally";

    test_case(remove_btw_string(string, 0, 5) == true, idx);    // case-1
    test_case(strcmp(string->content, s16) == 0, idx);          // case-2

    test_case(remove_btw_string(string, -1, 5) == false, idx);  // case-3
    test_case(strcmp(string->content, s16) == 0, idx);          // case-4

    test_case(remove_btw_string(string, 4, 16) == false, idx);  // case-5

    test_case(remove_btw_string(string, 5, 4) == false, idx);   // case-6
    
    test_case(remove_btw_string(string, 5, 5) == true, idx);    // case-7
    test_case(strcmp(string->content, s17) == 0, idx);          // case-8
    show_result();


    /* ----- Check for remove_from_string ----- */
    pass = 0; cases = 7, idx = 0;
    print_header(msgs[13]);
    
    CHAR s18[] = "new tin";

    test_case(remove_from_string(string, 7) == true, idx);      // case-1
    test_case(strcmp(string->content, s18) == 0, idx);          // case-2
    test_case(string->length == 7, idx);                        // case-3

    test_case(remove_from_string(string, -1) == false, idx);    // case-4
    test_case(strcmp(string->content, s18) == 0, idx);          // case-5

    test_case(remove_from_string(string, 7) == false, idx);     // case-6
    test_case(strcmp(string->content, s18) == 0, idx);          // case-7
    show_result();


    // /* ----- Check for remove_in_string ----- */
    // pass = 0; cases = 2;
    // print_header(msgs[12]);
    // CHAR fs3[] = "the new string";
    // free(substr);
    // substr = create_string_wc(" finally");
    // remove_in_string(string, substr, true);
    // test_case(strcmp(string->content, fs1) == 0);
    // free(substr);
    // substr = create_string_wc("set ");
    // remove_in_string(string, substr, false);
    // test_case(strcmp(string->content, fs3) == 0);
    // show_result();

    // /* ----- Check for check_pangram ----- */
    // pass = 0; cases = 3;
    // print_header(msgs[13]);
    // CHAR ps1[] = "The quick brown fox jumps over the lazy dog";
    // CHAR ps2[] = "The quick brown fox jumped over the lazy dog";
    // test_case(check_pangram_lipogram(string, false, false) == 0);
    // free(string);
    // string = create_string_wc(ps1);
    // test_case(check_pangram_lipogram(string, false, false) == 1);
    // free(string);
    // string = create_string_wc(ps2);
    // test_case(check_pangram_lipogram(string, true, false) == 2);
    // show_result();

    return 0;
}
