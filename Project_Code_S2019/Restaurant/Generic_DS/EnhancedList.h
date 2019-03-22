#ifndef __ENHANCEDLIST_H_
#define __ENHANCEDLIST_H_
#include "Node.h"


//ostream& operator <<(ostream& o, Order& ord);	// for testing



/*
	This data structure contains the functions of a List as well as the functions of a queue: [but it cannot be considered neither of both]
	1)insert
	4)remove
	2)enqueue
	3)dequeue
	
*/
template<typename T>
class EnhancedList {
	Node<T>* frontPtr;
	Node<T>* backPtr;


public:
	EnhancedList();

	bool insert(const T&item);					// inserts items in certain positions depending on their priority [the operator '>' should be overloaded in each class that calls this function]
	bool remove(const int id, T& item);			//removes items by their IDs
	bool enqueue(const T& item);				//puts an item in the back of the list [same as queue]
	bool dequeue(T& item);						//removes an item from the front of the list [same as queue]
	bool isEmpty() const;						//checks if the list is empty
	bool getFront(T& item) const;				//gets a copy of the item pointed to by the frontPtr

	//void display() const {						//for testing only
	//	Node<T>* curr = frontPtr;
	//	while (curr!= NULL)
	//	{
	//		cout << curr->getItem();
	//		curr = curr->getNext();
	//	}
	}
	~EnhancedList();
};



template<typename T>
EnhancedList<T>::EnhancedList() {
	frontPtr = NULL;							//initializing an empty list --> frontPtr and backPtr point to NULL
	backPtr = NULL;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
bool EnhancedList<T>::insert(const T&item) {
	Node<T>* newNode = new Node<T>(item);
	if (newNode == NULL)
	{
		return false;
	}
	if (isEmpty())						// if the list is empty
	{
		frontPtr = newNode;
		backPtr = newNode;
		return true;
	}
	
	if (item > frontPtr->getItem())		// if the given item's priority is greater than the first item's priority
	{									//...It also handles the case in which the list contains a single element
		newNode->setNext(frontPtr);
		frontPtr = newNode;
		return true;
	}
	Node<T>* prev = frontPtr;
	Node<T>* curr = frontPtr->getNext();
	while (curr != NULL)
	{
		if (item > curr->getItem())		// if the given item's priority is greater than the current item's priority
		{
			prev->setNext(newNode);
			newNode->setNext(curr);
			return true;
		}
		prev = curr;
		curr = curr->getNext();
	}
	backPtr->setNext(newNode);			// if the given item has the lower priority from the whole list => inserted at the end of the list
	backPtr = newNode;					//...It also handles the case in which the list contains a single element
	
	return true;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
bool EnhancedList<T>::remove(int id, T& item) {
	if (isEmpty())
	{
		return false;
	}
	if (frontPtr == backPtr)				// if there is only one element in the list
	{
		if (frontPtr->getItem() == id)		// if the the id of the element = the given id (opertor == should be overloaded)
		{
			item = frontPtr->getItem();
			delete frontPtr;
			frontPtr = NULL;
			backPtr = NULL;
			return true;
		}
		else {
			return false;
		}
	}
	if (frontPtr->getItem() == id)			// if the id was = the id of the FIRST element
	{
		item = frontPtr->getItem();
		Node<T>* temp = frontPtr;
		frontPtr = frontPtr->getNext();
		delete temp;
		return true;
	}


	Node<T>* prev = frontPtr;
	Node<T>* curr = frontPtr->getNext();
	while (curr != NULL)
	{
		if (curr->getItem() == id)
		{
			if (curr == backPtr)
			{
				backPtr = prev;
			}
			prev->setNext(curr->getNext());

			item = curr->getItem();
			delete curr;
			return true;
		}
		prev = curr;
		curr = curr->getNext();
	}
	return false;					// the id was not found

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
bool EnhancedList<T>::enqueue(const T& item) {
	Node<T>* newNode = new Node<T>(item);
	if (newNode == NULL)
	{
		return false;
	}
	if (isEmpty())					// if the list is empty
	{
		frontPtr = newNode;
		backPtr = newNode;
		return true;
	}
	backPtr->setNext(newNode);
	backPtr = newNode;
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
bool EnhancedList<T>::dequeue(T& item) {
	if (isEmpty())
	{
		return false;				 // the list is empty
	}

	item = frontPtr->getItem();		 // returns the value of the item

	if (backPtr == frontPtr)		 // the list contains only one element
	{
		delete frontPtr;
		frontPtr = NULL;
		backPtr = NULL;
		return true;
	}

	Node<T>* tempNode = frontPtr;
	frontPtr = frontPtr->getNext();
	delete tempNode;
	return true;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
bool EnhancedList<T>::isEmpty() const {
	if (backPtr == NULL || frontPtr == NULL)
	{
		return true;
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
bool EnhancedList<T>::getFront(T& item) const {
	if (isEmpty())
	{
		return false;
	}
	item = frontPtr->getItem();
	return true;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
EnhancedList<T>::~EnhancedList() {
	Node<T>* tempPtr = frontPtr;
	frontPtr = frontPtr->getNext();
	while (frontPtr->getNext() != NULL) {
		delete tempPtr;
		tempPtr = frontPtr;
		frontPtr = frontPtr->getNext();
	}
	delete tempPtr;
	frontPtr = NULL;
	backPtr = NULL;
}

#endif // !__ENHANCEDLIST_H_