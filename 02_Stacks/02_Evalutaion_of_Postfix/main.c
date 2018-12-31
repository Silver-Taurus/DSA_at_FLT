#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

typedef enum{false, true} bool;

struct Stack{
    int top;
    unsigned capacity;
    int *arr;
};

// Utility function
bool isEmpty(struct Stack *stack){
    return stack->top == -1;
}

struct Stack* createStack(unsigned cap){
    struct Stack *stack = (struct Stack*)malloc(sizeof(struct Stack));
    if(!stack)
        return NULL;

    stack->top = -1;
    stack->capacity = cap;
    stack->arr = (int*)malloc(stack->capacity * sizeof(int));

    if(!stack->arr)
        return NULL;

    return stack;
}

// Stack Operations
int peek(struct Stack *stack){
    return stack->arr[stack->top];
}

char pop(struct Stack *stack){
    if(!isEmpty(stack))
        return stack->arr[stack->top--];
    return '$';
}

void push(struct Stack *stack, int op){
    stack->arr[++stack->top] = op;
}

// Main Function
int evalPostfix(char *exp){
    // Create a stack of capacity of equal to the length of the expression
    struct Stack *stack =  createStack(strlen(exp));
    int i;

    // See if the stack is created
    if(!stack)
        return -1;
    
    // Scan all characters one by one
    for(i = 0; exp[i]; ++i){
        // If the scanned character is Number
        if(isdigit(exp[i]))
            push(stack, exp[i] - '0');
        
        // If the scanned character is an operand
        else{
            int val1 = pop(stack);
            int val2 = pop(stack);

            switch(exp[i]){
                case '+': push(stack, val2 + val1); break;
                case '-': push(stack, val2 - val1); break;
                case '*': push(stack, val2 * val1); break;
                case '/': push(stack, val2/val1); break;
            }
        }
    }

    return pop(stack);
}

// Driver program to test above functions 
int main() 
{ 
    char exp[] = "231*+9-"; 
    printf ("postfix evaluation: %d\n", evalPostfix(exp)); 
    return 0; 
} 