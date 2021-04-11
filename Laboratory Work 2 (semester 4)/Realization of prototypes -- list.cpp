#include "Header.h"
#include "List.h"

List::NodeL::NodeL(NodeL* next, NodeH* in_tree, std::string symbol, size_t freq)
{
	this->next = next;
	this->in_tree = in_tree;
	this->symbol = symbol;
	this->freq = freq;
}

void List::add(std::string c, NodeH* pointer, size_t freq)
{
	NodeL* current;                                                 // Pointer to the current list's element

	if (head == NULL)
	{
		head = new NodeL(NULL, pointer, c, freq);
		number++;
	}
	else
	{
		current = find(c);
		if (current != NULL)
			current->freq++;
		else
		{
			current = head;
			while (current->next != NULL)
				current = current->next;

			current->next = new NodeL(NULL, pointer, c, freq);
			number++;
		}
	}
}

List::NodeL* List::get_min()
{
	NodeL* current;                                                 // Pointer to the current list's element
	NodeL* pre_min = NULL;                                          // Pointer to the previous of minimal element
	NodeL* min = head;                                              // Pointer to the minimal element
	NodeL* worker = NULL;                                           // Pointer to the next of current list's element

	if (head == NULL)
		throw std::out_of_range("The list is emoty.");

	current = head;
	while (current != NULL)
	{
		if (current->freq < min->freq)
		{
			pre_min = worker;
			min = current;
		}

		worker = current;
		current = current->next;
	}

	if (pre_min != NULL)
		pre_min->next = min->next;
	else
		head = min->next;

	number--;
	return min;
}

List::NodeL* List::find(std::string c)
{
	NodeL* current;                                                 // Pointer to the current list's element

	if (head == NULL)
		throw std::out_of_range("The list is empty.");

	current = head;
	while (true)
	{
		if (current == NULL)
			return NULL;
		else if (current->symbol == c)
			return current;
		else
			current = current->next;
	}
}
