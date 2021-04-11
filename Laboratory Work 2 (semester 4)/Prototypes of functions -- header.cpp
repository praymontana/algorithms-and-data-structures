#pragma once 

#include <iostream>
#include <fstream>

// Class for describing the node
class NodeH
{
private:

    std::string value;							            // NodeH element's value
    std::string code;                                       // NodeH element's code
    int frequency;                                          // Frequency of occurence
    NodeH* parent;					                        // Pointer to parent node
    NodeH* left;					                        // Pointer to the left child
    NodeH* right;					                        // Pointer to the right child

    NodeH(std::string value, int freq, NodeH* parent, NodeH* left, NodeH* right);

    friend class HUFF;
};

// Class describing the helping list
#include "List.h"

class Decode
{
public:
    std::string val;                                        // Element's value
    std::string kod;                                        // Element's code

    Decode()
    {
        this->val = "";
        this->kod = "";
    }

    Decode(std::string val, std::string kod)
    {
        this->val = val;
        this->kod = kod;
    }
};

// Class describing the Huffman code's tree
class HUFF
{
public:

    size_t count;                    // Number of nodes
    std::string set_of_symbols;      // Set of symbols in the incoming string
    List* lst;                       // Helping list of single symbols
    NodeH* Root = NULL;              // Binary tree's root

    HUFF()
    {
        count = 0;
        set_of_symbols = "";
        lst = new List();
    }

    ~HUFF()
    {
        delete lst;
    }

    // Return the root's value
    NodeH* get_root() { return Root; }

    // Return the set of symbols
    std::string get_set() { return set_of_symbols; }

    // Read the data from file 
    void read_from_file(std::string name_of_file);

    // Read the data from console
    void read_from_console(std::string data);

    // Find the needing node
    NodeH* finder(char key);

    // Creating a binary tree
    void coding();

    // Give a code for every tree's leaf
    void forming_codes(NodeH* prev);

    // Print the code and frequency of every leaf 
    void print_code(NodeH* root);

    // Get every leaf's code for decoding
    size_t get_code(NodeH* current, Decode** array, size_t index);

    // Coding the incoming data
    std::string coder();

    // Decoding the incoming data
    std::string decoder(std::string data);
};
