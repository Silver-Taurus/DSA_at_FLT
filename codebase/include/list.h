// Include files
#include "types.h"

#ifndef __LIST__
#define __LIST__

/*
    Structure for the list
*/
typedef struct list {
    void *data;
    INT cap;
    INT length;
} list_t;

/* ---------- Function prototype ---------- */
// Function to create a new list
list_t* create_list ();

#endif