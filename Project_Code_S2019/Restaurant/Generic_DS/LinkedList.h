#ifndef __LINKEDLIST_H_
#define __LINKEDLIST_H_
#include "Node.h"

// The list starts indexing from 1


template<class T>
class LinkedList {
	int itemCount; //number of elements in the Linked List
	Node<T>* head; //ptr to head
	Node<T>* backPtr; //to enhance the complexity of insertEnd() function

	Node<T>* getNodeAt(int pos) const; //function gets the pointer to the node at a certain position

public:
	LinkedList();
	LinkedList(const LinkedList<T>& l);					//copy constructor
	LinkedList<T> operator=(const LinkedList<T>& l);	//assignment operator

	bool isEmpty()const;					// returns the true if the list is empty of elements
	int getLength() const;					// returns the number of elements in the list
	bool insert(int pos, T item);			//insert at a certain position
	bool remove(int pos, T& item);			//removes nodes from a certain position
	void DeleteAll();						//deletes all elements in the list
	
	bool getItem(int pos, T& item)const;	//returns the value of the item in the Node
	bool setItem(int pos, const T& newItem);
	void traverse(void(* pFn)(T item));				//traverses the list and applies a certain function to each element

	bool peekFront(T& item)const;
	bool insertEnd(const T& item);
	bool removeFront(T& item);
	~LinkedList();								//destructor


	//For testig only
	void printList() {
		Node<T>*curr = head;
		if (curr == NULL) cout << "The list is empty" << endl;
		while (curr != NULL) {
			cout << curr->getItem() << "->";
			curr = curr->getNext();
		}
		cout << "*" << endl;
	}
};

template<class T>
Node<T>* LinkedList<T>::getNodeAt(int pos) const{
	if (pos > itemCount || pos < 1)
	{
		return NULL;
	}
	int count = 1;
	Node<T>* curr = head;
	while (curr != NULL && count <= itemCount)
	{
		if (count == pos)
		{
			return curr;
		}
		curr = curr->getNext();
		count++;
	}
	return NULL;
}
template<class T>
LinkedList<T>::LinkedList():head(nullptr), backPtr(nullptr), itemCount(0) {

}
template<class T>
LinkedList<T>::LinkedList(const LinkedList<T>& l) {
	head = NULL;
	backPtr = NULL;
	itemCount = 0;
	Node<T>* curr = l.head;
	while (curr != NULL) {
		insertEnd(curr->getItem());
		curr = curr->getNext();
	}


}
template<class T>
LinkedList<T> LinkedList<T>::operator=(const LinkedList<T>& l) {
	if (l.head == head) // if the list is assigned to itself (usually this happens implicitly)
	{
		return *this;
	}
	if (head != NULL)
	{
		DeleteAll();
	}
	head = NULL;	//redundant but for more precaution
	backPtr = NULL;	//redundant but for more precaution
	itemCount = 0;	//redunant but for more precaution
	Node<T>* curr = l.head;
	while (curr != NULL) {
		insertEnd(curr->getItem());
		curr = curr->getNext();
	}
	return *this;

}
template<class T>
bool LinkedList<T>::isEmpty()const {
	return !itemCount;

}
template<class T>
int LinkedList<T>::getLength() const {
	return itemCount;
}
template<class T>
bool LinkedList<T>::insert(int pos, T item) {
	if (pos > itemCount + 1 || pos < 1)
	{
		return false;
	}
	Node<T>* newNode = new Node<T>(item);
	
	if (pos == 1)
	{
		newNode->setNext(head);
		head = newNode;
		itemCount++;
		if (itemCount == 1)
		{
			backPtr = newNode;
		}
		return true;
	}
	if (pos == itemCount+1)
	{
		newNode->setNext(NULL);
		backPtr->setNext(newNode);
		backPtr = newNode;
		itemCount++;
		return true;
	}


	Node<T>* prev = getNodeAt(pos - 1);
	newNode->setNext(prev->getNext());
	prev->setNext(newNode);
	itemCount++;
	return true;
}
template<class T>
bool LinkedList<T>::remove(int pos, T& item) {
	if (pos > itemCount || pos < 1)
	{
		return false;
	}
	if (pos == 1)
	{
		Node<T>* toDelete = head;
		item = head->getItem();
		head = head->getNext();
		delete toDelete;
		itemCount--;
		if (itemCount == 0)
		{
			backPtr == NULL;
		}
		return true;
	}
	
	Node<T>*prev = getNodeAt(pos-1);
	Node<T>* toDelete = prev->getNext();
	item = toDelete->getItem();
	prev->setNext(toDelete->getNext());
	delete toDelete;
	if (pos == itemCount)
	{
		backPtr = prev;
	}
	itemCount--;
	return true;
}
template<class T>
void LinkedList<T>::DeleteAll() {
	if (isEmpty())
	{
		return;
	}
	while (head!=NULL)
	{
		T item;
		remove(1, item);
	}
}
template<class T>
bool LinkedList<T>::getItem(int pos, T& item)const {
	if (pos > itemCount || pos < 1)
	{
		return false;
	}
	item = getNodeAt(pos)->getItem();
	return true;
}
template<class T>
bool LinkedList<T>::setItem(int pos, const T& newItem) {
	if (pos > itemCount || pos < 1)
	{
		return false;
	}
	Node<T>* temp = getNodeAt(pos);
	temp->setItem(newItem);
	return true;
}
template<class T>
void LinkedList<T>::traverse(void(* pFn)(T item)) {
	if (isEmpty()) return;
	Node<T>* curr = head;
	while (curr!=NULL)
	{
		(*pFn)(curr->getItem());
		curr = curr->getNext();
	}

}
template<class T>
LinkedList<T>::~LinkedList() {
	DeleteAll();
}
template<class T>
bool LinkedList<T>::peekFront(T& item)const {
	return getItem(1, item);
}
template<class T>
bool LinkedList<T>::insertEnd(const T& item) {
	return insert(itemCount+1, item);
}
template<class T>
bool LinkedList<T>::removeFront(T& item) {
	return remove(1,item);
}

#endif //!__LINKEDLIST_H_