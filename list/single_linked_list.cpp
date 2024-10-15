#include <iostream>

struct Node{
    Node* nxt;
    int data;
    Node(int val) : nxt(nullptr), data(val) {}
};
class SingleLinkedList{
private: 
    Node* head;
public:
    SingleLinkedList() : head(nullptr){}
    void insert(int val){
        Node* newNode = new Node(val);
        if(!head){
            head = newNode;
            return;
        }
        Node* last_node = head;
        while(last_node->nxt){
            last_node = last_node->nxt;
        }
        last_node->nxt = newNode;
    }
    void print() {
        Node* curNode = head;
        while (curNode) {
            std::cout << curNode->data;
            if (curNode->nxt) {
                std::cout << " -> ";
            }
            curNode = curNode->nxt;
        }
        std::cout << "\n";
    }
};

int main(){
    std::ios::sync_with_stdio(0);
    std::cin.tie(0);
    SingleLinkedList singlelinkedlist;
    singlelinkedlist.insert(10);
    singlelinkedlist.insert(20);
    singlelinkedlist.insert(30);

    singlelinkedlist.print();

}
