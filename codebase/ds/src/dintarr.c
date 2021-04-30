#include "dintarr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

iarr_t* create_iarray () {
    iarr_t *new_int_arr = (iarr_t *) malloc(sizeof(iarr_t));
    
    // Initializing the fields
    new_int_arr->cap = LEN;
    new_int_arr->length = 0;
    
    // Creating the arr field amd then initialize it
    new_int_arr->arr = (INT *) malloc(iarr_cap_size(new_int_arr));
    memset(new_int_arr->arr, 0, iarr_cap_size(new_int_arr));

    return new_int_arr;
}

void extend_iarray (iarr_t *int_arr) {
    INT *new_arr;

    // Update the int_arr cap field to the twice the current cap
    int_arr->cap *= 2;

    // Creating a new arr and initialize it
    new_arr = (INT *) malloc(iarr_cap_size(int_arr));
    memset(new_arr, 0, iarr_cap_size(int_arr));

    // Copy the data of arr field of int_arr to new arr
    for (INT index = 0; index < int_arr->length; index++)
        new_arr[index] = int_arr->arr[index];

    // Free the original arr data and set new arr to the field
    free(int_arr->arr);
    int_arr->arr = new_arr;
}

void append_iarray (iarr_t *int_arr, INT val) {
    // Store the new value
    int_arr->arr[int_arr->length++] = val;

    // Check if the dynamic int array is full
    if (int_arr->length == int_arr->cap)
        extend_iarray(int_arr);
}
