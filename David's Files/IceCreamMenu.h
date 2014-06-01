#ifndef ICECREAMMENU_H_INCLUDED
#define ICECREAMMENU_H_INCLUDED

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
