// Binary Search Tree ADT
// Created by Frank M. Carrano and Tim Henry.
// Modified by: Sean Ashe

#ifndef _BINARY_SEARCH_TREE
#define _BINARY_SEARCH_TREE

#include "BinaryNode.h"
#include "BinaryTree.h"
#include <iostream>
#include <string>

using namespace std;

template<class ItemType>
class BinarySearchTree : public BinaryTree<ItemType>
{
private:
	// internal insert node: insert newNode in nodePtr subtree
<<<<<<< HEAD:Sean's Files/BinarySearchTree.h
	BinaryNode<ItemType>* _insert(BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
    
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(BinaryNode<ItemType>* nodePtr, const ItemType target, bool & success);
    
=======
	BinaryNode<ItemType>* _insert(bool visit(ItemType, ItemType), BinaryNode<ItemType>* nodePtr, BinaryNode<ItemType>* newNode);
   
	// internal remove node: locate and delete target node under nodePtr subtree
	BinaryNode<ItemType>* _remove(bool visit(ItemType, ItemType), BinaryNode<ItemType>* nodePtr, 
												const ItemType target, bool & success);
   
>>>>>>> origin/master:BinarySearchTree.h
	// delete target node from tree, called by internal remove node
	BinaryNode<ItemType>* deleteNode(BinaryNode<ItemType>* targetNodePtr);
    
	// remove the leftmost node in the left subtree of nodePtr
	BinaryNode<ItemType>* removeLeftmostNode(BinaryNode<ItemType>* nodePtr, ItemType & successor);
    
	// search for target node
<<<<<<< HEAD:Sean's Files/BinarySearchTree.h
	BinaryNode<ItemType>* findNode(BinaryNode<ItemType>* treePtr, const ItemType & target) const;
    
public:
=======
	BinaryNode<ItemType>* findNode(bool visit(ItemType, ItemType), bool visit1(ItemType, ItemType), 
									BinaryNode<ItemType>* treePtr, const ItemType & target) const;
   
public:  
>>>>>>> origin/master:BinarySearchTree.h
	// insert a node at the correct location
    bool insert(bool visit(ItemType, ItemType), bool visit1(ItemType, ItemType), const ItemType & newEntry);
	// remove a node if found
	bool remove(bool visit(ItemType, ItemType), const ItemType & anEntry);
	// find a target node
<<<<<<< HEAD:Sean's Files/BinarySearchTree.h
	bool getEntry(const ItemType & target, ItemType & returnedItem) const;
    
=======
	bool getEntry(bool visit(ItemType, ItemType), bool visit1(ItemType, ItemType), const ItemType & target, 
					ItemType & returnedItem) const;
 
>>>>>>> origin/master:BinarySearchTree.h
};


///////////////////////// public function definitions ///////////////////////////

template<class ItemType>
bool BinarySearchTree<ItemType>::insert(bool visit(ItemType, ItemType), bool visit1(ItemType, ItemType), const ItemType & newEntry)
{
	BinaryNode<ItemType>* newNodePtr;
	ItemType garbageData;
	
	if (getEntry(visit, visit1, newEntry, garbageData) == true)
		return false;
	newNodePtr = new BinaryNode<ItemType>(newEntry);
<<<<<<< HEAD:Sean's Files/BinarySearchTree.h
	rootPtr = _insert(rootPtr, newNodePtr);
=======
	rootPtr = _insert(visit, rootPtr, newNodePtr); 
>>>>>>> origin/master:BinarySearchTree.h
	count++;
	return true;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::remove(bool visit(ItemType, ItemType), const ItemType & target)
{
	bool isSuccessful = false;
	rootPtr = _remove(visit, rootPtr, target, isSuccessful);
	if (isSuccessful == true)
		count--;
	return isSuccessful;
}

template<class ItemType>
bool BinarySearchTree<ItemType>::getEntry(bool visit(ItemType, ItemType), bool visit1(ItemType, ItemType), 
										  const ItemType& anEntry, ItemType & returnedItem) const
{
	BinaryNode<ItemType>* nodePtr;
	nodePtr = findNode(visit, visit1, rootPtr, anEntry);
	if (nodePtr != 0)
	{
		returnedItem = nodePtr->getItem();
		return true;
	}
	
	return false;
}



//////////////////////////// private functions ////////////////////////////////////////////

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_insert(bool visit(ItemType, ItemType), BinaryNode<ItemType>* nodePtr,
                                                          BinaryNode<ItemType>* newNodePtr)
{
	if (nodePtr == 0)
		return newNodePtr;
	else
	{
<<<<<<< HEAD:Sean's Files/BinarySearchTree.h
		if (newNodePtr->getItem()->getName() < nodePtr->getItem()->getName())
			nodePtr->setLeftPtr(_insert(nodePtr->getLeftPtr(), newNodePtr));
=======
		//if (newNodePtr->getItem()/*->getName()*/ < nodePtr->getItem()/*->getName()*/)
		if (visit(newNodePtr->getItem(), nodePtr->getItem()))
			nodePtr->setLeftPtr(_insert(visit, nodePtr->getLeftPtr(), newNodePtr));
>>>>>>> origin/master:BinarySearchTree.h
		else
			nodePtr->setRightPtr(_insert(visit, nodePtr->getRightPtr(), newNodePtr));
		
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::_remove(bool visit(ItemType, ItemType), BinaryNode<ItemType>* nodePtr,
                                                          const ItemType target, bool & success)

{
	if (nodePtr == 0)
	{
		success = false;
		return 0;
	}
<<<<<<< HEAD:Sean's Files/BinarySearchTree.h
	if (nodePtr->getItem()->getName() > target->getName())
		nodePtr->setLeftPtr(_remove(nodePtr->getLeftPtr(), target, success));
	else if (nodePtr->getItem()->getName() < target->getName())
		nodePtr->setRightPtr(_remove(nodePtr->getRightPtr(), target, success));
	else
=======
	//if (nodePtr->getItem()/*->getName()*/ > target/*->getName()*/)
	if (visit(target, nodePtr->getItem()))
		nodePtr->setLeftPtr(_remove(visit, nodePtr->getLeftPtr(), target, success));
	//else if (nodePtr->getItem()/*->getName()*/ < target/*->getName()*/)	 
	else if (visit(nodePtr->getItem(), target))
		nodePtr->setRightPtr(_remove(visit, nodePtr->getRightPtr(), target, success));
	else		
>>>>>>> origin/master:BinarySearchTree.h
	{
		nodePtr = deleteNode(nodePtr);
		success = true;
	}
	return nodePtr;
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::deleteNode(BinaryNode<ItemType>* nodePtr)
{
	if (nodePtr->isLeaf())
	{
		delete nodePtr;
		nodePtr = 0;
		return nodePtr;
	}
	else if (nodePtr->getLeftPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getRightPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else if (nodePtr->getRightPtr() == 0)
	{
		BinaryNode<ItemType>* nodeToConnectPtr = nodePtr->getLeftPtr();
		delete nodePtr;
		nodePtr = 0;
		return nodeToConnectPtr;
	}
	else
	{
		ItemType newNodeValue;
		nodePtr->setRightPtr(removeLeftmostNode(nodePtr->getRightPtr(), newNodeValue));
		nodePtr->setItem(newNodeValue);
		return nodePtr;
	}
}

template<class ItemType>
BinaryNode<ItemType>* BinarySearchTree<ItemType>::removeLeftmostNode(BinaryNode<ItemType>* nodePtr,
                                                                     ItemType & successor)
{
	if (nodePtr->getLeftPtr() == 0)
	{
		successor = nodePtr->getItem();
		return deleteNode(nodePtr);
	}
	else
	{
		nodePtr->setLeftPtr(removeLeftmostNode(nodePtr->getLeftPtr(), successor));
		return nodePtr;
	}
}


template<class ItemType>
<<<<<<< HEAD:Sean's Files/BinarySearchTree.h
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(BinaryNode<ItemType>* nodePtr,
                                                           const ItemType & target) const
{
	if (nodePtr != 0)
	{
		if (nodePtr->getItem()->getName() == target->getName())
		{
			return nodePtr;
		}
		if (nodePtr->getItem()->getName() < target->getName())
			findNode(nodePtr->getRightPtr(), target);
=======
BinaryNode<ItemType>* BinarySearchTree<ItemType>::findNode(bool visit(ItemType, ItemType), bool visit1(ItemType, ItemType), 
														   BinaryNode<ItemType>* nodePtr, const ItemType & target) const 
{
	if (nodePtr != 0)
	{
		//if (nodePtr->getItem()/*->getName()*/ == target/*->getName()*/)
		if (visit1(nodePtr->getItem(), target))
		{
			return nodePtr;
		}
		//if (nodePtr->getItem()/*->getName()*/ < target/*->getName()*/)
		if (visit(nodePtr->getItem(), target))
			findNode(visit, visit1, nodePtr->getRightPtr(), target);
>>>>>>> origin/master:BinarySearchTree.h
		else
			findNode(visit, visit1, nodePtr->getLeftPtr(), target);
	}
	else
		return 0;
<<<<<<< HEAD:Sean's Files/BinarySearchTree.h
    
}
=======

}  
>>>>>>> origin/master:BinarySearchTree.h

#endif

