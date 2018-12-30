#include<iostream>

struct Node{
    int data;
    struct Node* next;
};

class Sll{
    Node *start;

public:
    Sll() : start(NULL) {}

    void push(int);
    void rotate(int);
    void display();
};

int main(){
    // Start with the empty list
    Sll list;
    
    // Create a list 10 20 30 40 50
    for(int i = 50; i> 0; i-= 10)
        list.push(i);
    
    std::cout<<"Given Linked List is: ";
    list.display();

    // Rotating the lsit by 3 for example
    list.rotate(3);
    std::cout<<"\nRotated Linked List is: ";
    list.display();
    std::cout<<std::endl;

    return 0;
}

void Sll::push(int data){
    // allocate node
    Node *new_node = new Node;

    // put in the data
    new_node->data = data;

    // link the old list to the new node
    new_node->next = start;

    // update the start pointer
    start = new_node;
}

void Sll::display(){
    Node *temp = start;
    while(temp){
        std::cout<<temp->data<<' ';
        temp = temp->next;
    }
}

void Sll::rotate(int key){
    // If key is 0, no change occurs
    if(key == 0)
        return;
    
    // Get the key node
    Node *cur = start;
    int count = 1;
    while(count < key && cur){
        cur = cur->next;
        count++;
    }

    // If current is NUll, k is greater than tge size of the linked list, so no chagne occurs
    if(!cur)
        return;

    Node *keyNode = cur;
    while(cur->next)
        cur = cur->next;
    
    cur->next = start;
    start = keyNode->next;
    keyNode->next = NULL;
}
