#include "dstring.h"
#include "dintarr.h"
#include "unit_test.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
    Main driver code (must include)

        Note: 
        - Maximum test cases for any function is taken as 8.
        - passes, cases and idx to be initialized first.
        - test_case will take the expr to evaluate.
        - show_result will be used to print result to the console.
*/
INT main (void) {
    // Variable to check on
    str_t *string;

    // Header messages
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
        "remove_at_string",
        "remove_in_string",
        "remove_all_in_string",
        "count_uc_string",
        "count_lc_string",
        "count_num_string",
        "count_spc_string",
        "replace_string"
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
    pass = 0; cases = 3; idx = 0;
    print_header(msgs[4]);

    CHAR s2[] = " Created by Silver...\n";
    CHAR s3[] = "Set the string Created by Silver...\n";

    free(string);
    string = create_string_wc(s1);
    append_string(string, s2);
    test_case(strcmp(string->content, s3) == 0, idx);           // case-1
    test_case(string->length == 36, idx);                       // case-2
    test_case(string->cap == 64, idx);                          // case-3
    show_result();


    /* ----- Check for set_string ----- */
    pass = 0, cases = 3, idx = 0;
    print_header(msgs[5]);

    CHAR s4[] = "Testing set string";
    set_string(string, s4);

    test_case(strcmp(string->content, s4) == 0, idx);           // case-1
    test_case(string->cap == 32, idx);                          // case-2
    test_case(string->length == 18, idx);                       // case-3
    show_result();


    /* ----- Check for substr_btw_string ----- */
    pass = 0; cases = 6, idx = 0;
    print_header(msgs[6]);

    CHAR s5[] = "ing set str", s6[] = "t";
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
    test_case(strcmp(substr->content, s5) == 0, idx);           // case-4

    free(substr);
    substr = substr_btw_string(string, 0, 17);
    test_case(strcmp(substr->content, s4) == 0, idx);           // case-5

    free(substr);
    substr = substr_btw_string(string, 3, 3);
    test_case(strcmp(substr->content, s6) == 0, idx);           // case-6
    show_result();


    /* ----- Check for substr_from_string ----- */
    pass = 0; cases = 6, idx = 0;
    print_header(msgs[7]);

    CHAR s7[] = "g";

    free(substr);
    substr = substr_from_string(string, 0); 
    test_case(strcmp(substr->content, s4) == 0, idx);           // case-1
    test_case(substr->length == 18, idx);                       // case-2

    free(substr);
    substr = substr_from_string(string, -1);
    test_case(substr == NULL, idx);                             // case-3

    free(substr);
    substr = substr_from_string(string, 18);
    test_case(substr == NULL, idx);                             // case-4
    
    free(substr);
    substr = substr_from_string(string, 17);
    test_case(strcmp(substr->content, s7) == 0, idx);           // case-5
    test_case(substr->length == 1, idx);                        // case-6
    show_result();


    /* ----- Check for substr_in_string ----- */
    pass = 0; cases = 4, idx = 0;
    print_header(msgs[8]);

    INT pos;    
    CHAR s8[] = "Set the new string finally";

    free(string);
    free(substr);
    string = create_string_wc(s8);
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
    test_case(positions->array[0] == 15, idx);                    // case-3
    test_case(positions->array[1] == 20, idx);                    // case-4
    
    free(substr);
    substr = create_string_wc("set");
    positions = substr_all_in_string(string, substr, false);
    test_case(positions->length == 1, idx);                     // case-5
    test_case(positions->array[0] == 0, idx);                     // case-6

    positions = substr_all_in_string(string, substr, true);
    test_case(positions == NULL, idx);                          // case-7
    
    free(substr);
    substr = create_string_wc("llys");
    positions = substr_all_in_string(string, substr, false);
    test_case(positions == NULL, idx);                          // case-8
    show_result();


    /* ----- Check for insert_at_string ----- */
    pass = 0; cases = 6, idx = 0;
    print_header(msgs[10]);

    CHAR s9[] = "Set the string";
    CHAR s10[] = "new ";
    CHAR s11[] = "Set the new string";
    CHAR s12[] = " finally";

    free(string);
    string = create_string_wc(s9);

    test_case(insert_at_string(string, 8, s10) == true, idx);    // case-1
    test_case(strcmp(string->content, s11) == 0, idx);           // case-2
    test_case(string->length == 18, idx);                       // case-3

    test_case(insert_at_string(string, 18, s12) == true, idx);  // case-4
    test_case(strcmp(string->content, s8) == 0, idx);           // case-5
    test_case(string->length == 26, idx);                       // case-6
    show_result();


    /* ----- Check for replace_ch_string ----- */
    pass = 0; cases = 6, idx = 0;
    print_header(msgs[11]);
    
    CHAR s13[] = "Set the new gtring finally";
    CHAR s14[] = "Get the new gtring finally";
    CHAR s15[] = "Het the new HtrinH finally";
    CHAR c1 = 's', c2 = 'g', c3 = 'G', c4 = 'G', c5 = 'H';
   
    replace_ch_string(string, c1, c2, true);
    test_case(strcmp(string->content, s13) == 0, idx);          // case-1
    test_case(string->length == 26, idx);                       // case-2
    
    replace_ch_string(string, c1, c3, false);
    test_case(strcmp(string->content, s14) == 0, idx);          // case-3
    test_case(string->length == 26, idx);                       // case-4

    replace_ch_string(string, c4, c5, false);
    test_case(strcmp(string->content, s15) == 0, idx);          // case-5
    test_case(string->length == 26, idx);                       // case-6
    show_result();


    /* ----- Check for remove_ch_string ----- */
    pass = 0; cases = 6, idx = 0;
    print_header(msgs[12]);
    
    CHAR s16[] = "et the new trin finally";
    CHAR s17[] = "et te new trin finally";

    remove_ch_string(string, c5, true);
    test_case(strcmp(string->content, s16) == 0, idx);          // case-1
    test_case(string->length == 23, idx);                       // case-2

    remove_ch_string(string, c5, false);
    test_case(strcmp(string->content, s17) == 0, idx);          // case-3
    test_case(string->length == 22, idx);                       // case-4

    remove_ch_string(string, 'x', false);
    test_case(strcmp(string->content, s17) == 0, idx);          // case-5
    test_case(string->length == 22, idx);                       // case-6
    show_result();


    /* ----- Check for remove_btw_string ----- */
    pass = 0; cases = 8, idx = 0;
    print_header(msgs[13]);
    
    CHAR s18[] = "new trin finally";
    CHAR s19[] = "new tin finally";

    test_case(remove_btw_string(string, 0, 5) == true, idx);    // case-1
    test_case(strcmp(string->content, s18) == 0, idx);          // case-2

    test_case(remove_btw_string(string, -1, 5) == false, idx);  // case-3
    test_case(strcmp(string->content, s18) == 0, idx);          // case-4

    test_case(remove_btw_string(string, 4, 16) == false, idx);  // case-5

    test_case(remove_btw_string(string, 5, 4) == false, idx);   // case-6
    
    test_case(remove_btw_string(string, 5, 5) == true, idx);    // case-7
    test_case(strcmp(string->content, s19) == 0, idx);          // case-8
    show_result();


    /* ----- Check for remove_from_string ----- */
    pass = 0; cases = 7, idx = 0;
    print_header(msgs[14]);
    
    CHAR s20[] = "new tin";

    test_case(remove_from_string(string, 7) == true, idx);      // case-1
    test_case(strcmp(string->content, s20) == 0, idx);          // case-2
    test_case(string->length == 7, idx);                        // case-3

    test_case(remove_from_string(string, -1) == false, idx);    // case-4
    test_case(strcmp(string->content, s20) == 0, idx);          // case-5

    test_case(remove_from_string(string, 7) == false, idx);     // case-6
    test_case(strcmp(string->content, s20) == 0, idx);          // case-7
    show_result();


    /* ----- Check for remove_at_string ----- */
    pass = 0; cases = 7, idx = 0;
    print_header(msgs[15]);
    
    CHAR s21[] = "new";

    test_case(remove_from_string(string, 3) == true, idx);      // case-1
    test_case(strcmp(string->content, s21) == 0, idx);          // case-2
    test_case(string->length == 3, idx);                        // case-3

    test_case(remove_from_string(string, -1) == false, idx);    // case-4
    test_case(strcmp(string->content, s21) == 0, idx);          // case-5

    test_case(remove_from_string(string, 6) == false, idx);     // case-6
    test_case(strcmp(string->content, s21) == 0, idx);          // case-7
    show_result();


    /* ----- Check for remove_in_string ----- */
    pass = 0; cases = 6, idx = 0;
    print_header(msgs[16]);

    CHAR s22[] = "Set the new string";
    CHAR s23[] = "the new string";
    
    free(substr);
    free(string);
    string = create_string_wc(s8);
    substr = create_string_wc(" finally");
    remove_in_string(string, substr, true);
    test_case(strcmp(string->content, s22) == 0, idx);          // case-1
    test_case(string->length == 18, idx);                       // case-2

    free(substr);
    substr = create_string_wc("set ");
    remove_in_string(string, substr, true);
    test_case(strcmp(string->content, s22) == 0, idx);          // case-3
    test_case(string->length == 18, idx);                       // case-4   

    remove_in_string(string, substr, false);
    test_case(strcmp(string->content, s23) == 0, idx);          // case-5
    test_case(string->length == 14, idx);                       // case-6    
    show_result();


    /* ----- Check for remove_all_in_string ----- */
    pass = 0; cases = 6, idx = 0;
    print_header(msgs[17]);

    CHAR s24[] = "Set the new string finally to be set ";
    CHAR s25[] = "Set the new strg fally to be set ";
    CHAR s26[] = "the new strg fally to be ";
    
    free(substr);
    free(string);
    string = create_string_wc(s24);
    substr = create_string_wc("in");
    remove_all_in_string(string, substr, true);
    test_case(strcmp(string->content, s25) == 0, idx);          // case-1
    test_case(string->length == 33, idx);                       // case-2

    free(substr);
    substr = create_string_wc("set ");
    remove_all_in_string(string, substr, false);
    test_case(strcmp(string->content, s26) == 0, idx);          // case-3
    test_case(string->length == 25, idx);                       // case-4   

    remove_all_in_string(string, substr, false);
    test_case(strcmp(string->content, s26) == 0, idx);          // case-5
    test_case(string->length == 25, idx);                       // case-6    
    show_result();
    

    /* ----- Check for count_uc_string ----- */
    pass = 0; cases = 1; idx = 0;
    print_header(msgs[18]);

    CHAR s27[] = "#GeeKs01fOr@gEEks07";
    INT count;

    free(string);
    string = create_string_wc(s27);
    count = count_uc_string(string);
    test_case(count == 5, idx);                                 // case-1
    show_result();


    /* ----- Check for count_lc_string ----- */
    pass = 0; cases = 1; idx = 0;
    print_header(msgs[19]);

    count = count_lc_string(string);
    test_case(count == 8, idx);                                 // case-1
    show_result();


    /* ----- Check for count_num_string ----- */
    pass = 0; cases = 1; idx = 0;
    print_header(msgs[20]);

    count = count_num_string(string);
    test_case(count == 4, idx);                                 // case-1
    show_result();


    /* ----- Check for count_spc_string ----- */
    pass = 0; cases = 1; idx = 0;
    print_header(msgs[21]);

    count = count_spc_string(string);
    test_case(count == 2, idx);                                 // case-1
    show_result();


    /* ----- Check for replace_string ----- */
    pass = 0; cases = 4; idx = 0;
    print_header(msgs[22]);

    CHAR s28[] = "geeks", s29[] = "Dragon";
    CHAR s30[] = "#Dragon01fOr@Dragon07";
    CHAR s31[] = "01", s32[] = "06";
    CHAR s33[] = "#Dragon06fOr@Dragon07";
    str_t *new_str;

    free(substr);
    substr = create_string_wc(s28);
    new_str = create_string_wc(s29);

    replace_string(string, substr, new_str, false);
    test_case(strcmp(string->content, s30) == 0, idx);          // case-1
    test_case(string->length == 21, idx);                       // case-2

    free(substr);
    free(new_str);
    substr = create_string_wc(s31);
    new_str = create_string_wc(s32);
    replace_string(string, substr, new_str, true);
    test_case(strcmp(string->content, s33) == 0, idx);          // case-3
    test_case(string->length == 21, idx);                       // case-4
    show_result();

    // /* ----- Check for check_pangram ----- */
    // pass = 0; cases = 3, idx = 0;
    // print_header(msgs[22]);
    // CHAR s27[] = "The quick brown fox jumps over the lazy dog";
    // CHAR s27[] = "The quick brown fox jumped over the lazy dog";
 
    // test_case(check_pangram_lipogram(string, false, false) == 0, idx);  // case-1
    // free(string);
    // string = create_string_wc(s27);
    // test_case(check_pangram_lipogram(string, false, false) == 1, idx);  // case-2

    // free(string);
    // string = create_string_wc(s27);
    // test_case(check_pangram_lipogram(string, true, false) == 2, idx);   // case-3
    // show_result();


    // /* ----- Check for min_window_substr ----- */
    // pass = 0; cases = 3; idx = 0;
    // print_header(msgs[23]);

    // str_t *pattern;
    // CHAR s28[] = "this is a test string";
    // CHAR s29[] = "tist";
    // CHAR s30[] = "t stri";
    // CHAR s31[] = "this is a test strings";
    // CHAR s32[] = "xenon";

    // free(substr);
    // free(string);
    // string = create_string_wc(s28);
    // pattern = create_string_wc(s29);
    // substr = min_window_substr(string, pattern);
    // test_case(strcmp(substr->content, s30) == 0, idx);          // case-1

    // free(substr);
    // free(pattern);
    // pattern = create_string_wc(s31);
    // substr = min_window_substr(string, pattern);
    // test_case(substr == NULL, idx);                             // case-2

    // free(substr);
    // free(pattern);
    // pattern = create_string_wc(s32);
    // substr = min_window_substr(string, pattern);
    // test_case(substr == NULL, idx);                             // case-3
    // show_result();

    return 0;
}
