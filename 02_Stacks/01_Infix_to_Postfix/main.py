# Class to convert the expression
class Conversion:
    # Constructor to initialise the class object
    def __init__(self, cap):
        self.top = -1
        self.capacity = cap

        # This list is used as a stack
        self.array = []
       
        # List for the output string
        self.output = []

        # Precedence
        self.precedence = {'+':1, '-':1, '*':2, '/':2, '^':3}

    # Utiltiy function
    def isEmpty(self):  # To check if the stack is empty
        return True if self.top == -1 else False
    
    def isOperand(self, ch):    # to check the scanned character is an operand
        return ch.isalpha()

    def notGreater(self, ch):   # Check if the precendence of operator is less
        try:
            a = self.precedence[ch]
            b = self.precedence[self.peek()]
            return True if a <=b else False
        except KeyError:
            return False


    # Stack methods
    def peek(self):   # Return the value of the top of the stack
        return self.array[-1]
    
    def pop(self):  # Pop the element from the stack
        if not self.isEmpty():
            self.top -= 1
            return self.array.pop()
        else:
            return "$" 
        
    def push(self, op): # Push the element to the stack
        self.top += 1
        self.array.append(op)


    # Main function
    def infix_to_postfix(self, exp):
        # Iterate over the exp
        for ch in exp:
            # If the character is operand, add it to output
            if self.isOperand(ch):
                self.output.append(ch)
            
            # If the character is an '(', push it to the stack
            elif ch == '(':
                self.push(ch)
            
            # If the character is an ')
            elif ch == ')':
                while((not self.isEmpty()) and self.peek() != '('):
                    self.output.append(self.pop())
                if(not self.isEmpty() and self.peek() != '('):
                    return
                else:
                    self.pop()

            # An operator is scanned
            else:
                while(not self.isEmpty() and self.notGreater(ch)):
                    self.output.append(self.pop())
                self.push(ch)
            
        # Pop all the operator from the stack
        while not self.isEmpty():
            self.output.append(self.pop()) 

        print("".join(self.output))


# Driver Program
exp = "a+b*(c^d-e)^(f+g*h)-i"
obj = Conversion(len(exp))
obj.infix_to_postfix(exp)