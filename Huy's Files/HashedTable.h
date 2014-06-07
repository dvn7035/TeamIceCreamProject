// Hashed Table to store the dictionary
// Huy Nguyen
// 06/03/2014
#ifndef _HASHED_TABLE
#define _HASHED_TABLE

#include <string>
#include "IceCreamFlavor.h"



using namespace std;

class HashedTable 
{
private:
	int number;
	int size;
	IceCreamFlavor ** data;
	int* probe;
	int HashingFunction(string);
	int ColRes(int,int);
public:
	HashedTable();
	HashedTable(int);
	bool add(IceCreamFlavor * address);
	void displayStats();
	bool findRecord(int index, string word);
};


#endif