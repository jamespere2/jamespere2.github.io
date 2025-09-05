#include <iostream>
#ifndef QueueT_H
#define QueueT_H
using namespace std;

template <class ItemType>
struct NodeType
{
	ItemType info;
	NodeType<ItemType>* next;
};
template <class ItemType>
class Que
{
public:
	Que();
	~Que();

	// user-defined copy constructor
	Que(const Que<ItemType>& original);
	// user-defined assignment operator
	void operator=(Que <ItemType>& otherQueue);
	void makeEmpty();
	bool empty() const;
	bool full() const;

	void addQ(ItemType newItem);
	void removeQ(ItemType& item);
	void removeQ();
	void print() const;
private:
	NodeType<ItemType>* qFront;
	NodeType<ItemType>* qRear;
};
template <class ItemType>
Que<ItemType>::Que() // Class constructor.
// Post: qFront and qRear are set to NULL.
{
	qFront = NULL;
	qRear = NULL;
}
template <class ItemType> // Class destructor.
Que<ItemType>::~Que()
{
	makeEmpty();
}
template<class ItemType> // user-defined copy constructor
Que<ItemType>::Que(const Que <ItemType>& original)
{
	NodeType<ItemType>* tempPtr;
	NodeType<ItemType>* newPtr;
	if (original.qFront == 0)
		qFront = qRear = NULL;
	else // allocate memory for first node
	{
		tempPtr = original.qFront;
		newPtr = new NodeType<ItemType>;
		newPtr->info = tempPtr->info;
		tempPtr = tempPtr->next;
		qFront = newPtr;
		while (tempPtr != NULL) // deep copy other nodes
		{
			newPtr->next = new NodeType< ItemType >;
			newPtr = newPtr->next;
			newPtr->info = tempPtr->info;
			tempPtr = tempPtr->next;
		}
		newPtr->next = NULL;
		qRear = newPtr;
	}
}
template <class ItemType>
void Que<ItemType>::makeEmpty()
// Post: Queue is empty; all elements have been deallocated.
{
	NodeType<ItemType>* tempPtr;
	while (qFront != NULL)
	{
		tempPtr = qFront;
		qFront = qFront->next;
		delete tempPtr;
	}
	qRear = NULL;
}
template <class ItemType> // user-defined assignment operator
void Que <ItemType>::operator=(Que <ItemType>& otherQueue)
{
	if (this != &otherQueue)
	{
		NodeType<ItemType>* tempPtr;
		NodeType<ItemType>* newPtr;
		if (otherQueue.Empty())
			empty();
		else // allocate memory for first node
		{
			tempPtr = otherQueue.qFront;
			newPtr = new NodeType<ItemType>;
			newPtr->info = tempPtr->info;
			tempPtr = tempPtr->next;
			qFront = newPtr;
			while (tempPtr != NULL) // deep copy other nodes
			{
				newPtr->next = new NodeType< ItemType >;
				newPtr = newPtr->next;
				newPtr->info = tempPtr->info;
				tempPtr = tempPtr->next;
			}
			newPtr->next = NULL;
			qRear = newPtr;
		}
	}
	else
		cout << "The two queues are the same. " << endl;
}
template <class ItemType>
bool Que<ItemType>::full() const
// Returns true if there is no memory for another ItemType in the heap;
// false otherwise.
{
	NodeType<ItemType>* ptr;
	ptr = new NodeType<ItemType>;
	if (ptr == NULL)
		return true;
	else
	{
		delete ptr;
		return false;
	}
}
template <class ItemType>
bool Que<ItemType>::empty() const
// Returns true if there are no elements in the queue; false otherwise.
{
	return (qFront == NULL);
}
template <class ItemType>
void Que<ItemType>::addQ(ItemType newItem)
// Adds newItem to the rear of the queue.
// Pre: Queue has been initialized and is not full.
// Post: newItem is at rear of queue.
{
	NodeType<ItemType>* newNode;
	newNode = new NodeType<ItemType>;
	newNode->info = newItem;
	newNode->next = NULL;
	if (qRear == NULL)
		qFront = newNode;
	else
		qRear->next = newNode;
	qRear = newNode;
}
template <class ItemType>
void Que<ItemType>::removeQ()
// Removes front item from the queue and returns it in item.
// Pre: Queue has been initialized and is not empty.
// Post: Front element has been removed from queue.
// item is a copy of removed element.
{
	NodeType<ItemType>* tempPtr;
	tempPtr = qFront;
	qFront = qFront->next;
	if (qFront == NULL)
		qRear = NULL;
	delete tempPtr;
}
template <class ItemType>
void Que<ItemType>::removeQ(ItemType& item)
// Removes front item from the queue and returns it in item.
// Pre: Queue has been initialized and is not empty.
// Post: Front element has been removed from queue.
// item is a copy of removed element.
{
	NodeType<ItemType>* tempPtr;
	tempPtr = qFront;
	item = qFront->info;
	qFront = qFront->next;
	if (qFront == NULL)
		qRear = NULL;
	delete tempPtr;
}
template <class ItemType>
void Que<ItemType>::print() const
{
	NodeType<ItemType>* tempPtr;
	tempPtr = qFront;
	while (tempPtr != NULL)
	{
		cout << tempPtr->info << ' ';
		tempPtr = tempPtr->next;
	}
	cout << endl;


	
}
#endif
