/**/

#include <iostream>
#include <iomanip>

int main()
{
	IceCreamMenu menu;
	char choice;

	cout << "<Placeholder>" << endl;
	do
	{
		cout << "a. add ice cream flavor" << endl;
			 << "b. delete ice cream flavor" << endl;
			 << "c. find an ice cream flavor" << endl;
			 << "d. list flavors in hashed table order" << endl;
			 << "e. list flavors in alphabetical order" << end;
			 << "f. print indented tree" << endl;
			 << "g. display hashtable statistics" << endl;
			 << "h. compare" << endl;
			 << "i. quit" << end;

			 cin >> choice;
			 //need to flush
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