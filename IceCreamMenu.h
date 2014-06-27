#ifndef ICECREAMMENU_H_INCLUDED
#define ICECREAMMENU_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
 
#include "HashedTable.h"
#include "BinarySearchTree.h"

class IceCreamMenu
{
private:
    BinarySearchTree<IceCreamFlavor*> BST;
    HashedTable HST;
public:
    IceCreamMenu();
    void AddFlavor();
    void DeleteFlavor();
    void FindAndDisplayFlavor();
    void ListHashedTable();
    void ListKeySequence();
    void PrintIndentedTree();
    void PrintHashStats();
	void Compare();
	void Quit();
};

#endif // ICECREAMMENU_H_INCLUDED