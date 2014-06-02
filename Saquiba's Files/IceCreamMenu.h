#ifndef ICECREAMMENU_H_INCLUDED
#define ICECREAMMENU_H_INCLUDED

#include "IceCreamFlavor.h"
#include "HashedTable.h"
#include "BinarySearchTree.h"

const int SIZE = 100;

class IceCreamMenu
{
private:
    BinarySearchTree <IceCreamFlavor*> BST;
    IceCreamFlavor* HashedTable [SIZE];
    //SortedList<IceCreamFlavor*> HashedTable;
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
