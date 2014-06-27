//Main.cpp was created by David Nguyen
#include <iostream>
#include <iomanip>
#include <cctype>
#include "IceCreamMenu.h"

using namespace std;

int main()
{
	IceCreamMenu menu;
	char choice;

	cout << "Welcome to the Ice Cream Shoppe inventory system: " << endl;
	do
	{
		cout << "a. add ice cream flavor" << endl;
		cout << "d. delete ice cream flavor" << endl;
		cout << "f. find and display an ice cream flavor" << endl;
		cout << "h. list flavors in hashed table order" << endl;
		cout << "k. list flavors in key sequence" << endl;
		cout << "i. print indented tree" << endl;
		cout << "s. display hashtable statistics" << endl;
		cout << "c. compare" << endl;
		cout << "q. quit" << endl;

		cin >> choice;
		cin.sync();
		switch (tolower(choice))
		{
			case 'a': 
				menu.AddFlavor(); break;
			case 'd':
				menu.DeleteFlavor(); break;
			case 'f':
				menu.FindAndDisplayFlavor(); break;
			case 'h':
				menu.ListHashedTable(); break;
			case 'k':
				menu.ListKeySequence(); break;
			case 'i':
				menu.PrintIndentedTree(); break;
			case 's':
				menu.PrintHashStats(); break;
			case 'c':
				menu.Compare(); break;
			case 'q':
				menu.Quit(); break;
			default:
				cout << "That command was not understood" << endl; break;
		}
	} while (choice != 'q');
	return 0;
}