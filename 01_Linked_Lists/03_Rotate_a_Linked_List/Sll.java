class Sll{
    Node start;  // head of list
    
    // Linked list Node
    class Node{
        int data;
        Node next;

        Node(int d){
            data = d;
            next = null;
        }
    }

    // Operating functions
    void push(int data){
        // Allocate the Node and the put in the data
        Node new_node = new Node(data);

        // Make next of new_node as start
        new_node.next = start;

        // update the start pointer
        start = new_node;
    }

    void display(){
        Node temp = start;
        while(temp != null){
            System.out.print(temp.data + " ");
            temp = temp.next;
        }
        System.out.println();
    }

    void rotate(int key){
        if(key == 0)
            return;
        
        Node cur = start;
        int count = 1;
        while(count < key && cur != null){
            cur = cur.next;
            count++;
        }

        if(cur == null)
            return;
        
        Node keyNode = cur;
        while(cur.next != null)
            cur = cur.next;
        cur.next = start;
        start = keyNode.next;
        keyNode.next = null;
    }

    // Driver program
    public static void main(String args[]){
        Sll list = new Sll();

        // Create a list 10 20 30 40 50
        for(int i = 50; i > 0; i -= 10)
            list.push(i);
        
        System.out.print("Given list is: ");
        list.display();

        // Rotate the list by 3 for example
        list.rotate(3);
        System.out.print("Rotated list is: ");
        list.display();
    }
}
