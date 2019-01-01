import java.util.Stack;

class Evaluation{
    // Method to evaluate the postfix expression
    static int evaluatePostfix(String exp){
        // Create a stack
        Stack<Integer> stack = new Stack<>();

        // Scan all characters one by one
        for(int i = 0; i < exp.length(); i++){
            char ch = exp.charAt(i);

            // If the scanned character is number, push it to the stack
            if(Character.isDigit(ch))
                stack.push(ch - '0');
            
            // If the scanned character is operator
            else{
                int val1 = stack.pop();
                int val2 = stack.pop();

                switch(ch){ 
                    case '+':   
                        stack.push(val2+val1); 
                        break; 
                      
                    case '-': 
                        stack.push(val2- val1); 
                        break; 
                      
                    case '/': 
                        stack.push(val2/val1); 
                        break; 
                      
                    case '*': 
                        stack.push(val2*val1); 
                        break; 
              } 
            }
        }
        return stack.pop();
    }

    // Driver program to test above functions 
    public static void main(String args[]){
        String exp="231*+9-"; 
        System.out.println("postfix evaluation: "+evaluatePostfix(exp)); 
    } 
}