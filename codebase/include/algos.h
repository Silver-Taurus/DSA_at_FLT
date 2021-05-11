// Include files
#include "types.h"
#include "dstring.h"
#include "dintarr.h"

#ifndef __ALGOS__
#define __ALGOS__

/* ---------- String Algorithms ---------- */
// Function to check whether a string is a "Pangram" or "holoalphabetic" as well as a
// "pangrammatic liporgram" and print the missing alphabets if asked
INT check_pangram_lipogram (str_t *string, bool_t check_lipogram, bool_t print_missing);

// Function to find the min. window substr in a dynamic string that contains all the
// characters of a given patter
str_t* min_window_substr (str_t *string, str_t *pattern);


#endif