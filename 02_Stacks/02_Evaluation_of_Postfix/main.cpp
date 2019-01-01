#include<iostream>
#include<string.h>
#include<stack>

// Main Funtion
int evaluatePostfix(std::string exp){
    // Create the stack
    std::stack<int> stack;

    // Scan the characters
    for(char &ch: exp){
        // If the scanned character is a Number
        if(isdigit(ch))
            stack.push(ch - '0');
        
        // If the scanned character is an operator
        else{
            int val1 = stack.top(); stack.pop();
            int val2 = stack.top(); stack.pop();
            switch(ch){
            case '+': stack.push(val2 + val1); break;  
            case '-': stack.push(val2 - val1); break;  
            case '*': stack.push(val2 * val1); break;  
            case '/': stack.push(val2 / val1); break;  
            }
        }
    }

    return stack.top();
}

// Driver Program
int main()  {  
    std::string exp = "231*+9-";  
    std::cout<<"postfix evaluation: "<< evaluatePostfix(exp);  
    std::cout<<std::endl;
    return 0;  
}  