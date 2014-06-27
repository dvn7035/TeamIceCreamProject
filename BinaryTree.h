// Binary tree abstract base class
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Sean Ashe
 
#ifndef _BINARY_TREE
#define _BINARY_TREE

#include "BinaryNode.h"
#include <iostream>
#include <iomanip>

template<class ItemType>
class BinaryTree
{
protected:
	BinaryNode<ItemType>* rootPtr;		// ptr to root node
	int count;							// number of nodes in tree

public:
	// "admin" functions
 	BinaryTree()						{rootPtr = 0; count = 0;}
	BinaryTree(const BinaryTree<ItemType> & tree)	
	{
		rootPtr = copyTree(tree.rootPtr);
		count = tree.count;
	}
	
	virtual ~BinaryTree()				{destroyTree(rootPtr); rootPtr = 0; count = 0; }		
	BinaryTree & operator=(const BinaryTree & sourceTree);
   
	// common functions for all binary trees
 	bool isEmpty() const				{return count == 0;}
	int size() const					{return count;}
	void clear()						{destroyTree(rootPtr); rootPtr = 0; count = 0;}
	void preOrder(void visit(ItemType &)) const		{_preorder(visit, rootPtr);}
	void inOrder(void visit(ItemType &)) const		{_inorder(visit, rootPtr);}
	void postOrder(void visit(ItemType &)) const	{_postorder(visit, rootPtr);}
	void reverseOrder(void visit(ItemType &)) const		{_reverseorder(visit, rootPtr);}

	void printIndented(void visit(ItemType)) const						{_printIndented(visit, rootPtr);}

	// abstract functions to be implemented by derived class
	virtual bool insert(bool visit(ItemType, ItemType), bool visit1(ItemType, ItemType), const ItemType & newData) = 0; 
	virtual bool remove(bool visit(ItemType, ItemType), const ItemType & data) = 0; 
	virtual bool getEntry(bool visit(ItemType, ItemType), bool visit1(ItemType, ItemType), const ItemType & anEntry, ItemType & returnedItem) const = 0;

private:   
	// delete all nodes from the tree
	void destroyTree(BinaryNode<ItemType>* nodePtr);

	// copy from the tree rooted at nodePtr and returns a pointer to the copy
	BinaryNode<ItemType>* copyTree(const BinaryNode<ItemType>* nodePtr);

	// internal traverse
	void _preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	void _postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;
	
	// traverse in reverse order
	void _reverseorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const;

	void _printIndented(void visit(ItemType), BinaryNode<ItemType>* nodePtr, int indent = 0) const;
   
}; 

//////////////////////////////////////////////////////////////////////////

template<class ItemType>
void BinaryTree<ItemType>::_printIndented(void visit(ItemType), BinaryNode<ItemType>* nodePtr, int indent = 0) const
{
	if (nodePtr != 0)
	{
		_printIndented(visit, nodePtr->getRightPtr(), indent + 7);
		cout << setw(indent) << " " ;
		visit(nodePtr->getItem());
		_printIndented(visit, nodePtr->getLeftPtr(), indent + 7);
	}
}


template<class ItemType>
BinaryNode<ItemType>* BinaryTree<ItemType>::copyTree(const BinaryNode<ItemType>* nodePtr) 
{
	BinaryNode<ItemType>* newNodePtr = 0;

	if (nodePtr != 0)
	{
		newNodePtr = new BinaryNode<ItemType>(nodePtr->getItem());
		newNodePtr->setLeftPtr(copyTree(nodePtr->getLeftPtr()));
		newNodePtr->setRightPtr(copyTree(nodePtr->getRightPtr()));
	}
	else
		return 0;
	
	return newNodePtr;
}  

template<class ItemType>
void BinaryTree<ItemType>::destroyTree(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr != 0)
	{
		destroyTree(nodePtr->getLeftPtr());
		destroyTree(nodePtr->getRightPtr());
		delete nodePtr;
		nodePtr = 0;
		count = 0;
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_preorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		ItemType item = nodePtr->getItem();
		visit(item);
		_preorder(visit, nodePtr->getLeftPtr());
		_preorder(visit, nodePtr->getRightPtr());
	} 
}  

template<class ItemType>
void BinaryTree<ItemType>::_inorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_inorder(visit, nodePtr->getLeftPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
		_inorder(visit, nodePtr->getRightPtr());
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_postorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_postorder(visit, nodePtr->getLeftPtr());
		_postorder(visit, nodePtr->getRightPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
	}
}  

template<class ItemType>
void BinaryTree<ItemType>::_reverseorder(void visit(ItemType &), BinaryNode<ItemType>* nodePtr) const
{
	if (nodePtr != 0)
	{
		_reverseorder(visit, nodePtr->getRightPtr());
		ItemType item = nodePtr->getItem();
		visit(item);
		_reverseorder(visit, nodePtr->getLeftPtr());
	}
}  


template<class ItemType>
BinaryTree<ItemType> & BinaryTree<ItemType>::operator=(const BinaryTree<ItemType> & sourceTree)
{
	if (this != &sourceTree)
	{
		this->clear();
		rootPtr = this->copyTree(sourceTree.rootPtr);
		count = sourceTree.count;
	}
	return *this;
}  


#endif

