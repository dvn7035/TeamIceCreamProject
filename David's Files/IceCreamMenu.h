#ifndef ICECREAMMENU_H_INCLUDED
#define ICECREAMMENU_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>

#include "IceCreamMenu.h"
#include "HashedTable.h"
#include "BinarySearchTree.h"

class IceCreamMenu
{
private:
    BinarySearchTree<IceCreamFlavor*> BST;
    IceCreamFlavor* HashedTable;
public:
    IceCreamMenu();
    void AddFlavor();
    void DeleteFlavor();
    void FindAndDisplayFlavor();
    void ListHashedTable();
    void ListKeySequence();
    void PrintIndentedTree();
    void PrintHashStats();
};

#endif // ICECREAMMENU_H_INCLUDED
