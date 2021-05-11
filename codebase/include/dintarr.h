// Include files
#include "types.h"
#include <stddef.h>

#ifndef __DINTARR__
#define __DINTARR__

/*
    Structure for the dynamic int array
*/
typedef struct dintarr {
    INT *array;
    INT cap;
    INT length;
} iarr_t;


/* ---------- Creating macros for functionality to be used in program ---------- */
#define iarr_cap_size(iarr) (sizeof(INT) * iarr->cap)
#define set_iarr_cap(iarr, len) while (iarr->cap <= len) iarr->cap *= 2
#define check_subarr_pos(iarr, pos) (pos >= 0 && pos < iarr->length)
#define check_arr_insert_pos(iarr, pos) (pos >= 0 && pos <= iarr->length)


/* ---------- Function prototype ---------- */
// Function to create a new dynamic int array
iarr_t *create_iarray ();

// Function to create a new dynamic int array with given array
iarr_t* create_iarray_wc (INT *array, INT length);

// Function to extend a dynamic int array
void extend_iarray (iarr_t *iarray);

// Function to take input in a dynamic int array
void input_iarray (iarr_t *iarray);

// Function to append a value in dynamic int array
void append_val_iarray (iarr_t *iarray, INT val);

// Function to append an array in dynamic int array
void append_arr_iarray (iarr_t *iarray, INT *array, INT length);

// Function to set array of dynamic int array
void set_iarray (iarr_t *iarray, INT *array, INT length);

// Function to get subarr of a dynamic int array between a start position and end position
iarr_t* subarr_btw_iarray (iarr_t *iarray, INT star_pos, INT end_pos);

// Function to get subarr of a dynamic int array from a position
iarr_t* subarr_from_iarray (iarr_t *iarray, INT star_pos);

// Function to search first occurrence of a value in dynamic int array and return the position
INT search_iarray (iarr_t *iarray, INT val);

// Function to search all occurrences of a value in dynamic int array and return the position
iarr_t* search_all_iarray (iarr_t *iarray, INT val);

// Function to add value at the given position in dynamic int array
bool_t insert_val_at_iarray (iarr_t *iarray, INT pos, INT val);

// Function to add array at the given position in dynamic int array
bool_t insert_arr_at_iarray (iarr_t *iarray, INT pos, INT *array, INT length);

// Function to replace all occurrences of a value in dynamic int array
void replace_val_iarray (iarr_t *iarray, INT val, INT new_val);

// Function to remove values in a dynamic int array based on start position and end position
bool_t remove_btw_iarray (iarr_t *iarray, INT start_pos, INT end_pos);

// Function to remove values in a dynamic int array from a start position
bool_t remove_from_iarray (iarr_t *iarray, INT start_pos);

// Function to remove values in a dynamic int array at a given position
bool_t remove_at_iarray (iarr_t *iarray, INT pos);

// Function to remove first occurrence of a value in a dynamic int array
void remove_in_iarray (iarr_t *iarray, INT val);

// Function to remove all occurrences of a value in a dynamic int array
void remove_all_in_iarray (iarr_t *iarray, INT val);

// Function to give count of a value in dynamic int array
INT count_val_iarray (iarr_t *iarray, INT val);

// Function to display dynamic int array
void display_iarray (iarr_t *iarray);

// Function to check equality of two dynamic int arrays are equal
bool_t check_eq_iarray (iarr_t *iarray1, iarr_t *iarray2);

// Function to chechk equality of dynamic int array and int array
bool_t check_arr_eq_iarray (iarr_t *iarray, INT *array, INT length);


/* ---------- Utility Function Prototypes ---------- */
// Function to create and initialize the array to 0
INT* __create_array (size_t size);

// Function to copy the array of iarray to a new array
void __copy_to_new_array (INT *new_array, iarr_t *iarray);

// Function to copy the array of iarray to a new array upto a length
void __copy_l_to_new_array (INT *new_array, iarr_t *iarray, INT length);

// Function to copy the array of iarray to a new array except a ceratin length portion
// between start_pos and end_pos and also record the length of new array
void __copy_lrem_to_new_array (INT *new_array, iarr_t *iarray, INT *length, INT start_pos, INT end_pos);

// Function to copy the array to a iarray's array
void __copy_array_to_iarray (iarr_t *iarray, INT *array, INT length);

// Function to copy iarray to another iarray
void __copy_iarray_to_iarray (iarr_t *dest_iarray, iarr_t *src_iarray);

// Function to free the old array and save the new array to iarray and update length
void __save_array_iarr (iarr_t *iarray, INT *new_array, INT length);

#endif