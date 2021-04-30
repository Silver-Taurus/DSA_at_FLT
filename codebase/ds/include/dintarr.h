// Include files
#include "types.h"

#ifndef __DINTARR__
#define __DINTARR__

/*
    Structure for the dynamic int array
*/
typedef struct dintarr {
    INT *arr;
    INT cap;
    INT length;
} iarr_t;

/* ---------- Creating macros for functionality to be used in program ---------- */
#define iarr_cap_size(int_arr) (sizeof(INT) * int_arr->cap)

/* ---------- Function prototype ---------- */
// Function to create a new dynamic int array
iarr_t *create_iarray ();

// Function to extend a dynamic int array
void extend_iarray (iarr_t *int_arr);

// Function to append in dynamic int array
void append_iarray (iarr_t *int_arr, INT val);

#endif