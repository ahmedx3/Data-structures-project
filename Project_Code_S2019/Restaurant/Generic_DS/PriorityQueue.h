#ifndef _PRIORITYQUEUE
#define _PRIORITYQUEUE
#include "Node.h"

template<typename T>
class PriorityQueue
{
private:
	Node<T>* backPtr;
	Node<T>* frontPtr;
public:
	PriorityQueue();
	bool isEmpty() const;
	bool enqueue(const T& newEntry);
	bool dequeue(T& frntEntry);
	bool peekFront(T& frntEntry)  const;
	~PriorityQueue();
};


template<typename T>
inline PriorityQueue<T>::PriorityQueue()
{
	backPtr = nullptr;
	frontPtr = nullptr;
}
///////////////////////////////////////////////////////////////////////////



template<typename T>
inline bool PriorityQueue<T>::isEmpty() const
{
	if (frontPtr == nullptr)
		return true;
	else
		return false;
}
///////////////////////////////////////////////////////////////////////////


template<typename T>
inline bool PriorityQueue<T>::enqueue(const T & newEntry)
{
	Node<T>* newNodePtr = new Node<T>(newEntry);	 // Create New Node With Data

	if (isEmpty())		// If Empty Make Front and Back pointers points to first node
	{
		frontPtr = newNodePtr;
		backPtr = newNodePtr;
		return true;
	}

	if (newNodePtr->getItem() > frontPtr->getItem())    // If newEntry has higher priority than first node put it before first
	{
		newNodePtr->setNext(frontPtr);
		frontPtr = newNodePtr;
		return true;
	}

	Node<T>* temp = frontPtr;

	while (temp->getNext())			// insert newNode after last one similar in piriority
	{
		if (newNodePtr->getItem() > temp->getNext()->getItem())
		{
			newNodePtr->setNext(temp->getNext());
			temp->setNext(newNodePtr);
			return true;
		}
		temp = temp->getNext();
	}

	backPtr->setNext(newNodePtr);		// new node has least priority so insert at last
	backPtr = newNodePtr;
	return true;

}
///////////////////////////////////////////////////////////////////////////


template<typename T>
inline bool PriorityQueue<T>::dequeue(T & frntEntry)
{
	if (isEmpty())
		return false;

	Node<T>* nodeToDeletePtr = frontPtr;
	frntEntry = frontPtr->getItem();
	frontPtr = frontPtr->getNext();
	// Queue is not empty; remove front
	if (nodeToDeletePtr == backPtr)	 // Special case: one node in queue
		backPtr = nullptr;

	// Free memory reserved by the dequeued node
	delete nodeToDeletePtr;


	return true;
}
///////////////////////////////////////////////////////////////////////////


template<typename T>
inline bool PriorityQueue<T>::peekFront(T & frntEntry) const
{
	if (isEmpty())
		return false;

	frntEntry = frontPtr->getItem();
	return true;
}
///////////////////////////////////////////////////////////////////////////


template<typename T>
inline PriorityQueue<T>::~PriorityQueue()
{
}
///////////////////////////////////////////////////////////////////////////


#endif