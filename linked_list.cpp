#include <iostream>
#include "linked_list.hpp"
using namespace std;

// Constructs an empty linked list by allocating the head pointer and setting it to null.
LinkedList::LinkedList()
{
    head = new Node*;
    *head = nullptr;
    size = 0;
}

// Destroys the linked list.
// NOTE: The cleanup code is currently commented out to avoid double-free issues in some usages.
// If you want the list to automatically free nodes, uncomment clearList() and delete head.
LinkedList::~LinkedList() {
    //clearList();
    //delete head;
}

// Returns the number of nodes currently stored in the list.
int LinkedList::getSize()
{
    return size;
}

// Prints the list contents to stdout, showing the index and value of each node.
void LinkedList::printList()
{
    if (*head == nullptr)
    {
        cout << "List is empty." << endl;
        return;
    }

    int index = 0;
    Node *current = *head;
    while(current != nullptr)
    {
        cout << index << ": " << current->data << endl;
        current = current->next;
        index++;
    }
}

// Deletes every node in the list and resets the head pointer and size counter.
void LinkedList::clearList()
{
    if (*head == nullptr)
    {
        cout << "List is empty, no need to clear." << endl;
        return;
    }
    Node *current = *head;
    Node *temp;
    while (current)
    {
        temp = current;
        current = current->next;
        delete temp;
        size--;
    }
    *head = nullptr;
}

// Appends a new node with the given value to the end of the list.
// If the list is empty, the new node becomes the head.
void LinkedList::appendNode(string value)
{
    Node *newNode = new Node;
    newNode->data = value;
    newNode->next = nullptr;

    if (*head == nullptr)
    {
        *head = newNode;
        cout << "Node appended: " << value << endl;
    }
    else
    {
        Node *current = *head;
        while (current->next != nullptr)
        {
            current = current->next;
        }
        current->next = newNode;
        cout << "Node appended: " << value << endl;
    }
    size++;
}

// Removes the node at the specified zero-based position.
// If the position is invalid, the list remains unchanged.
void LinkedList::removeNode(int position)
{
    if (*head == nullptr)
    {
        cout << "List is empty. No node removed." << endl;
        return;
    }

    if (position < 0 || position >= size)
    {
        cout << "Invalid position. No node removed." << endl;
        return;
    }

    Node *current = *head;
    if (position == 0)
    {
        *head = current->next;
        delete current;
        cout << "Node at position " << position << " removed." << endl;
    }
    else
    {
        Node *previous = nullptr;
        for (int i = 0; i < position; i++)
        {
            previous = current;
            current = current->next;
        }
        previous->next = current->next;
        delete current;
        cout << "Node at position " << position << " removed." << endl;
    }
    size--;
}

// Removes the first node whose data matches the given value.
// If no matching node exists, the list remains unchanged.
void LinkedList::removeNode(string value)
{
    if (*head == nullptr)
    {
        cout << "List is empty. No node removed." << endl;
        return;
    }

    Node *current = *head;
    Node *previous = nullptr;

    while (current != nullptr)
    {
        if (current->data == value)
        {
            if (previous == nullptr)
            {
                *head = current->next;
            }
            else
            {
                previous->next = current->next;
            }
            delete current;
            cout << "Node with value \"" << value << "\" removed." << endl;
            size--;
            return;
        } else {
            previous = current;
            current = current->next;
        }
    }
    cout << "Node with value \"" << value << "\" not found." << endl;
}

// Inserts a new node with the given value at the specified zero-based position.
// If the position is invalid, no node is inserted.
void LinkedList::insertNode(string value, int position)
{
    if (position < 0 || position > size)
    {
        cout << "Invalid position. No node inserted." << endl;
        return;
    }

    Node *current = *head;
    for (int i = 0; i < position - 1; i++)
    {
        current = current->next;
    }

    Node *newNode = new Node();
    newNode->data = value;
    newNode->next = current->next;
    current->next = newNode;
    cout << "Node inserted: " << value << " at position " << position << endl;
    size++;
}

// Pushes a new node onto the front of the list (new head).
void LinkedList::pushNode(string value)
{
    Node *newNode = new Node();
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
    size++;
    cout << "Node pushed: " << value << endl;
}