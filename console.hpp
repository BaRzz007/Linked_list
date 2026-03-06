#ifndef CONSOLE_HPP
#define CONSOLE_HPP

using namespace std;
#include <iostream>
#include <string>
#include <memory>
#include <unordered_map>
#include <vector>
#include "linked_list.hpp"

class Console
{
public:
    void run();
private:
    class Context;
    unordered_map<string, Context> context_map;
    string prompt = ">> ";
    string input();
    void help(string func = "");
    void createList(string name);
    void showAll(); //prints all contexts (lists) and their sizes
    void exec(vector<string> tokens);
    vector<string> parse(string input);
};

#endif // CONSOLE_HPP