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
    } else if (command == "exit") {
        for(auto &pair : context_map) {
            pair.second.clearList();
        }
        return true;
    } else {
        auto it = context_map.find(command);
        if (it == context_map.end()) {
            cout << "List '" << command << "' not found. Type 'lists' to see all lists." << endl;
            return false;
        }

        Context &ctx = it->second;
        if (tokens.size() < 2) {
            cout << "Usage: " << command << " <operation> [args]" << endl;
            return false;
        }

        string operation = tokens[1];
        if (operation == "append" && tokens.size() > 2) ctx.append(tokens[2]);
        else {
            cout << "Usage: " << command << " append <value>" << endl;
            return false;
        }
        if (operation == "push" && tokens.size() > 2) ctx.push(tokens[2]);
        else {
            cout << "Usage: " << command << " push <value>" << endl;
            return false;
        }
        if (operation == "insert") {
            if (tokens.size() > 3) {
                try {
                    int pos = stoi(tokens[3]);
                    ctx.insert(tokens[2], pos);
                } catch (invalid_argument&) {
                    cout << "Position must be an integer." << endl;
                }
            } else {
                cout << "Usage: " << command << " insert <value> <position>" << endl;
                return false;
            }
        }
        if (operation == "remove" && tokens.size() > 2) {
            try {
                int pos = stoi(tokens[2]);
                ctx.remove(pos);
            } catch (invalid_argument&) {
                ctx.remove(tokens[2]);
            }
        } else {
            cout << "Usage: " << command << " remove <value|position>" << endl;
            return false;
        }
        if (operation == "show_all") {
            ctx.printList();
            return false;
        }
        cout << command << ": " << operation << ": " << "invalid operation" << endl;
    }
    return false;
}

void Console::createList(string name)
{
    if (context_map.find(name) == context_map.end()) {
        context_map[name] = Context(name);
        cout << "List '" << name << "' created." << endl;
    } else {
        cout << "List '" << name << "' already exists." << endl;
    }
}

void Console::showAll()
{
    if (context_map.empty()) {
        cout << "No lists have been created yet." << endl;
        return;
    }

    cout << "Existing lists:" << endl;
    for (const auto &pair : context_map) {
        cout << "- " << pair.first << endl;
    }
}

void Console::help(string operation)
{
    if (operation.empty()) {
        cout << "Available commands:" << endl;
        cout << "  create <list_name> - Create a new list" << endl;
        cout << "  lists - Show all existing lists" << endl;
        cout << "  <list_name> <operation> [args] - Perform an operation on a list" << endl;
        cout << "  help [command] - Show help for a specific command" << endl;
        cout << "  exit - Exit the console" << endl;
    } else if (operation == "create") {
        cout << "Usage: create <list_name>" << endl;
        cout << "Creates a new list with the specified name." << endl;
    } else if (operation == "lists") {
        cout << "Usage: lists" << endl;
        cout << "Shows all existing lists." << endl;
    } else if (operation == "<list_name>") {
        cout << "Usage: <list_name> <operation> [args]" << endl;
        cout << "Performs an operation on the specified list. Operations include:" << endl;
        cout << "  append <value> - Append a value to the end of the list" << endl;
        cout << "  push <value> - Push a value to the front of the list" << endl;
        cout << "  insert <value> <position> - Insert a value at a specific position in the list" << endl;
        cout << "  remove <value|position> - Remove a value or node at a specific position from the list" << endl;
        cout << "  show_all - Show all elements in the list" << endl;
    } else {
        cout << "No help available for '" << operation << "'." << endl;
    }
}

string Console::input()
{
    string line;
    getline(cin, line);
    return line;
}

vector<string> Console::parse(string buffer)
{
    vector<string> tokens;
    if (buffer.empty())
    {
        tokens = {};
        return tokens;
    }

    stringstream ss(buffer);
    string token;
    char quote = '\0';

    while (ss >> ws)
    {
        if (ss.peek() == '"' || ss.peek() == '\'')
        {
            quote = ss.get();
            getline(ss, token, quote);
            tokens.push_back(token);
        }
        else
        {
            ss >> token;
            tokens.push_back(token);
        }
    }
    return tokens;
}