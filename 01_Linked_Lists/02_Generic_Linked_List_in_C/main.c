#include<stdio.h>
#include<stdlib.h>

// Node structure for the Linked list construction
struct Node{
    void *data;
    struct Node *next;
};

// Linked List operating functions
void push(struct Node**, void*, size_t);
void display(struct Node*, void(*)(void*));

// Utility functions
void printInt(void *i){
    printf(" %d", *(int*)i);
}
void printFloat(void *f){
    printf(" %.1f", *(float*)f);
}

// Driver program
int main(){
    struct Node *start = NULL;

    // Create and print an int linked list
    unsigned int_size = sizeof(int);
    int arr1[] = {10,20,30,40,50,60,70,80,90,100}, i;

    for (i = 9; i >= 0; i--)
        push(&start, &arr1[i], int_size);
    
    printf("Created Integer Linked List.\nList is: ");
    display(start, printInt);
    printf("\n");

    // Create and print a float linked list
    unsigned float_size = sizeof(float);
    start = NULL;
    float arr2[] = {10.1,20.2,30.3,40.4,50.5};

    for (i = 4; i >= 0; i--)
        push(&start, &arr2[i], float_size);
    
    printf("Created Float Linked List.\nList is: ");
    display(start, printFloat);
    printf("\n");

    return 0;
}

void push(struct Node **startPtr, void *new_data, size_t data_size){
  // Allocate the memory for the node
  struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));

  new_node->data = malloc(data_size);
  new_node->next = *startPtr;

  // Copy contents of new_data to newly allocated memory.
   int i;
   for(i = 0; i < data_size; i++)
    *(char*)(new_node->data + i) = *(char*)(new_data + i);  // Assuming the size of char is 1 byte.

   (*startPtr) = new_node; 
}

void display(struct Node *node, void (*fPtr)(void*)){
    while(node){
        (*fPtr)(node->data);
        node = node->next;
    }
}