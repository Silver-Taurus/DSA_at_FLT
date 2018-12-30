#include<stdio.h>
#include<stdlib.h>

struct Node{
    int data;
    struct Node *next;
};

void push(struct Node**, int);
void display(struct Node*);
void rotate(struct Node**, int);

int main(){
    // Allocate start node to an empty list
    struct Node *start = NULL;

    // Create a list: 10 20 30 40 50
    int i;
    for(i = 50; i > 0; i -= 10)
        push(&start,i);
    
    printf("Given Linked List is: ");
    display(start);

    // Rotating the list by 3 for example
    rotate(&start,3);
    printf("\nRotated Linked List is: ");
    display(start);
    printf("\n");

    return 0;
}

void push(struct Node **startPtr, int data){
    // Allocate the node
    struct Node *new_node = (struct Node*)malloc(sizeof(struct Node));

    // Put in the data
    new_node->data = data;

    // Link the old list to the new node
    new_node->next = *startPtr;

    // Move the start pointer
    *startPtr = new_node;
}

void display(struct Node *node){
    while(node){
        printf("%d ",node->data);
        node = node->next;
    }
}

void rotate(struct Node **startPtr, int key){
    // If key is 0, no change occurs
    if(key == 0)
        return;

    // Get the key node
    int count = 1;
    struct Node *cur = *startPtr;
    while(count < key && cur){
        cur = cur->next;
        count++;
    }

    // If current is NULL, key is greater than the size of the list, so no change occurs
    if(!cur)
        return;

    struct Node *keyNode = cur;
    while(cur->next)
        cur = cur->next;
    cur->next = *startPtr;
    *startPtr = keyNode->next;
    keyNode->next = NULL;
}