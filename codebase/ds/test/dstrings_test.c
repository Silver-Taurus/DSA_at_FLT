#include "dstrings.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

#define print_header(msg) printf("Case - %-25s: ", msg)

#define case_check(expr) if (expr) pass++
#define result() if (pass == cases) p_success(); else p_failure(); count()

#define p_success() printf("%20s", "SUCCESS... ")
#define p_failure() printf("%20s", "FAILURE... ")
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
        "substr_btw_string",
        "substr_from_string",
        "insert_at_string",
        "replace_ch_string",
        "remove_ch_string",
        "substr_in_string",
        "remove_string",
        "check_pangram_lipogram"
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
    free(string);
    string = create_string();
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
    append_string(string, as);
    display_string(string);
    nl();

    /* ----- Check for set_string ----- */
    pass = 0, cases = 3;
    CHAR s[] = "Set the string";
    print_header(msgs[4]);
    set_string(string, s);
    case_check(strcmp(string->content, s) == 0);
    case_check(string->cap == 16);
    case_check(string->length == 14);
    result();

    /* ----- Check for create_string_wd ----- */
    pass = 0; cases = 3;
    print_header(msgs[5]);
    free(string);
    string = create_string_wc(s);
    case_check(strcmp(string->content, s) == 0);
    case_check(string->cap == 16);
    case_check(string->length == 14);
    result();

    /* ----- Check for substr_btw_string ----- */
    pass = 0; cases = 6;
    CHAR c_str1[] = "t the s", c_str2[] = "t";
    print_header(msgs[6]);
    str_t *substr = substr_btw_string(string, -1, 8);
    case_check(substr == NULL);
    free(substr);
    substr = substr_btw_string(string, 0, 15);
    case_check(substr == NULL);
    free(substr);
    substr = substr_btw_string(string, 4, 3);
    case_check(substr == NULL);
    free(substr);
    substr = substr_btw_string(string, 2, 8);
    case_check(strcmp(substr->content, c_str1) == 0);
    free(substr);
    substr = substr_btw_string(string, 0, 13);
    case_check(strcmp(substr->content, s) == 0);
    free(substr);
    substr = substr_btw_string(string, 2, 2);
    case_check(strcmp(substr->content, c_str2) == 0);
    result();

    /* ----- Check for substr_from_string ----- */
    pass = 0; cases = 2;
    print_header(msgs[7]);
    free(substr);
    substr = substr_from_string(string, 0);
    case_check(strcmp(substr->content, s) == 0);
    free(substr);
    substr = substr_from_string(string, -1);
    case_check(substr == NULL);
    result();

    /* ----- Check for insert_at_string ----- */
    pass = 0; cases = 4;
    CHAR ns1[] = "new ";
    CHAR ns2[] = " finally";
    CHAR fs1[] = "Set the new string";
    CHAR fs2[] = "Set the new string finally";
    print_header(msgs[8]);
    case_check(insert_at_string(string, 8, ns1) == true);
    case_check(strcmp(string->content, fs1) == 0);
    case_check(insert_at_string(string, 18, ns2) == true);
    case_check(strcmp(string->content, fs2) == 0);
    result();

    /* ----- Check for replace_ch_string ----- */
    pass = 0; cases = 3;
    print_header(msgs[9]);
    CHAR ch1 = 's', ch2 = 'G', new_ch1 = 'g', new_ch2 = 'G', new_ch3 = 'H';
    CHAR rs1[] = "Set the new gtring finally";
    CHAR rs2[] = "Get the new gtring finally";
    CHAR rs3[] = "Het the new HtrinH finally";
    replace_ch_string(string, ch1, new_ch1, true);
    case_check(strcmp(string->content, rs1) == 0);
    replace_ch_string(string, ch1, new_ch2, false);
    case_check(strcmp(string->content, rs2) == 0);
    replace_ch_string(string, ch2, new_ch3, false);
    case_check(strcmp(string->content, rs3) == 0);
    result();

    /* ----- Check for remove_ch_string ----- */
    pass = 0; cases = 3;
    print_header(msgs[10]);
    CHAR re1[] = "et the new trin finally";
    CHAR re2[] = "et te new trin finally";
    remove_ch_string(string, new_ch3, true);
    case_check(strcmp(string->content, re1) == 0);
    remove_ch_string(string, new_ch3, false);
    case_check(strcmp(string->content, re2) == 0);
    remove_ch_string(string, 'x', false);
    case_check(strcmp(string->content, re2) == 0);
    result();

    /* ----- Check for substr_in_string ----- */
    pass = 0; cases = 4;
    print_header(msgs[11]);
    free(substr);
    substr = create_string_wc("new");
    INT pos = substr_in_string(string, substr, true);
    case_check(pos == 6);
    free(string);
    free(substr);
    string = create_string_wc(fs2);
    substr = create_string_wc("set");
    pos = substr_in_string(string, substr, false);
    case_check(pos == 0);
    pos = substr_in_string(string, substr, true);
    case_check(pos == -1);
    free(substr);
    substr = create_string_wc("llys");
    pos = substr_in_string(string, substr, false);
    case_check(pos == -1);
    result();

    /* ----- Check for remove_string ----- */
    pass = 0; cases = 2;
    print_header(msgs[12]);
    CHAR fs3[] = "the new string";
    free(substr);
    substr = create_string_wc(" finally");
    remove_string(string, substr, true);
    case_check(strcmp(string->content, fs1) == 0);
    free(substr);
    substr = create_string_wc("set ");
    remove_string(string, substr, false);
    case_check(strcmp(string->content, fs3) == 0);
    result();

    /* ----- Check for check_pangram ----- */
    pass = 0; cases = 3;
    print_header(msgs[13]);
    CHAR ps1[] = "The quick brown fox jumps over the lazy dog";
    CHAR ps2[] = "The quick brown fox jumped over the lazy dog";
    case_check(check_pangram_lipogram(string, false, false) == 0);
    free(string);
    string = create_string_wc(ps1);
    case_check(check_pangram_lipogram(string, false, false) == 1);
    free(string);
    string = create_string_wc(ps2);
    case_check(check_pangram_lipogram(string, true, false) == 2);
    result();

    return 0;
}
