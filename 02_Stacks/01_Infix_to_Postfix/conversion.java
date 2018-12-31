import java.util.Stack;

class conversion{
    // Utility function to give the precedence
    static int Prec(char ch){
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

    // Main Method
    static String infix_to_postfix(String exp){
        // initialising empty string for result
        String result = new String("");

        // initialising empty stack
        Stack<Character>  stack = new Stack<>();

        for (int i = 0; i < exp.length(); ++i){
            char c = exp.charAt(i);

            // If the scanned character is an operand, add it to the output
            if(Character.isLetterOrDigit(c))
                result += c;
            
            // If the scanned character is an '('
            else if(c == '(')
                stack.push(c);
            
            // If the scanned characeter is an ')'
            else if(c == ')'){
                while(!stack.isEmpty() && stack.peek() != '(')
                    result += stack.pop();
                if(!stack.isEmpty() && stack.peek() != '(')
                    return "Invalid Expression";
                else
                    stack.pop();
            }

            // If an operator is encountered
            else{
                while(!stack.isEmpty() && Prec(c) <= Prec(stack.peek()))
                    result += stack.pop();
                stack.push(c);
            }
        }

        // pop all the operators from the stack
        while(!stack.isEmpty())
            result += stack.pop();

        return result;
    }

    // Driver Program
    public static void main(String args[]){
        String exp = "a+b*(c^d-e)^(f+g*h)-i";
        System.out.println(infix_to_postfix(exp));
    }
}