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
	cout << *anItem << endl;
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
		infile.open (fname.c_str());
	}

	while (getline(infile, punct, '\n'))		
		count++;							
	HST.AllocateMemory(count);				


	infile.clear();							//reset point to beginning of file
	infile.seekg(0, infile.beg);


	while (getline(infile, flavor, ','))
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

	infile.close();				//Close file
}

void IceCreamMenu::AddFlavor()
{
	string name;
	double price;
	int calories;
	int pick;
	IceCreamFlavor* flavor = new IceCreamFlavor();
	IceCreamFlavor* returned = new IceCreamFlavor();
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
		
		delete returned;
	
	}
	return;
}

void IceCreamMenu::DeleteFlavor()
{
	string name;
	IceCreamFlavor* flavor = new IceCreamFlavor();
	IceCreamFlavor* returned = new IceCreamFlavor();

	cout<<"What flavor would you like to delete?\nEnter the name of the flavor: ";
	getline (cin, name);
	flavor->setName(name);
	cout<<endl;

	if (HST.remove(flavor, returned) && (BST.remove(compareL, flavor)))	//bst
	{
		cout<<"entry deleted\n\n";								//returned has the adress of storage
	}
	else 
		cout<<"Entry cannot be found.\n"<<endl;

	delete flavor;
	delete returned;
	return;
}

void IceCreamMenu::FindAndDisplayFlavor()
{
	string name;
	IceCreamFlavor* search = new IceCreamFlavor();
	//IceCreamFlavor* returned = new IceCreamFlavor();

	IceCreamFlavor* returned;

	cout<<"\nEnter the name of what you would like to search for: ";
	getline(cin, name);
	cout<<endl;

	search->setName(name);					//the name is set

	if(HST.getEntry(search, returned))			//pretend HashTable is like this
		cout<<endl<<*returned<<endl;
	else 
		cout << "Entry not found" << endl << endl;

	delete search;

	return;
}

void IceCreamMenu::ListHashedTable()
{
	HST.printTable();
	cout<<endl;
}

void IceCreamMenu::ListKeySequence()
{
	BST.inOrder(display);
	cout<<endl;
}

void IceCreamMenu::PrintIndentedTree()
{
	BST.printIndented(displayForIndented);
	cout<<endl;
}

void IceCreamMenu::PrintHashStats()
{
	HST.displayStats();
	cout<<endl;
}

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
			//if (fname != "IceCreamShop")
				//originalFile <<*HST.getData(i);
		}
	}
	
	
	BST.inOrder(Delete);
	
	infile.close();
	originalFile.close();
}

void IceCreamMenu::Compare()
{
	//string IceCreamFlavor1, IceCreamFlavor2;
	//IceCreamFlavor* Return = new IceCreamFlavor();
	//IceCreamFlavor* search = new IceCreamFlavor();
	//List <IceCreamFlavor> list;
	//int location;

	//cout << "Please enter two keys seperated by a newline that you want to compare:" << endl;
	//getline(cin, IceCreamFlavor1);
	//getline(cin, IceCreamFlavor2);
	////cin >>  IceCreamFlavor1 >> IceCreamFlavor2;

	//search->setName(IceCreamFlavor1);
	//while (!HST.getEntry(search, Return))
	//{
	//	cout << "The first parameter was incorrect please enter another one" << endl;
	//	cin >> IceCreamFlavor1;
	//	search->setName(IceCreamFlavor1);
	//}
	//list.insert(*Return, 1);
	//
	//search->setName(IceCreamFlavor2);
	//while (!HST.getEntry(search, Return))
	//{
	//	cout << "The second parameter was incorrect please enter another one" << endl;
	//	cin >> IceCreamFlavor2;
	//	search->setName(IceCreamFlavor2);
	//}
	//list.insert (*Return, 2);
	//list.display();

	//do 
	//{
	//	cout<<"Would you like to compare another flavor? If so, please enter another one followed by the position " << endl
	//	    <<"where you would like to see it. If not, type \"quit\"";
	//	cin >> IceCreamFlavor1 >> location;
	//	if (IceCreamFlavor1 != "quit")
	//	{
	//		if (list.size() < 4)
	//			list.insert(
	//	}
	//	

	//	
	//	else if (IceCreamFlavor1 != "quit" && list.size() == 4)
	//	{
	//		//prompt a position a position to overwrite
	//	}

	//}while (IceCreamFlavor1 != "quit")

	//for(int i = 0; i<2; i++)
	//{
	//	cout<<"Enter another key you want to compare and a location seperated by a newline: \n";
	//	getline(cin, IceCreamFlavor3);
	//	cin >> location;
	//	search->setName(IceCreamFlavor3);
	//	if(HST.getEntry(search, Return))
	//		list.insert (*Return, location);
	//	cin.sync();
	//	list.display();
	//}
	//delete Return;
	//delete search;
	//list.clear();
	//return;
}