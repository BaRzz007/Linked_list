#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

#include <string>
using namespace std;

class LinkedList
{
private:
    struct Node
    {
        string data;
        Node *next;
    };

    Node **head;
    int size;
public:
    LinkedList();
    ~LinkedList();
    void printList();
    void removeNode(int position);
    void removeNode(string value);
    void appendNode(string value);
    void insertNode(string value, int position);
    void pushNode(string value);
    void clearList();
    int getSize();
}

#endif // LINKED_LIST_HPP