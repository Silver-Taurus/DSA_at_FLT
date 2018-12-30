#include<iostream>
#include<string>
#include<stack>

// Utility Function
bool isOperand(char ch){
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

int prec(char ch){  // Function to return the precedence of the operator
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
void infix_to_postifx(std::string s){
    std::stack<char> stack;
    stack.push('$');
    int len = s.length();
    std::string ns;

    for(int i = 0; i < len; i++){
        // If the scanned character is an operand
        if(isOperand(s[i]))
            ns += s[i];
        // If the scanned character is '('
        else if(s[i] == '(')
            stack.push(s[i]);
        // If the scanned operator is ')'
        else if(s[i] == ')'){
            while(stack.top() != '$' && stack.top() != '('){
                char c = stack.top();
                stack.pop();
                ns += c;
            }
            if(stack.top() == '(')
                stack.pop();
        }
        // If the operator is scanned
        else{
            while(stack.top() != '$' && prec(s[i]) <= prec(stack.top())){
                char c = stack.top();
                stack.pop();
                ns += c;
            }           
            stack.push(s[i]);     
        }
    }

    while(stack.top() != '$'){
        char c = stack.top();
        stack.pop();
        ns += c;
    }

    std::cout<<ns<<std::endl;
}

// Driver Program
int main(){
    std::string exp = "a+b*(c^d-e)^(f+g*h)-i";
    infix_to_postifx(exp);
    return 0;
}