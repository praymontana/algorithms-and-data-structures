#include "Header.h"
#include "List.h"
#include <cmath>

NodeH::NodeH(std::string value, int freq, NodeH* parent, NodeH* left, NodeH* right)
{
    this->value = value;
    this->code = "";
    this->frequency = freq;
    this->parent = parent;
    this->left = left;
    this->right = right;
}

void HUFF::read_from_file(std::string name_of_file)
{
    std::ifstream file(name_of_file);                               // Opening file
    size_t i;                                                       // Loop parameter

    if (file.is_open())
    {
        while (file.peek() != EOF)
        {
            set_of_symbols += file.get();
        }

        for (i = 0; i < set_of_symbols.length(); i++)
            lst->add(set_of_symbols.substr(i, 1), NULL);
    }
    else
        std::cout << "There was a problem with opening the file. Check it and try again." << std::endl;
}


void HUFF::read_from_console(std::string data)
{
    size_t i;                                                       // Loop parameter

    if (data != "")
    {
        set_of_symbols = data;

        for (i = 0; i < set_of_symbols.length(); i++)
            lst->add(set_of_symbols.substr(i, 1), NULL);
    }
    else
        std::cout << "There was a problem with reading the entered string. Check it and try again." << std::endl;
}


NodeH* HUFF::finder(char key)
{
    NodeH* current = this->Root;                                    // Pointer to the current node for finding

    while (true)
    {
        if (current == NULL)
            return NULL;

        if ((current->value[0] == key) && (current->value.length() == 1))
            return current;
        else
        {
            size_t i;
            NodeH* left_child = current->left;

            for (i = 0; i < left_child->value.length(); i++)
            {
                if (current->value[i] == key)
                {
                    current = current->left;
                    break;
                }
            }

            if (i == left_child->value.length())
                current = current->right;
        }
    }
}

void HUFF::coding()
{
    List::NodeL* first_minimal;                                             // First minimal list's element
    List::NodeL* second_minimal;                                            // Second minimal list's element (first was deleted)
    NodeH* their_parent;                                                    // Pointer to the parent of creating nodes
    NodeH* first_leaf;                                                      // First creating node
    NodeH* second_leaf;                                                     // Second creating node

    if (lst->number == 0)
        throw std::out_of_range("The list is empty. Fill it first.");
    else if (lst->number == 1)
    {
        first_minimal = lst->get_min();
        Root = new NodeH(first_minimal->symbol, first_minimal->freq, NULL, NULL, NULL);
        delete first_minimal;
    }

    do
    {
        first_minimal = lst->get_min();
        second_minimal = lst->get_min();

        first_leaf = first_minimal->in_tree;
        second_leaf = second_minimal->in_tree;

        if (first_leaf && !second_leaf)
        {
            second_leaf = new NodeH(second_minimal->symbol, second_minimal->freq, NULL, NULL, NULL);
            count++;
        }
        else if (second_leaf && !first_leaf)
        {
            first_leaf = new NodeH(first_minimal->symbol, first_minimal->freq, NULL, NULL, NULL);
            count++;
        }
        else if (!second_leaf && !first_leaf)
        {
            first_leaf = new NodeH(first_minimal->symbol, first_minimal->freq, NULL, NULL, NULL);
            second_leaf = new NodeH(second_minimal->symbol, second_minimal->freq, NULL, NULL, NULL);
            count += 2;
        }

        if (first_leaf->value > second_leaf->value)
            their_parent = new NodeH(second_leaf->value + first_leaf->value, first_leaf->frequency + second_leaf->frequency, NULL, second_leaf, first_leaf);
        else
            their_parent = new NodeH(first_leaf->value + second_leaf->value, first_leaf->frequency + second_leaf->frequency, NULL, first_leaf, second_leaf);

        first_leaf->parent = their_parent;
        second_leaf->parent = their_parent;

        delete first_minimal;
        delete second_minimal;

        // Their parent is a single element -- add it in the list 
        lst->add(their_parent->value, their_parent, their_parent->frequency);
    } while (lst->number != 1);

    first_minimal = lst->get_min();
    Root = first_minimal->in_tree;
    delete first_minimal;

    forming_codes(Root);
}

void HUFF::forming_codes(NodeH* prev)
{
    NodeH* current = prev;                                          // Pointer to the current element

    if (current->left)
    {
        current->left->code = prev->code + "0";
        forming_codes(current->left);
    }
    if (current->right)
    {
        current->right->code = prev->code + "1";
        forming_codes(current->right);
    }
}

void HUFF::print_code(NodeH* current)
{
    if (current == NULL)
        throw std::out_of_range("The tree is empty!");

    if (current->left)
        print_code(current->left);
    if (current->right)
        print_code(current->right);

    if ((current->left == nullptr) && (current->right == nullptr))
    {
        std::cout << current->value << " code: " << current->code << " frequency: " << current->frequency << std::endl;
    }
}

size_t HUFF::get_code(NodeH* current, Decode** array, size_t index)
{
    if (!current->left && !current->right)
    {
        array[index]->val = current->value;
        array[index]->kod = current->code;
        return index + 1;
    }
    else
    {
        index = get_code(current->left, array, index);
        index = get_code(current->right, array, index);
    }
}

std::string HUFF::coder()
{
    std::string result = "";                                        // Resulting string
    NodeH* current;                                                 // Pointer to the current element
    size_t i,                                                       // Loop parameter
        cnt = 2;                                                    // Power of two for uniform encoding

    for (i = 0; i < set_of_symbols.length(); i++)
    {
        current = finder(set_of_symbols[i]);

        result += current->code;
    }
    std::cout << result << std::endl;
    std::cout << "Huffman code's length: " << result.length() << std::endl;
    while (count > std::pow(2, cnt))
        cnt++;

    std::cout << "Uniform code's length: " << set_of_symbols.length() * cnt << std::endl;
    std::cout << "\nCompression ratio: " << 1 - (float)result.length()/(set_of_symbols.length() * cnt) << std::endl;

    return result;
}

std::string HUFF::decoder(std::string data)
{
    Decode** decode;                                                // List of letters and their codes
    std::string helper;                                             // Helping string for decoding
    std::string result = "";                                        // Resulting string
    size_t bias = 0,                                                // Bias of string's index
        i, j;                                                       // Loop parameters

    decode = new Decode*[count];

    for (i = 0; i < count; i++)
        decode[i] = new Decode();

    get_code(Root, decode, 0);

    while (bias < data.length())
    {
        for (j = 0; j < count; j++)
        {
            if (data.length() - bias >= decode[j]->kod.length())
            {
                helper = data.substr(bias, decode[j]->kod.length());
                if (helper == decode[j]->kod)
                {
                    result += decode[j]->val;
                    bias += decode[j]->kod.length();
                    break;
                }
            }
        }
    }

    std::cout << result << std::endl;
    return result;
}
