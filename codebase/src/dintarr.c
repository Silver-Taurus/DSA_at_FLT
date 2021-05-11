#include "dintarr.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

iarr_t* create_iarray () {
    iarr_t *new_iarray = (iarr_t *) malloc(sizeof(iarr_t));
    
    // Initializing the fields
    new_iarray->cap = LEN;
    new_iarray->length = 0;
    new_iarray->array = __create_array(iarr_cap_size(new_iarray));

    return new_iarray;
}

iarr_t* create_iarray_wc (INT *array, INT length) {
    iarr_t *new_iarray = (iarr_t *) malloc(sizeof(iarr_t));
    
    // Initialize the cap with 0 and perform set_iarray
    new_iarray->cap = 0;
    set_iarray(new_iarray, array, length);

    return new_iarray;
}

void extend_iarray (iarr_t *iarray) {
    INT *new_array;

    // Update the cap, create and fill new_array and save in iarray
    iarray->cap *= 2;
    new_array = __create_array(iarr_cap_size(iarray));
    __copy_to_new_array(new_array, iarray);
    __save_array_iarr(iarray, new_array, -1);
}

void input_iarray (iarr_t *iarray) {
    INT input;
    CHAR ch;

    // Take input from the console till the newline
    while (scanf(INT_FS CHAR_FS, &input, &ch)) {
        append_val_iarray(iarray, input);
       
        if (ch == '\n')
            break;
    }
}

void append_val_iarray (iarr_t *iarray, INT val) {
    // Store the new value
    iarray->array[iarray->length++] = val;

    // Check if the dynamic int array is full
    if (iarray->length == iarray->cap)
        extend_iarray(iarray);
}

void append_arr_iarray (iarr_t *iarray, INT *array, INT length) {
    INT index;

    // Store all the value of array to iarray
    for (index = 0; index < length; index++)
        append_val_iarray(iarray, array[index]);
}

void set_iarray (iarr_t *iarray, INT *array, INT length) {
    // Check if the cap is less than equal to given array's length
    if (iarray->cap <= length) {
        // If cap is not 0 and hence an array exists, free it
        if (iarray->cap)
            free(iarray->array);

        // Set req. cap and Create a new array
        iarray->cap = LEN;
        set_iarr_cap(iarray, length);
        iarray->array = __create_array(iarr_cap_size(iarray));
    }

    // If cap is sufficient, reset the array to 0 to take new entry
    else
        memset(iarray->array, 0, iarr_cap_size(iarray));

    // Reset iarray length
    iarray->length = 0;

    // Set the given array to iarray's array
    __copy_array_to_iarray(iarray, array, length);
}

iarr_t *subarr_btw_iarray (iarr_t *iarray, INT start_pos, INT end_pos) {
    INT index, length = 0;
    iarr_t *subarr;

    // Check for the valid start position, if not return NULL
    if (!check_subarr_pos(iarray, start_pos))
        return NULL;

    // Check for the valid end position, if not return NULL
    if (!check_subarr_pos(iarray, end_pos))
        return NULL;

    // Check for start and end position
    if (start_pos > end_pos)
        return NULL;

    // If positions are valid find the length of subarr
    length = end_pos - start_pos + 1;

    // Create empty subarr and initialize fields
    subarr = (iarr_t *) malloc(sizeof(iarr_t));
    subarr->length = 0;
    subarr->cap = LEN;

    // Set the req. cap size and create array
    set_iarr_cap(subarr, length);
    subarr->array = __create_array(iarr_cap_size(subarr));

    // Fill the subarr array
    for (index = 0; index < length; index++)
        subarr->array[subarr->length++] = iarray->array[start_pos + index];

    return subarr;
}

iarr_t* subarr_from_iarray (iarr_t *iarray, INT start_pos) {
    // Get the subarr_from using the subarr_btw
    return subarr_btw_iarray(iarray, start_pos, iarray->length - 1);
}

INT search_iarray (iarr_t *iarray, INT val) {
    INT index, pos = -1;

    // Find the first occurrence of value in array
    for (index = 0; index < iarray->length; index++) {
        if (iarray->array[index] == val) {
            pos = index;
            break;
        }
    }

    return pos;
}

iarr_t* search_all_iarray (iarr_t *iarray, INT val) {
    INT index;
    iarr_t *positions = create_iarray();

    // Find all the occurrences of value in array
    for (index = 0; index < iarray->length; index++)
        if (iarray->array[index] == val)
            append_val_iarray(positions, index);

    // Check in case, no occurrence is present
    if (positions->length == 0)
        return NULL;
    
    return positions;
}

bool_t insert_val_at_iarray (iarr_t *iarray, INT pos, INT val) {
    iarr_t *subarr;
    INT *new_array;
    
    // Check for the valid position, if not return false
    if (!check_arr_insert_pos(iarray, pos))
        return false;

    // If position is last - use append_val_iarray
    if (pos == iarray->length)
        append_val_iarray(iarray, val);

    // Proceed with the insertion of value
    else {
        // Get the subarr
        subarr = subarr_from_iarray(iarray, pos);

        // Set the req. cap size and create new array
        set_iarr_cap(iarray, iarray->length + 1);
        new_array = __create_array(iarr_cap_size(iarray));

        // Form the new array before pos and save it in iarray
        __copy_l_to_new_array(new_array, iarray, pos);
        __save_array_iarr(iarray, new_array, pos);

        // Append the val and remaining array data
        append_val_iarray(iarray, val);
        __copy_iarray_to_iarray(iarray, subarr);

        // Free the subarr
        free(subarr);
    }

    return true;
}

bool_t insert_arr_at_iarray (iarr_t *iarray, INT pos, INT *array, INT length) {
    iarr_t *subarr;
    INT *new_array;
    
    // Check for the valid position, if not return false
    if (!check_arr_insert_pos(iarray, pos))
        return false;

    // If position is last - use append_arr_iarray
    if (pos == iarray->length)
        append_arr_iarray(iarray, array, length);

    // Proceed with the insertion of value
    else {
        // Get the subarr
        subarr = subarr_from_iarray(iarray, pos);

        // Set the req. cap size and create new array
        set_iarr_cap(iarray, iarray->length + 1);
        new_array = __create_array(iarr_cap_size(iarray));

        // Form the new array before pos and save it in iarray
        __copy_l_to_new_array(new_array, iarray, pos);
        __save_array_iarr(iarray, new_array, pos);

        // Append the val and remaining array data
        append_arr_iarray(iarray, array, length);
        __copy_iarray_to_iarray(iarray, subarr);

        // Free the subarr
        free(subarr);
    }

    return true;
}

void replace_val_iarray (iarr_t *iarray, INT val, INT new_val) {
    INT index;

    // Replace all the occurrences of a val with new_val in dynamic int array
    for (index = 0; index < iarray->length; index++)
        if (iarray->array[index] == val)
            iarray->array[index] = new_val;
}

bool_t remove_btw_iarray (iarr_t *iarray, INT start_pos, INT end_pos) {
    INT length = 0;
    INT *new_array;

    // Check for the valid start position, if not return false
    if (!check_subarr_pos(iarray, start_pos))
        return false;

    // Check for the valid end position, if not return false
    if (!check_subarr_pos(iarray, end_pos))
        return false;

    // Check for start and end position
    if (start_pos > end_pos)
        return false;

    // Create new array, copy the req. array and keep track of length
    new_array = __create_array(iarr_cap_size(iarray));
    __copy_lrem_to_new_array(new_array, iarray, &length, start_pos, end_pos);

    // Save the new array with new length
    __save_array_iarr(iarray, new_array, length);

    return true;
}

bool_t remove_from_iarray (iarr_t *iarray, INT start_pos) {
    // Perform remove_from using the remove_btw
    return remove_btw_iarray(iarray, start_pos, iarray->length - 1);
}

bool_t remove_at_iarray (iarr_t *iarray, INT pos) {
    // Perform remove_at using the remove_btw
    return remove_btw_iarray(iarray, pos, pos);
}

void remove_in_iarray (iarr_t *iarray, INT val) {
    INT pos, length = 0;
    INT *new_array;

    // Create new array based on iarray's array
    pos = search_iarray(iarray, val);

    // Check for the case - if val is not present in array
    if (pos == -1)
        return;

    // Create new array based on iarray's array
    new_array = __create_array(iarr_cap_size(iarray));

    // If the position is found fill new array and keep tarck of length
    __copy_lrem_to_new_array(new_array, iarray, &length, pos, pos);

    // Save the array to iarray with new length
    __save_array_iarr(iarray, new_array, length);
}

void remove_all_in_iarray (iarr_t *iarray, INT val) {
    INT index1, index2, length = 0;
    INT *new_array;
    iarr_t *positions;

    // Create new array based on iarray's array
    positions = search_all_iarray(iarray, val);

    // Check for the case - if val is not present in array
    if (positions == NULL)
        return;

    // Create new array based on iarray's array
    new_array = __create_array(iarr_cap_size(iarray));

    // If the position is found fill new array and keep tarck of length
    for (index1 = 0, index2 = 0; index1 < iarray->length; index1++) {
        if (index1 != positions->array[index2])
            new_array[length++] = iarray->array[index1];

        else
            index2++;
    }
    
    // Save the array to iarray with new length
    __save_array_iarr(iarray, new_array, length);
}

INT count_val_iarray (iarr_t *iarray, INT val) {
    INT count = 0, index;

    // Find the occurrences of value in array
    for (index = 0; index < iarray->length; index++)
        if (iarray->array[index] == val)
            count++;
    
    return count;
}

void display_iarray (iarr_t *iarray) {
    INT index;

    // Traverse the array of dynamic int array
    for (index = 0; index < iarray->length; index++)
        intout(iarray->array[index]);
}

bool_t check_eq_iarray (iarr_t *iarray1, iarr_t *iarray2) {
    INT index1, index2;

    // Check for the equality of two dynamic int arrays
    for (index1 = 0, index2 = 0; index1 < iarray1->length && index2 < iarray2->length; index1++, index2++)
        if (iarray1->array[index1] != iarray2->array[index2])
            return false;

    return true;
}

bool_t check_arr_eq_iarray (iarr_t *iarray, INT *array, INT length) {
    INT index1, index2;

    // Check for the equality of a dynamic int array and an int array
    for (index1 = 0, index2 = 0; index1 < iarray->length && index2 < length; index1++, index2++)
        if (iarray->array[index1] != array[index2])
            return false;

    return true;
}


/* ---------- Utility Functions ---------- */
INT* __create_array (size_t size) {
    INT *new_array = (INT *) malloc(size);
    memset(new_array, 0, size);

    return new_array;
}

void __copy_to_new_array (INT *new_array, iarr_t *iarray) {
    INT index;

    for (index = 0; index < iarray->length; index++)
        new_array[index] = iarray->array[index];
}

void __copy_l_to_new_array (INT *new_array, iarr_t *iarray, INT length) {
    INT index;

    for (index = 0; index < length; index++)
        new_array[index] = iarray->array[index];
}

void __copy_lrem_to_new_array (INT *new_array, iarr_t *iarray, INT *length, INT start_pos, INT end_pos) {
    INT index;

    for (index = 0; index < iarray->length; index++)
        if (!(index >= start_pos && index <= end_pos))
            new_array[(*length)++] = iarray->array[index];
}

void __copy_array_to_iarray (iarr_t *iarray, INT *array, INT length) {
    INT index;

    for (index = 0; index < length; index++)
        iarray->array[iarray->length++] = array[index];
}

void __copy_iarray_to_iarray (iarr_t *dest_iarray, iarr_t *src_iarray) {
    INT index;

    for (index = 0; index < src_iarray->length; index++)
        dest_iarray->array[dest_iarray->length++] = src_iarray->array[index];
}

void __save_array_iarr (iarr_t *iarray, INT *new_array, INT length) {
    free(iarray->array);
    iarray->array = new_array;

    if (length != -1)
        iarray->length = length;
}
