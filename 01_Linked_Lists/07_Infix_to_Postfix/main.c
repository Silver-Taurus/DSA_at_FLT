#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef enum{false,true} bool;

// Stack implementation
struct Stack{
    int top;
    unsigned capacity;
    char *arr;
};

// Stack Operations
struct Stack* createStack(unsigned cap){
    struct Stack *stack = (struct Stack*)malloc(sizeof(struct Stack));
    
    if(!stack)
        return NULL;
    
    stack->top = -1;
    stack->capacity = cap;
    stack->arr = (char*)malloc(stack->capacity * sizeof(char));

    if(!stack->arr)
        return NULL;
    
    return stack;
}

// Utility Functions
bool isEmpty(struct Stack *stack){
    return stack->top == -1;
}
char peek(struct Stack *stack){
    return stack->arr[stack->top];
}
char pop(struct Stack *stack){
    if(!isEmpty(stack))
        return stack->arr[stack->top--];
    return '$';
}
void push(struct Stack *stack, char op){
    stack->arr[++stack->top] = op;
}
bool isOperand(char ch){
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}
int Prec(char ch){  // Function to return the precedence of the operator
    switch(ch){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        case '^':
            return 3;
    }
    return -1;
}


// Main Function
void infix_to_postfix(char *exp){
    int i, j;

    // Create a stack of capacity equal to expression
    struct Stack *stack = createStack(strlen(exp));
    if(!stack)
        return;

    for(i = 0, j = -1; exp[i]; ++i){
        // If the scanned cahracter is an operand
        if(isOperand(exp[i]))
            exp[++j] = exp[i];
        // If the scanned operator is '('
        else if (exp[i] == '(')
            push(stack,exp[i]);
        // If the scanned operator is ')'
        else if(exp[i] == ')'){
            while(!isEmpty(stack) && peek(stack) != '(')
                exp[++j] = pop(stack);
            if(!isEmpty(stack) && peek(stack) != '(')
                return;
            else
                pop(stack);
        }
        // If the scanned token is operator
        else{
            while(!isEmpty(stack) && Prec(exp[i]) <= Prec(peek(stack)))
                exp[++j] = pop(stack);
            push(stack, exp[i]);
        }
    }

    // Pop all the operators from the stack
    while(!isEmpty(stack))
        exp[++j] = pop(stack);
    
    exp[++j] = '\0';
    printf("%s\n",exp);
}

// Driver Program
int main(){
    char exp[] = "a+b*(c^d-e)^(f+g*h)-i";
    infix_to_postfix(exp);
    return 0;
}