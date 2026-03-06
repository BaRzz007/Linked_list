#include "console.hpp"
#include <sstream>

class Console::Context
{
public:
    Context(string name)
    {
        this->name = name;
        this->list = LinkedList();
    }

    void append(string value)
    {
        this->list.appendNode(value);
    }

    void insert(string value, int position)
    {
        this->list.insertNode(value, position);
    }

    void push(string value)
    {
        this->list.pushNode(value);
    }

    void remove(string value)
    {
        this->list.removeNode(value);
    }

    void remove(int position)
    {
        this->list.removeNode(position);
    }

    void clearList()
    {
        this->list.clearList();
    }

    void printList()
    {
        cout << "List: " << this->name << endl;
        this->list.printList();
    }
private:
    string name;
    LinkedList list;
};

void Console::run()
{
    string buffer;
    vector<string> tokens;
    cout << "Welcome to the Linked List Console!" << endl;
    cout << "Type 'help' for a list of commands." << endl;

    while (true)
    {
        cout << prompt;
        buffer = input();
        tokens = parse(buffer);
        if (exec(tokens)) {
            break;
        }
    }
}

bool Console::exec(vector<string> tokens)
{
    if (tokens.empty())
    {
        return false;
    }

    string command = tokens[0];

    if (command == "create")
    {
        if (tokens.size() > 1) createList(tokens[1]);
        else cout << "Usage: create <list_name>" << endl;
    } else if (command == "lists") {
        showAll();
    } else if (command == "help") {
        help(tokens.size() > 1 ? tokens[1] : "");
    }
    
}