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
	EnhancedList(const EnhancedList<T>&);			//copy constructor

	bool insert(const T&item);					// inserts items in certain positions depending on their priority [the operator '>' should be overloaded in each class that calls this function]
	bool remove(const int id, T& item);			//removes items by their IDs
	bool enqueue(const T& item);				//puts an item in the back of the list [same as queue]
	bool dequeue(T& item);						//removes an item from the front of the list [same as queue]
	bool isEmpty() const;						//checks if the list is empty
	bool peekFront(T& item) const;				//gets a copy of the item pointed to by the frontPtr
	

	//void display() const {					//for testing only
	//	Node<T>* curr = frontPtr;
	//	while (curr!= NULL)
	//	{
	//		cout << curr->getItem();
	//		curr = curr->getNext();
	//	}
	//}

	EnhancedList<T>& operator=(const EnhancedList<T>&);	//assignment operator
	~EnhancedList();								//destructor
};



template<typename T>
EnhancedList<T>::EnhancedList() {
	frontPtr = NULL;											//initializing an empty list --> frontPtr and backPtr point to NULL
	backPtr = NULL;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
EnhancedList<T>::EnhancedList(const EnhancedList& e2) {				//Copy constructor
	if (e2.isEmpty())
	{
		frontPtr = NULL;
		backPtr = NULL;
	}
	else {
		frontPtr = NULL;										//This initialization is important for enqueue function to work properly
		backPtr = NULL;
		Node<T>* ptrToOld = e2.frontPtr;
		while (ptrToOld != NULL)
		{
			enqueue(ptrToOld->getItem());						//enqueue()--->handles everything...check it out.
			ptrToOld = ptrToOld->getNext();
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

template<typename T>
EnhancedList<T>& EnhancedList<T>::operator=(const EnhancedList& e2) {
	if (&e2 == this)							//handles the case in which the  the object is assigned to itself(usually happens implicitly)
	{
		return *this;
	}											//Same as copy constructor
	if (e2.isEmpty())
	{
		frontPtr = NULL;
		backPtr = NULL;
	}
	else {
		frontPtr = NULL;										
		backPtr = NULL;
		Node<T>* ptrToOld = e2.frontPtr;
		while (ptrToOld != NULL)
		{
			enqueue(ptrToOld->getItem());
			ptrToOld = ptrToOld->getNext();
		}
	}
	return *this;
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
	if (isEmpty())					// if the list is empty [The front pointer must be initialized by NULL]
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
bool EnhancedList<T>::isEmpty() const {			//[The front pointer must be initialized by NULL]
	if (backPtr == NULL || frontPtr == NULL)
	{
		return true;
	}
	return false;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<typename T>
bool EnhancedList<T>::peekFront(T& item) const {
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
	if (frontPtr == NULL)
	{
		return;
	}

	Node<T>* prev = frontPtr;
	frontPtr = frontPtr->getNext();
	while (frontPtr != NULL) {
		delete prev;
		prev = frontPtr;
		frontPtr = frontPtr->getNext();
	}
	delete prev;
	frontPtr = NULL;
	backPtr = NULL;
	
	
}


#endif // !__ENHANCEDLIST_H_