#include <iostream>

struct Node{
    Node *prev, *next;
    int data;
    Node(int val) : prev(nullptr), next(nullptr), data(val) {}
};

class DoublyLinkedList{
private:
    Node* head;
    Node* tail;
public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void append(int val){
        Node* newNode = new Node(val);
        if(!head){
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    void deleteNode(int val){
        Node* temp = head;
        while(temp&&temp->data!=val){

        }
    }
};