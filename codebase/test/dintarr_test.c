#include "dintarr.h"
#include "unit_test.h"
#include <stdio.h>
#include <stdlib.h>

/* ---------- Macros ---------- */
#define arr_size(arr) sizeof(arr) / sizeof(INT)

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
    iarr_t *iarray;

    // Header messages
    CHAR *msgs[] = {
        "create_iarray",
        "create_iarray_wc",
        "extend_iarray",
        "input_iarray",
        "append_val_iarray",
        "append_arr_iarray",
        "set_iarray",
        "subarr_btw_iarray",
        "subarr_from_iarray",
        "search_iarray",
        "search_all_iarray",
        "insert_val_at_iarray",
        "insert_arr_at_iarray",
        "replace_val_iarray",
        "remove_btw_iarray",
        "remove_from_iarray",
        "remove_at_iarray",
        "remove_in_array",
        "remove_all_in_array",
        "count_val_iarray"
    };


    /* ----- Check for create_iarray ----- */
    pass = 0, cases = 2, idx = 0;
    fc_init();
    print_header(msgs[0]);

    iarray = create_iarray();
    
    test_case(iarray->cap == LEN, idx);                             // case-1
    test_case(iarray->length == 0, idx);                            // case-2
    show_result();


    /* ----- Check for create_iarray_wd ----- */
    pass = 0; cases = 3, idx = 0;
    print_header(msgs[1]);
    
    INT i1[] = {1, 2, 3, 4, 5};
    INT s1 = arr_size(i1);

    free(iarray);
    iarray = create_iarray_wc(i1, s1);
    test_case(iarray->cap == LEN, idx);                             // case-1
    test_case(iarray->length == 5, idx);                            // case-2
    test_case(check_arr_eq_iarray(iarray, i1, s1), idx);            // case-3
    show_result();


    /* ----- Check for extend_iarray ----- */
    pass = 0, cases = 2, idx = 0;
    print_header(msgs[2]);

    INT cap = iarray->cap, len = iarray->length;
    extend_iarray(iarray);
    
    test_case(iarray->cap == cap * 2, idx);                         // case-1
    test_case(iarray->length == len, idx);                          // case-2
    show_result();


    /* ----- Check for input_iarray ----- */
    print_header(msgs[3]);

    free(iarray);
    iarray = create_iarray();
    nl();

    strout("Enter a iarray: ");
    input_iarray(iarray);   

    strout("Your input: "); 
    display_iarray(iarray);
    nl(); nl();


    /* ----- Check for append_val_iarray ----- */
    pass = 0; cases = 8; idx = 0;
    print_header(msgs[4]);

    INT n1 = 6;
    INT i2[] = {1, 2, 3, 4, 5 ,6};
    INT i3[] = {1, 2, 3, 4, 5 ,6, 6};
    INT i4[] = {1, 2, 3, 4, 5 ,6, 6, 6};
    INT s2 = arr_size(i2);
    INT s3 = arr_size(i3);
    INT s4 = arr_size(i4);

    free(iarray);
    iarray = create_iarray_wc(i1, s1);
    append_val_iarray(iarray, n1);
    test_case(check_arr_eq_iarray(iarray, i2, s2), idx);            // case-1
    test_case(iarray->length == s2, idx);                           // case-2
    test_case(iarray->cap == LEN, idx);                             // case-3
    
    append_val_iarray(iarray, n1);
    test_case(check_arr_eq_iarray(iarray, i3, s3), idx);            // case-4
    test_case(iarray->length == s3, idx);                           // case-5
   
    append_val_iarray(iarray, n1);
    test_case(check_arr_eq_iarray(iarray, i4, s4), idx);            // case-6
    test_case(iarray->length == s4, idx);                           // case-7
    test_case(iarray->cap == 16, idx);                              // case-8
    show_result();


    /* ----- Check for append_val_iarray ----- */
    pass = 0; cases = 3; idx = 0;
    print_header(msgs[5]);

    INT i5[] = {1, 2, 3, 4, 5, 1, 2, 3, 4, 5};
    INT s5 = arr_size(i5);

    free(iarray);
    iarray = create_iarray_wc(i1, s1);
    append_arr_iarray(iarray, i1, s1);
    test_case(check_arr_eq_iarray(iarray, i5, s5), idx);            // case-1
    test_case(iarray->length == s5, idx);                           // case-2
    test_case(iarray->cap == 16, idx);                             // case-3
    show_result();


    /* ----- Check for set_iarray ----- */
    pass = 0, cases = 3, idx = 0;
    print_header(msgs[6]);

    INT i6[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10 ,11, 12, 13, 14, 15, 16};
    INT s6 = arr_size(i6);

    set_iarray(iarray, i6, s6);

    test_case(check_arr_eq_iarray(iarray, i6, s6), idx);            // case-1
    test_case(iarray->cap == 32, idx);                              // case-2
    test_case(iarray->length == 16, idx);                           // case-3
    show_result();


    /* ----- Check for subarr_btw_iarray ----- */
    pass = 0, cases = 8, idx = 0;
    print_header(msgs[7]);

    INT i7[] = {6, 7, 8, 9, 10};
    INT s7 = arr_size(i7);
    INT n2 = 6;
    iarr_t *subarr;

    subarr = subarr_btw_iarray(iarray, 5, 9);

    test_case(check_arr_eq_iarray(subarr, i7, s7), idx);            // case-1
    test_case(subarr->cap == LEN, idx);                             // case-2
    test_case(subarr->length == 5, idx);                            // case-3
    
    free(subarr);
    subarr = subarr_btw_iarray(iarray, -1, 9);
    test_case(subarr == NULL, idx);                                 // case-4
    
    subarr = subarr_btw_iarray(iarray, 5, s6);
    test_case(subarr == NULL, idx);                                 // case-5

    subarr = subarr_btw_iarray(iarray, 6, 4);
    test_case(subarr == NULL, idx);                                 // case-6

    subarr = subarr_btw_iarray(iarray, 5, 5);
    test_case(subarr->length == 1, idx);                            // case-7
    test_case(subarr->array[0] == n2, idx);                         // case-8
    show_result();


    /* ----- Check for subarr_from_iarray ----- */
    pass = 0, cases = 8, idx = 0;
    print_header(msgs[8]);

    INT i8[] = {12, 13, 14, 15, 16};
    INT s8 = arr_size(i8);
    INT n3 = 16;

    free(subarr);
    subarr = subarr_from_iarray(iarray, 11);
    test_case(check_arr_eq_iarray(subarr, i8, s8), idx);            // case-1
    test_case(subarr->cap == LEN, idx);                             // case-2
    test_case(subarr->length == 5, idx);                            // case-3

    free(subarr);
    subarr = subarr_from_iarray(iarray, 15);
    test_case(subarr->length == 1, idx);                            // case-4
    test_case(subarr->array[0] == n3, idx);                         // case-5

    free(subarr);
    subarr = subarr_from_iarray(iarray, s6);
    test_case(subarr == NULL, idx);                                 // case-6
    
    subarr = subarr_from_iarray(iarray, -1);
    test_case(subarr == NULL, idx);                                 // case-7
    
    subarr = subarr_from_iarray(iarray, 0);
    test_case(check_eq_iarray(subarr, iarray), idx);                // case-8
    show_result();


    /* ----- Check for search_iarray ----- */
    pass = 0, cases = 4, idx = 0;
    print_header(msgs[9]);

    INT i9[] = {1, 2, 4, 6, 6, 2, 3, 4};
    INT s9 = arr_size(i9);
    INT n4 = 6, n5 = 3;
    INT n6 = 0, n7 = -1;
    INT n8 = 4, n9 = 2;

    free(iarray);
    iarray = create_iarray_wc(i9, s9);
    test_case(search_iarray(iarray, n4) == n5, idx);             // case-1
    test_case(search_iarray(iarray, n6) == n7, idx);             // case-2
    test_case(search_iarray(iarray, n8) == n9, idx);             // case-3
    test_case(iarray->cap == 16, idx);                              // case-4
    show_result();


    /* ----- Check for search_all_iarray ----- */
    pass = 0, cases = 5, idx = 0;
    print_header(msgs[10]);

    INT i10[] = {3, 4};
    INT i11[] = {2, 7};
    INT s10 = arr_size(i10);
    INT s11 = arr_size(i11);

    free(subarr);
    subarr = search_all_iarray(iarray, n4);
    test_case(check_arr_eq_iarray(subarr, i10, s10), idx);            // case-1
    test_case(subarr->length == 2, idx);                            // case-2

    free(subarr);
    subarr = search_all_iarray(iarray, n6);
    test_case(subarr == NULL, idx);                                 // case-3

    subarr = search_all_iarray(iarray, n8);
    test_case(check_arr_eq_iarray(subarr, i11, s11), idx);          // case-4
    test_case(subarr->length == 2, idx);                            // case-5
    show_result();


    /* ----- Check for insert_val_at_iarray ----- */
    pass = 0, cases = 6, idx = 0;
    print_header(msgs[11]);

    INT n10 = 6, n11 = 8;
    INT n12 = 16, n13 = 6;
    INT i12[] = {1, 2, 4, 6, 6, 2, 3, 4, 6};
    INT i13[] = {1, 2, 4, 6, 6, 2, 16, 3, 4, 6};
    INT s12 = arr_size(i12);
    INT s13 = arr_size(i13);
                                                                
    test_case(insert_val_at_iarray(iarray, 9, 100) == false, idx);  // case-1

    test_case(insert_val_at_iarray(iarray, -1, 100) == false, idx); // case-2

    test_case(insert_val_at_iarray(iarray, n11, n10), idx);         // case-3
    test_case(check_arr_eq_iarray(iarray, i12, s12), idx);          // case-4
    
    test_case(insert_val_at_iarray(iarray, n13, n12), idx);         // case-5
    test_case(check_arr_eq_iarray(iarray, i13, s13), idx);          // case-6
    show_result();


    /* ----- Check for insert_arr_at_iarray ----- */
    pass = 0, cases = 6, idx = 0;
    print_header(msgs[12]);

    INT i14[] = {69, 14};
    INT i15[] = {1, 2, 4, 6, 6, 2, 16, 3, 4, 6, 69, 14};
    INT i16[] = {1, 2, 4, 6, 6, 2, 69, 14, 16, 3, 4, 6, 69, 14};
    INT s14 = arr_size(i14);
    INT s15 = arr_size(i15);
    INT s16 = arr_size(i16);
                                                                
    test_case(insert_arr_at_iarray(iarray, s13 + 1, i14, s14) == false, idx);  
                                                                    // case-1
    test_case(insert_arr_at_iarray(iarray, -1, i14, s14) == false, idx); 
                                                                    // case-2
    test_case(insert_arr_at_iarray(iarray, s13, i14, s14), idx);    // case-3
    test_case(check_arr_eq_iarray(iarray, i15, s15), idx);          // case-4
    
    test_case(insert_arr_at_iarray(iarray, 6, i14, s14), idx);      // case-5
    test_case(check_arr_eq_iarray(iarray, i16, s16), idx);          // case-6
    show_result();


    /* ----- Check for replace_val_iarray ----- */
    pass = 0, cases = 2, idx = 0;
    print_header(msgs[13]);

    INT n14 = 69, n15 = 6;
    INT i17[] = {1, 2, 4, 6, 6, 2, 6, 14, 16, 3, 4, 6, 6, 14};
    INT s17 = arr_size(i17);

    replace_val_iarray(iarray, n14, n15);
    test_case(check_arr_eq_iarray(iarray, i17, s17), idx);          // case-1
    test_case(iarray->length == s17, idx);                          // case-2
    show_result();


    /* ----- Check for remove_btw_iarray ----- */
    pass = 0, cases = 4, idx = 0;
    print_header(msgs[14]);

    INT n16 = s17, n17 = -1, n18 = 7, n19 = 10;
    INT i18[] = {1, 2, 4, 6, 6, 2, 6, 6, 6, 14};
    INT s18 = arr_size(i18);

    test_case(remove_btw_iarray(iarray, 0, n16) == false, idx);     // case-1
    test_case(remove_btw_iarray(iarray, n17, 10) == false, idx);    // case-2
    test_case(remove_btw_iarray(iarray ,n18, n19), idx);            // case-3
    test_case(check_arr_eq_iarray(iarray, i18, s18), idx);          // case-4
    show_result();


    /* ----- Check for remove_from_iarray ----- */
    pass = 0, cases = 4, idx = 0;
    print_header(msgs[15]);

    INT n20 = s18, n21 = s18 - 1; 
    INT i19[] = {1, 2, 4, 6, 6, 2, 6, 6, 6};
    INT s19 = arr_size(i19);

    test_case(remove_from_iarray(iarray, n20) == false, idx);       // case-1
    test_case(remove_from_iarray(iarray, n17) == false, idx);       // case-2
    test_case(remove_from_iarray(iarray, n21), idx);                // case-3
    test_case(check_arr_eq_iarray(iarray, i19, s19), idx);          // case-4
    show_result();


    /* ----- Check for remove_at_iarray ----- */
    pass = 0, cases = 4, idx = 0;
    print_header(msgs[16]);

    INT n22 = s19, n23 = 5; 
    INT i20[] = {1, 2, 4, 6, 6, 6, 6, 6};
    INT s20 = arr_size(i20);

    test_case(remove_at_iarray(iarray, n22) == false, idx);         // case-1
    test_case(remove_at_iarray(iarray, n17) == false, idx);         // case-2
    test_case(remove_at_iarray(iarray, n23), idx);                // case-3
    test_case(check_arr_eq_iarray(iarray, i20, s20), idx);          // case-4

    show_result();


    /* ----- Check for remove_in_iarray ----- */
    pass = 0, cases = 4, idx = 0;
    print_header(msgs[17]);

    INT n24 = 0, n25 = 6; 
    INT i21[] = {1, 2, 4, 6, 6, 6, 6};
    INT s21 = arr_size(i21);

    remove_in_iarray(iarray, n24);
    test_case(check_arr_eq_iarray(iarray, i20, s20), idx);          // case-1
    test_case(iarray->length == s20, idx);                          // case-2

    remove_in_iarray(iarray, n25);
    test_case(check_arr_eq_iarray(iarray, i21, s21), idx);          // case-3
    test_case(iarray->length == s21, idx);                          // case-4
    show_result();


    /* ----- Check for remove_all_in_iarray ----- */
    pass = 0, cases = 4, idx = 0;
    print_header(msgs[18]);

    INT i22[] = {1, 2, 4};
    INT s22 = arr_size(i22);

    remove_all_in_iarray(iarray, n24);
    test_case(check_arr_eq_iarray(iarray, i20, s20), idx);          // case-1
    test_case(iarray->length == s21, idx);                          // case-2
    remove_all_in_iarray(iarray, n25);
    test_case(check_arr_eq_iarray(iarray, i22, s22), idx);          // case-3
    test_case(iarray->length == s22, idx);                          // case-4
    show_result();


    /* ----- Check for count_val_iarray ----- */
    pass = 0, cases = 3, idx = 0;
    print_header(msgs[19]);

    INT i23[] = {6, 6, 6};
    INT s23 = arr_size(i23);
    INT n26 = 3, n27 = 1;

    append_arr_iarray(iarray, i23, s23);

    test_case(count_val_iarray(iarray, n25) == n26, idx);           // case-1
    test_case(count_val_iarray(iarray, n24) == n24, idx);           // case-2
    test_case(count_val_iarray(iarray, n27) == n27, idx);           // case-3
    show_result();
}
