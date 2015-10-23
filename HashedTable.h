// Hashed Table to store the menu
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
	int HashingFunction(string);
	int ColRes(int,int);
	bool search(int & index, string food);
	int maxProbe;
public:
	HashedTable() {};
	void AllocateMemory(int);
	bool add(IceCreamFlavor * address);
	void displayStats();
	bool getEntry(const IceCreamFlavor* , IceCreamFlavor* &);
	bool remove (IceCreamFlavor *, IceCreamFlavor * &);
	void printTable();
	int getSize (){return size;}
	void DeallocateMemory();
	IceCreamFlavor * getData (int i){return data[i];}
};


#endif