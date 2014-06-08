#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "IceCreamFlavor.h"
#include "IceCreamMenu.h"
#include "HashedTable.h"
#include "BinarySearchTree.h"

// display function to pass to BST traverse functions
void display (IceCreamFlavor* & anItem) 
{
	cout << *anItem;
	return;
} 

IceCreamMenu::IceCreamMenu()
{
	string flavor;			//stores flavor
	bool isNut = false;		//stores if there is a nut
	int calorie;			//stores calories
	double price;			//stores price
	string cmpnut = "nut";	//compares the word nut to what is is in the string nut to know if there are nuts or no nuts in the ice cream
	string nut;			//read in nut
	string comma;			//stores a comma read in
	bool added;

	int count = 0;			//store count for hashtable size

	ifstream infile;
	string fname;


	//instance of the icecreamflavor class. is this necessary?
	//initialize the hash arr elements. is this necessary? no right? since the hash table isnt made yet?

	bool eofReached = false;

	infile.open("IceCreamShop.txt");
	while (!infile)  // check for file open success or prompt for filename
	{
		cout << "Error opening "<<fname<< "file."<<endl<<"Enter filename: ";
		cin >> fname;
		infile.open (fname.c_str());
	}

	if (!infile.eof())	//check empty file
		eofReached = false;
		
		
	while (!eofReached)
	{
		getline(infile, flavor, ',');		//reads in flavor, which is seperated by a comma
		getline(infile, nut, ',');		//reads in nut which is seperated by a comma

		//check if eof
		if (infile.eof())
			eofReached = true;		//and it won't run again and copy last line of int and double again
		
		if (!eofReached)
		{
			infile>>calorie>>comma>>price;	//reads this extra time
			count++;	//increment count for hash table
			if (nut==cmpnut)
			{
				isNut=true;
				cout<<flavor<<", "<<"nut"<<", "<<calorie<<", $"<<setfill ('0')<<setprecision(2)<<price<<endl;	//why doesnt this print the last 0?
			}
			else
			{
				isNut=false;
				cout<<flavor<<", "<<"no nut"<<", "<<calorie<<", $"<<setfill ('0')<<setprecision(2)<<price<<endl;
			}

			//store as a MenuItem

			//call to put on tree
			IceCreamFlavor* data = new IceCreamFlavor(flavor, price, calorie, isNut);
			added = BST.insert(data);	//put in BST. not put in hashedtable yet because do not know how big it is
			if (added == true)
				count ++;				//hashedtable count.
									//didnt check for repeats because there aren't repeats in the textfile.
									//there never will be, not even when the program restarts again
		}		
	}

	//create hashedTable, and initialize it


	cout<< "Hello User."<<endl;
	//Close file
	infile.close();
}
void IceCreamMenu::AddFlavor()
{
	string name;
	double price;
	int calories;
//	bool nuts;
	int pick;
	IceCreamFlavor* flavor;
	IceCreamFlavor* returned;
	bool insertBST;
	bool insertTable;
//	int index;
	//bool found;

	cout<<"What flavor would you like to add?\nEnter the name of the flavor: ";
	getline (cin, name);
	flavor->setName(name);
	cout<<endl;
	

	//if (HST.findRecord(			//requires this function to get index ... why? and in that case, this canot acess the hashing function anyways 
	if (BST.getEntry(flavor, returned))	//temporarily use tree until hash table search is fixed.
									
	{
		cout<<"Entry cannot be added because of duplicate key.\n"<<endl;
		return;
	}

	cout<<endl;
	
	do
	{
		cout<<"Are there nuts in "<<name<< " ?\nEnter 1 for yes and 2 for no; you will be prompted again if you submit an invalid answer: ";
		cin>>pick;
		cin.sync();
	}while ((pick !='1') || (pick !='2'));
	
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

	cout<<"How much does this flavor cost>\nEnter cost without dollar sign: ";
	cin>>price;
	flavor->setPrice(price);

	cout<<endl;
	
	//actual insert:				
	insertTable = HST.add(flavor);
	if (insertTable == true)
	{
		insertBST = BST.insert(flavor);
		if(insertBST == false)
		{
			cout<<"\ninsert failed.\n";
			//HST.					//remove from hashed table. Hashed Table doesn't have a remove data function
		}
	}
	else
		cout<<"\ninsert failed.\n";
		
	return;
}

void IceCreamMenu::DeleteFlavor()
{
	string name;
	IceCreamFlavor* flavor;
	IceCreamFlavor* returned;
	bool removedBST = false;
	bool removedTable = false;


	cout<<"What flavor would you like to delete?\nEnter the name of the flavor: ";
	getline (cin, name);
	flavor->setName(name);
	cout<<endl;
	
	if (BST.getEntry(flavor, returned))	//again same problem, this should be the hashed table's job
	{
		cout<<"Entry cannot be deleted because it doesn't exist.\n"<<endl;
		return;
	}

	removedBST = BST.remove(flavor);//removal function of pointer of table
	//removedTable = HST.
	//delete data
	if (removedBST == true && removedTable == true)
	{
		delete returned;		//return has the adress of storage
		cout<<"\nremoval sucessful."<<endl;
	}
	else
		cout<<"\nRemoval not successful."<<endl;

	return;
}

void IceCreamMenu::FindAndDisplayFlavor()
{
	string name;
	IceCreamFlavor* search;
	bool found;			//need to know if found


	cout<<"\nEnter the name of what you would like to search for: ";
	getline(cin, name);
	cout<<endl;

	search->setName(name);

	//again same problem with hashed table

	//search hashtable (?) how

	return;
}

void IceCreamMenu::ListHashedTable()
{
	
}

void IceCreamMenu::ListKeySequence()
{
	BST.inOrder(display);
}

void IceCreamMenu::PrintIndentedTree()
{
	BST.printIndented();
}

void IceCreamMenu::PrintHashStats()
{
	HST.displayStats();
}

void IceCreamMenu::quit()	
{
	ifstream infile;
	ifstream originalFile;
	string fname;

	cout<<"Enter file name: ";
	cin >> fname;		
	cin.sync();						//flushes input stream incase of spaces and such
	infile.open(fname);
	originalFile.open("IceCreamShop.txt");	//needs to automatically save on this too, according to the insturctions
	
	//infile <<  						// write to infile to save data. copy from hashtable..how?
	
	infile.close();
	originalFile.close();
}