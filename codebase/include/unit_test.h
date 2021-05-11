// Include files
#include "types.h"
#include "string.h"

#ifndef __UNIT_TEST__
#define __UNIT_TEST__

/* ---------- Macros to define the constants to be used ---------- */
#define TCASES 8
#define COLOR_NRM "\x1B[0m"
#define COLOR_ERR "\x1B[31m"
#define COLOR_OK "\x1B[32m"

/* ---------- Global Variables for running test cases---------- */
INT cases, pass, idx;
CHAR failed_cases[8];

/* ---------- Macros to define functionalities to be used ---------- */
#define print_header(msg) fprintf(stdout, "Case - %-25s: ", msg)
#define fc_init() bzero(failed_cases, TCASES)
#define test_case(expr, idx) if (expr) pass++; else failed_cases[idx] = 1; idx++

#define p_success() fprintf(stdout, "%s%25s%s", COLOR_OK, "SUCCESS... ", COLOR_NRM)
#define p_failure() fprintf(stdout, "%s%25s%s", COLOR_ERR, "FAILURE... ", COLOR_NRM)
#define count() fprintf(stdout, "%d / %d cases passed.", pass, cases)

/* ---------- Utility Functions for testing ---------- */
void show_fail_status ();
void show_result ();

#endif