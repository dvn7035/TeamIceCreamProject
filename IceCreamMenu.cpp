//IceCreamMenu.cpp
//By:Saquiba Tariq, Sean Ashe, David Ngyuen

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "LinkedList.h"
#include "List.h"
#include "IceCreamFlavor.h"
#include "IceCreamMenu.h"
#include "HashedTable.h"
#include "BinarySearchTree.h"

// display function to pass to BST traverse functions
void display (IceCreamFlavor*& anItem) 
{
	cout << *anItem;
} 
void Delete (IceCreamFlavor*& anItem) 
{
	delete anItem;
} 
void displayForIndented(IceCreamFlavor* anItem)
{
	cout << anItem->getName() << endl;
}

bool compareL(IceCreamFlavor *item1, IceCreamFlavor *item2)
{
	return item1->getName() < item2->getName();
}

bool compareE(IceCreamFlavor *item1, IceCreamFlavor *item2)
{
	return item1->getName() == item2->getName();
}

/*
IceCreamMenu constructor
Reads file to get number of flavors. Then calls to allocate memory in hashtable.
Then, reads in data from file and stores the adresses of the flavor in the tree and hashtable.
*/
IceCreamMenu::IceCreamMenu()
{
	string flavor;			//stores flavor
	string cmpnut = "nut";	//compares the word nut to what is is in the string nut to know if there are nuts or no nuts in the ice cream
	string nut;			//read in nut
	bool isNut = false;		//stores if there is a nut
	int calorie;			//stores calories
	double price;			//stores price
	string punct;			//stores a comma or newline read in

	int count = 0;			//store count for hashtable size

	ifstream infile;
	string fname;

	infile.open("IceCreamShop.txt");
	while (!infile)							// check for file open success or prompt for filename
	{
		cout << "Error opening "<<fname<< "file."<<endl<<"Enter filename: ";
		cin >> fname;
		fname += ".txt";
		infile.open (fname.c_str());
	}

	while (getline(infile, punct, '\n'))		
		count++;									//allocate memory for hashtable
	//cout<<"COUNT: "<<count<<endl;
	HST.AllocateMemory(count);				


	infile.clear();								//reset point to beginning of file
	infile.seekg(0, infile.beg);


	while (getline(infile, flavor, ','))
	{
		if(flavor != "\n")
		{
			if (flavor[0] == '\n')
				flavor.erase(0,1);
			getline(infile, nut, ',');				//reads in nut which is seperated by a comma
			nut.erase(0,1);
			infile>>calorie>>punct>>price;	

			if (nut==cmpnut)
				isNut=true;
			else
				isNut=false;

												//calls to insert
			IceCreamFlavor* data = new IceCreamFlavor(flavor, price, calorie, isNut);
			IceCreamFlavor* returned = new IceCreamFlavor();
			if (!HST.add(data) || !BST.insert(compareL, compareE, data))
				cout<<"Data Entry Failed"<<endl;
		}

	}

	infile.close();									//Close file
}
/*
AddFlavor
Adds the adress of the flavor into the hash table and tree
First, it prompts for the flavor. Then checks if that flavor exists.
If it doesn't it continues to prompt for the rest of the flavor's information.
Else, it prints a message saying that the flavor is already in the shop.
*/
void IceCreamMenu::AddFlavor()
{
	string name;
	double price;
	int calories;
	int pick;
	IceCreamFlavor* flavor = new IceCreamFlavor();
	IceCreamFlavor* returned;
	bool valid = false;

	cout<<"What flavor would you like to add?\nEnter the name of the flavor: ";
	getline (cin, name);
	flavor->setName(name);
	cin.sync();
	cout<<endl;

	if ((HST.getEntry(flavor, returned)))	
		cout<<"We already have " << flavor->getName() << " in our shop. \n"<<endl;
	else
	{
		cout<<endl;
		do
		{
			cout<<"Are there nuts in "<<name<< " ?\nEnter 1 for yes and 0 for no;\nyou will be prompted again if you submit an invalid answer: ";
			cin>>pick;
			cin.sync();
			if ((pick == 0)||(pick == 1))
				valid = true;
			else
				valid = false;
		}while (!valid);		
	
		if (pick == 1)
			flavor->setnuts(true);
		else
			flavor->setnuts(false);
	
		cout<<endl;

		cout<<"How many calories are there?\nEnter number of calories: ";
		cin>>calories;
		flavor->setcal(calories);
		cin.sync();

		cout<<endl; 

		cout<<"How much does this flavor cost?\nEnter cost without dollar sign: ";
		cin>>price;
		flavor->setPrice(price);

		cout<<endl;
	
		BST.insert(compareL, compareE, flavor);				//insert in BST at end
		HST.add(flavor);
	}

	return;
}
/*
DeleteFlavor
First it prompts the user as to which flavor needs to be deleted.
Then it tries to remove from the Hashtable, and if it can then it goes on to remove from the BST.
Then, the actual adress information is deleted.
*/
void IceCreamMenu::DeleteFlavor()
{
	string name;
	IceCreamFlavor* flavor = new IceCreamFlavor();
	IceCreamFlavor* returned; 

	cout<<"What flavor would you like to delete?\nEnter the name of the flavor: ";
	getline (cin, name);
	flavor->setName(name);
	cout<<endl;

	if (HST.remove(flavor, returned) && (BST.remove(compareL, flavor)))	//bst
	{
		delete returned;
		cout<<"entry deleted\n\n";								//returned has the adress of storage
	}
	else 
		cout<<"Entry cannot be found.\n"<<endl;

	delete flavor;

	return;
}
/*
Find and Display flavor
Prompts the user to which flavor he or she would like to look up. Then, it searches for the flavor
in the HashTable because it would be faster. Then if it is found,it displays the information.
If it is not found, it says that the entry was not found.
*/
void IceCreamMenu::FindAndDisplayFlavor()
{
	string name;
	IceCreamFlavor* search = new IceCreamFlavor();
	IceCreamFlavor* returned;

	cout<<"\nEnter the name of what you would like to search for: ";
	getline(cin, name);
	cout<<endl;

	search->setName(name);					//the name is set

	if(HST.getEntry(search, returned))			//pretend HashTable is like this
		cout<<endl<<*returned<<endl;
	else 
		cout << "Entry not in the Ice Cream Shoppe inventory." << endl << endl;

	delete search;

	return;
}
/*
ListHashedTable
calls the printTable in the HashedTable class to print the table order.
*/
void IceCreamMenu::ListHashedTable()
{
	HST.printTable();
	cout<<endl;
}

/*
List key sequence
Calls the inOrder function of the BST to print the keys in order, alphabetical order.
*/
void IceCreamMenu::ListKeySequence()
{
	BST.inOrder(display);
	cout<<endl;
}
/*
PrintIndentedTree
Calls the print indented tree function in the BST.
*/
void IceCreamMenu::PrintIndentedTree()
{
	BST.printIndented(displayForIndented);
	cout<<endl;
}
/*
Print HashStats
Calls the displayStats of the Hashtable
*/
void IceCreamMenu::PrintHashStats()
{
	HST.displayStats();
	cout<<endl;
}
/*
Quit
Quit allows the user to enter their file name that they want to save in.
If it does not exist, it is opened and the new data is saved in hash table order.
The data in the original IceCreamShop.txt is overwritten as well to be able to open the new shop data
after the user quits the program.
*/
void IceCreamMenu::Quit()	
{
	ofstream infile;
	ofstream originalFile;
	string fname;

	cout<<"Enter file name: ";
	cin >> fname;
	fname += ".txt";
	infile.open (fname);
	cin.sync();						//flushes input stream incase of spaces and such
	originalFile.open("IceCreamShop.txt");	//needs to automatically save on this too, according to the insturctions.
	

	for (int i = 0; i< HST.getSize(); i ++)
	{
		if(HST.getData(i)!= 0)
		{
			infile <<*HST.getData(i);
			if (fname != "IceCreamShop")
				originalFile <<*HST.getData(i);
		}
	}
	
	
	BST.inOrder(Delete);
	HST.DeallocateMemory();
	infile.close();
	originalFile.close();
}
/*
Compare
Asks to compare two keys. Then if the first key is not valid, it prompts again for a 
valid key. Then it checks the second key as well the same way. Once both keys are valid, 
they are printed to the screen. Then the user has the option to quit or add a third item 
to the comparison and also pick the location they want to see it in. Then, again the key
is checked to be valid, and again the flavors are printed with their information like the 
user wanted to see. Then, the user has the option to quit again or enter a fourth key. 
And again, the same thing happens with the fourth key as the third. After the fourth key 
is entered, the user can compare another data, at a location, but can only see four data 
values at a time.
*/
void IceCreamMenu::Compare()
{
	string IceCreamFlavor1, IceCreamFlavor2;
	IceCreamFlavor* Return;
	IceCreamFlavor* search = new IceCreamFlavor();
	List <IceCreamFlavor> list;
	int location;

	cout << "Please enter two keys seperated by a newline that you want to compare:" << endl;

	for (int i = 0; i < 2; i++)
	{
		getline(cin, IceCreamFlavor1);
		search->setName(IceCreamFlavor1);
		while (!HST.getEntry(search, Return))
		{
			cout << "The flavor does not exist please enter another one" << endl;
			getline(cin, IceCreamFlavor1);
			search->setName(IceCreamFlavor1);
		}
		list.insert(*Return, i+1);
	}
	
	cout<<endl;
	list.display();

	do 
	{
		cout << "Would you like to compare another flavor? If so, type in it's name and where" << endl<< 
		"you would like to see it separated by a newline. If not, type \"quit\" followed by\"0\"" << endl;
		getline (cin, IceCreamFlavor1);
		cin >> location;
		cin.sync();
		if (IceCreamFlavor1 != "quit")
		{
			search->setName(IceCreamFlavor1);
			while (!HST.getEntry(search, Return))
			{
				cout << "The entry was not a valid please enter another one" << endl;
				getline(cin, IceCreamFlavor1);
				cin.sync();
				search->setName(IceCreamFlavor1);
			}
			while (!list.insert(*Return, location))
			{
				cout <<"The location was not valid please enter another one" << endl;
				cin >> location;
				cin.sync();
			}
			if(list.size() > 4)
				list.remove(location+1);

			cout<<endl;
			list.display();
		}
	} while (IceCreamFlavor1 != "quit");
	
	delete search;
	list.clear();
	return;
}