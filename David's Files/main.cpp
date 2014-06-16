#include <iostream>
#include <iomanip>
#include "IceCreamMenu.h"
//#include "MemTracker.h"

using namespace std;

int main()
{
	IceCreamMenu menu;
	char choice;

	cout << "<Placeholder>" << endl;
	do
	{
		cout << "a. add ice cream flavor" << endl;
		cout << "b. delete ice cream flavor" << endl;
		cout	 << "c. find an ice cream flavor" << endl;
		cout	 << "d. list flavors in hashed table order" << endl;
		cout	 << "e. list flavors in alphabetical order" << endl;
		cout	 << "f. print indented tree" << endl;
		cout	 << "g. display hashtable statistics" << endl;
		cout	 << "h. compare" << endl;
		cout	 << "i. quit" << endl;

			 cin >> choice;
			cin.sync();
			 switch (choice)
			 {
				case 'a': 
					menu.AddFlavor(); break;
				case 'b':
					menu.DeleteFlavor(); break;
				case 'c':
					menu.FindAndDisplayFlavor(); break;
				case 'd':
					menu.ListHashedTable(); break;
				case 'e':
					menu.ListKeySequence(); break;
				case 'f':
					menu.PrintIndentedTree(); break;
				case 'g':
					menu.PrintHashStats(); break;
				case 'h':
					menu.Compare(); break;
				case 'i':
					menu.Quit(); break;
				default:
					cout << "That command was not understood" << endl; break;
			 }
	} while (choice != 'i');
	return 0;
}