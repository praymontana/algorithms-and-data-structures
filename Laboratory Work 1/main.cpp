#include <iostream>
#include "LinkedList.h"

using namespace std;

int main() {
	LinkedList lst;
	LinkedList lst2;

	size_t index;
	int data,
		elem,
		ans;

	do
	{
		cout << "Choose what you want to do with your list: \n";
		cout << "1) Fill the list from the start \n";
		cout << "2) Fill the list from the end \n";
		cout << "3) Delete the last element \n";
		cout << "4) Delete the first element \n";
		cout << "5) Add the new element by its ID \n";
		cout << "6) Get the element by its ID \n";
		cout << "7) Remove the element by its ID \n";
		cout << "8) Get size of the list \n";
		cout << "9) Print the list to console \n";
		cout << "10) Clear the list \n";
		cout << "11) Change the element by its ID \n";
		cout << "12) Find the last entering in the list \n";
		cout << "13) Close the program \n";
		cout << "Your choice: \n";

		cin >> ans;
		switch (ans)
		{
		case (1):
			cout << "Enter the value of the element: \n";
			cin >> data;
			lst.push_front(data);
			cout << "Successfully! \n";

			system("pause");
			system("cls");
			break;

		case (2):
			cout << "Enter the value of the element: \n";
			cin >> data;
			lst.push_back(data);
			cout << "Successfully! \n";

			system("pause");
			system("cls");
			break;

		case (3):
			lst.pop_back();
			cout << "Successfully! \n";

			system("pause");
			system("cls");
			break;

		case (4):
			lst.pop_front();
			cout << "Successfully! \n";

			system("pause");
			system("cls");
			break;

		case (5):
			if (!lst.isempty()) {
				cout << "Enter the value of the element: \n";
				cin >> data;
				cout << "Enter the ID fron 0 to " << lst.get_size() - 1 << ": \n";
				cin >> index;
				try {
					lst.insert(data, index);
				}
				catch (out_of_range e) {
					cerr << e.what() << endl;
					do
					{
						cout << "try again: ";
						cin >> index;
					} while (index >= lst.get_size());
					lst.insert(data, index);
				}
				cout << "Successfully! \n";
			}
			else
				cerr << "The list is empty! Fill it first." << endl;

			system("pause");
			system("cls");
			break;

		case (6):
			if (!lst.isempty()) 
			{
				cout << "Enter the ID fron 0 to " << lst.get_size() - 1 << ": \n";
				cin >> index;
				try {
					lst.at(index);
				}
				catch (out_of_range e) {
					cerr << e.what() << endl;
					do
					{
						cout << "try again: ";
						cin >> index;
					} while (index >= lst.get_size());
				}
				cout << lst.at(index);
			}
			else
				cerr << "The list is empty! Fill it first." << endl;

			system("pause");
			system("cls");
			break;

		case (7):
			if (!lst.isempty()) {
				cout << "Enter the ID fron 0 to " << lst.get_size() - 1 << ": \n";
				cin >> index;
				try {
					lst.remove(index);
				}
				catch (out_of_range e) {
					cerr << e.what() << endl;
					do
					{
						cout << "try again: ";
						cin >> index;
					} while (index >= lst.get_size());
					lst.remove(index);
				}
				cout << "Successfully! \n";
			}
			else
				cerr << "The list is empty! Fill it first." << endl;

			system("pause");
			system("cls");
			break;

		case (8):
			cout << "Size of the list: " << lst.get_size() << endl;

			system("pause");
			system("cls");
			break;

		case (9):
			cout << "Your list:" << endl;
			if (lst.isempty())
				cout << "...is empty!" << endl;
			else
				lst.print_to_console();

			system("pause");
			system("cls");
			break;

		case (10):
			try
			{
				lst.clean();
				cout << "Successfully!" << endl;
			}
			catch (out_of_range e)
			{
				cerr << e.what() << endl;
				cout << "Fill the list first." << endl;
			}

			system("pause");
			system("cls");
			break;

		case (11):
			cout << "Enter the value of the element: \n";
			cin >> data;
			cout << "Enter the ID fron 0 to " << lst.get_size() - 1 << ": \n";
			cin >> index;
			try {
				lst.set(data, index);
			}
			catch (out_of_range e) {
				cerr << e.what() << endl;
				do
				{
					cout << "try again: ";
					cin >> index;
				} while (index >= lst.get_size());
			}
			cout << "Successfully! \n";

			system("pause");
			system("cls");
			break;

		case(12):
			system("cls");
			try
			{
				do
				{
					cout << "Enter an element of the second list -- ";
					cin >> elem;
					lst2.push_back(elem);

					cout << "Do you want to continue entering? If not, enter 0 -- ";
					cin >> ans;
				} while (ans != 0);

				index = lst.find_last(lst, lst2);

				cout << "The last entering in the main list was in the " << index << " ID." << endl;
				cout << "The Second ";
				lst2.clean();
			}
			catch (const char* exeption)
			{
				cerr << "Error: " << exeption << endl;
			}

			system("pause");
			system("cls");
			break;

		case(13):
			cout << "See you!" << endl;
			lst.cleaning();
			break;
			
		default:
			cout << "Incorrect input. Try again." << endl;
			system("pause");
			system("cls");
		}
	} while (ans != 13);

	return 0;
}
