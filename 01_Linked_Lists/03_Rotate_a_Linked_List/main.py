class Node:
    # Constructor to initialise the node object
    def __init__(self,data):
        self.data = data
        self.next = None

class Sll:    
    # Constructor to initialise the Sll object
    def __init__(self):
        self.start = None
    
    # Function to insert a new node at the beginning
    def push(self, data):
        # allocate the node and put the data
        new_node = Node(data)
        
        # Make new_node link to the start
        new_node.next = self.start

        # Update the start node
        self.start = new_node
    
    # Utility Function to print the list
    def display(self):
        temp = self.start
        while(temp):
            print(temp.data, end = " ")
            temp = temp.next
    
    # Operating Function to rotate the linked list
    def rotate(self,key):
        if key == 0:
            return
        
        cur = self.start
        count = 1
        while(count < key and cur):
            cur = cur.next
        
        if not cur:
            return
        
        keyNode = cur
        while(cur.next):
            cur = cur.next
        cur.next = self.start
        self.start = keyNode.next
        keyNode.next = None


# Driver Program
list = Sll()

# Create a list 10 20 30 40 50
for i in range(60,0,-10):   
    list.push(i)

print("Given List is: ")
list.display()

# Rotate the lsit by 3 for example
list.rotate(3)
print("\nRotated List is: ")
list.display()
print()