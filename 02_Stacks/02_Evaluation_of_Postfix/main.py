# Main Function
def evaluatePostfix(exp):
    # Create stack representation
    stack = []

    # Iterate over the expression to scan the characters
    for ch in exp:
        # If the scanned character is Number
        if ch.isdigit():
            stack.append(ch)
        
        # If the scanned character is operator
        else:
            val1 = stack.pop(-1)
            val2 = stack.pop(-1)
            stack.append(str(eval(val2 + ch + val1)))
        
    return int(stack.pop())

# Driver Program
exp = "231*+9-"
print("Postfix evaluation: {}".format(evaluatePostfix(exp)))