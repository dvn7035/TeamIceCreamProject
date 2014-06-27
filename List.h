// Linked List ADT 
// This list allows the user to insert and remove data at a specified position
// By CNguyen

//do data since already inherit frlom linked list class
//all needs is item count and ptr

#ifndef LIST
#define LIST

#include "LinkedList.h"
#include "Node.h"

template<class ItemType>
class List : public LinkedList<ItemType>  // derived from abstract LinkedList class
{
private:
	// Finds node at a specified position
	//supposed to return position of the node before where we should be
	Node<ItemType>* getNodeAt(int position) const;

public:
	// Adds node at a specified position
	bool insert(const ItemType& newEntry, int newPosition = 1);
	// Removes node at a specified position
	bool remove(int position);
	// Passes back node at a specified position
	bool getEntry(int position, ItemType & anEntry) const;
}; 


template<class ItemType>
bool List<ItemType>::insert(const ItemType& newEntry, int newPosition)	//pretend inserting myList.Insert(5,1), then (10,1), now pretend myList.insert (3,2)
{
	// check valid position
	if (newPosition < 1 || newPosition > itemCount + 1)					//it is true, so moves on			
	   return false;

	// create new node for newEntry	
	Node<ItemType>* newNodePtr = new Node<ItemType>(newEntry);			//newNodePtr = 5, has a 5. list looks like newNodePtr -> 5 -> 0	//insert 10, so now newptr -> 10 -> NULL. newNode Ptr -> 3
	if (newPosition == 1)   // insert new node at beginning				//newPosition does = 1
	{
		newNodePtr->setNext(headPtr);									//head is now set to the next node. head ptr is at 5
		headPtr = newNodePtr;											//head is now 5, head is now 10. headptr -> 10 -> 5 -> NULL
	}
	else  // insert new node in middle or end of list
	{
		Node<ItemType>* prevPtr = getNodeAt(newPosition - 1);	// go to position			//for (3,2) //after//currptr that was returned is now the prevptr. so prev ptr = 10
		newNodePtr->setNext(prevPtr->getNext());				//get next gets 5
		prevPtr->setNext(newNodePtr);							// now 10->3->5
	}
	itemCount++;														//item count is now 1 (after adding 5)
	return true;
}  


template<class ItemType>					//we have head -> 10 -> 3 -> 5 .... pretend myList.remove(2);
bool List<ItemType>::remove(int position)
{
	// check for valid position
	if (position < 1 || position > itemCount)	//false
	   return false;

	Node<ItemType>* deletePtr = 0;
	if (position == 1)   // remove first node 
	{
		deletePtr = headPtr; 
		headPtr = headPtr->getNext();
	}
	else   // remove from middle or end of list
	{
        Node<ItemType>* prevPtr = getNodeAt(position - 1); // get to position		//points to 10
		deletePtr = prevPtr->getNext();		// remove from list						//delete ptr at 3
		prevPtr->setNext(deletePtr->getNext());										//10 points to 5
	} 
	delete deletePtr;			//deletes 3
	itemCount--;				//decrement count
	return true;
}  

template<class ItemType>
bool List<ItemType>::getEntry(int position, ItemType & anEntry) const
{
   if (position < 1 || position > itemCount)
	   return false;

	Node<ItemType>* copyPtr = getNodeAt(position); // get to position
	anEntry = copyPtr->getItem();
	return true;
}  


template<class ItemType>
Node<ItemType>* List<ItemType>::getNodeAt(int position) const	//supposed to return the node before where we should be
{
	Node<ItemType>* curPtr = headPtr;		//headPtr is now 10... 2 pointers are pointing at the same thing
	for (int i = 1; i < position; i++)		
		curPtr = curPtr->getNext();			//this line doesnt run when want to insert 3 at 2nd position
											//list looks like head -> 10 -> 5 -> NULL, where curr ptr is 5
	return curPtr;	//returning pointer to 5
} 

#endif 
