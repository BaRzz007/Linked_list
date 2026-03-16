#include <iostream>
#include "linked_list.hpp"
using namespace std;

// constructor to initialize the linked list
LinkedList::LinkedList()
{
    head = new Node*;
    *head = nullptr;
    size = 0;
}

// destructor to clean up the linked list
LinkedList::~LinkedList() {
    //clearList();
    //delete head;
}

int LinkedList::getSize()
{
    return size;
}

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

// method to append a node to the end of the linked list
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

void LinkedList::pushNode(string value)
{
    Node *newNode = new Node();
    newNode->data = value;
    newNode->next = *head;
    *head = newNode;
    size++;
    cout << "Node pushed: " << value << endl;
}