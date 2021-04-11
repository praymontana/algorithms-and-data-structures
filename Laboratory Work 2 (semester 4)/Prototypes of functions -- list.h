#pragma once
#include "Header.h"

// Class that describes the list 
class List
{
public:
	class NodeL
	{
	public:
		NodeL* next;                                            // Pointer to the next element if the list
		std::string symbol;                                     // Symbol of the element
		NodeH* in_tree;                                         // Its analogue in Huffman's tree
		size_t freq;                                            // Frequency of the element

		NodeL(NodeL* next, NodeH* in_tree, std::string symbol, size_t freq);
	};

	NodeL* head;                                                // Head of the list
	size_t number;                                              // Number of elements

	List()
	{
		head = nullptr;
		number = 0;
	}

	~List()
	{
		NodeL* current;
		NodeL* deleted;

		current = head;
		while (current)
		{
			deleted = current;
			current = current->next;
			delete deleted;
		}
	}

    // Add a new element
	void add(std::string elem, NodeH* pointer, size_t freq = 1);

    // Get the minimal element
	NodeL* get_min();

    // Find the needing element
	NodeL* find(std::string c);
};
