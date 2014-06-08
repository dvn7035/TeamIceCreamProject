#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "IceCreamFlavor.h"
#include "IceCreamMenu.h"
//#include "HashedTable.h"
//#include "BinarySearchTree.h"




IceCreamMenu::IceCreamMenu()
{
	string flavor = " ";			//stores flavor
	bool isNut = false;		//stores if there is a nut
	int calorie;			//stores calories
	double price;			//stores price
	string cmpnut = "nut";	//compares the word nut to what is is in the string nut to know if there are nuts or no nuts in the ice cream
	string nut;			//read in nut
	string comma;			//stores a comma read in
	bool added;

	int count = 0;	//store count for hashtable size
	//int index;

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
			//added = BST.insert(data);				//put in BST
			//if (added == true)		
				//call to stick in hash table
			HST.add(data);		//i dont get how this works. since the insert in the hashed table class 
															//is responsible for calling the hashing function

		}
		
	}
	cout<< "Hello User."<<endl;
	//Close file
	infile.close();
}
void IceCreamMenu::AddFlavor()
{
	string name;
	double price;
	int calories;
	bool nuts;
	int pick;
	IceCreamFlavor* flavor;
	IceCreamFlavor* returned;
	bool insertBST;
	bool insertTable;
	//bool found;

	cout<<"What flavor would you like to add?\nEnter the name of the flavor: ";
	getline (cin, name);
	flavor->setName(name);
	cout<<endl;
	//if (BST.getEntry(flavor, returned))	//um, i think in the hashed table, we don't have a search function without
									//using the insert, so i used the tree.
	//{
	//	cout<<"Entry cannot be added because of duplicate key.\n"<<endl;
	//	return;
	//}

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

	cout<<"How much does this flacor cost>\nEnter cost without dollar sign: ";
	cin>>price;
	flavor->setPrice(price);

	cout<<endl;
	
	//actual insert:
	//insertBST=BST.insert(flavor);				//there are no set functions, so is this how we do it?
			
	//call to stick in hash table
	//HashedTable[index]->insert(IceCreamFlavor(flavor));		//how does this work?
	//HashedTable.insert(flavor);							//if class? and insert would call the hashing function?how would we check it inserted?
	
	//if (insertBST == true && insertTable == true)
	//	cout<<"\ninserted.\n";
//	else
//		cout<<"\ninsert failed.\n";
	
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
	
	//if (BST.getEntry(flavor, returned))	//um, i think in the hashed table, we don't have a search function without
									//using the insert, so i used the tree.
	//{
	//	cout<<"Entry cannot be deleted because it doesn't exist.\n"<<endl;
	//	return;
	//}

	//removedBST = BST.remove(flavor);//removal function of pointer of table
	//removedTable = ////removal function of pointer of Table
	//delete data
//	if (removedBST == true && removedTable == true)
		cout<<"\nremoval sucessful."<<endl;
//	else
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

	//search hashtable (?) how

	return;
}

void IceCreamMenu::quit()	//need to add based on instruction
{
	ifstream infile;
	string fname;

	cout<<"Enter file name: ";
	cin >> fname;		
	cin.sync();		//flushes input stream incase of spaces and such
	infile.open(fname);
	//infile <<  	// write to infile to save data. copy from?
	infile.close();
}

void IceCreamMenu::PrintHashStats()
{
	HST.displayStats();
}