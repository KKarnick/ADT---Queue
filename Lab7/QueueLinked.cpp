
#include "QueueLinked.h"

template <typename DataType>
QueueLinked<DataType>::QueueNode::QueueNode(const DataType& nodeData, QueueNode* nextPtr){
	//create a new node in queue
	dataItem = nodeData;
	next = nextPtr;
}

template <typename DataType>
QueueLinked<DataType>::QueueLinked(int maxNumber = Queue<DataType>::MAX_QUEUE_SIZE){
	front = 0;
	back = 0;
}

template <typename DataType>
QueueLinked<DataType>::QueueLinked(const QueueLinked& other){
	if (this != &other) {
		clear();  //clear current queue (deallocate space)
		QueueNode* curr = other.front;
		     //copy contents of queue
		while (curr != 0) {
			enqueue(curr->dataItem);
			curr = curr->next
		}
		     //set variables
		front = other.front;
		back = other.back
	}
	return *this;
}

template <typename DataType>
QueueLinked<DataType>& QueueLinked<DataType>::operator=(const QueueLinked& other){
	if (this != &other) {
		clear();  //clear current queue (deallocate space)
		QueueNode* curr = other.front;
		//copy contents of queue
		while (curr != 0) {
			enqueue(curr->dataItem);
			curr = curr->next
		}
		//set variables
		front = other.front;
		back = other.back
	}
	return *this;
}

template <typename DataType>
QueueLinked<DataType>::~QueueLinked(){
	clear();
}

template <typename DataType>
void QueueLinked<DataType>::enqueue(const DataType& newDataItem) throw (logic_error){
	if (isFull())
		throw logic_error("Queue is full.");
	else {
		QueueNode* newNode = new QueueNode(newDataItem, 0);
		 //check if any items already in list
		if (isEmpty())
			front = newNode;
		else 
			back->next = newNode;
		back = newNode;  //regardless of loops, back will be newNode
	}
}

template <typename DataType>
DataType QueueLinked<DataType>::dequeue() throw (logic_error){
	if (isEmpty())
		throw logic_error("Queue is empty.");
	else {
		QueueNode* nodeToRemove = front;
		DataType temp = front->dataItem;
		front = front->next;
		delete nodeToRemove;
		return temp;
	}
}

template <typename DataType>
void QueueLinked<DataType>::clear(){
	QueueNode* curr = front;
	while (curr != 0) {   //0 denotes nullptr again in this program
		front = front->next;
		delete curr;
		curr = front;
	}
	  //when finished deleting all elements, set back to nullptr
	back = 0;
}

template <typename DataType>
bool QueueLinked<DataType>::isEmpty() const{
	if (front == 0)
		return true;
	else
		return false;
}

template <typename DataType>
bool QueueLinked<DataType>::isFull() const{
        //only depends upon usable space...considered to always be expandable for this lab
	return false;
}

template <typename DataType>
void QueueLinked<DataType>::putFront(const DataType& newDataItem) throw (logic_error){
	if (isFull())
		throw logic_error("Queue is full.");
	else {
		front = new QueueNode(newDataItem, front);  //new item points to "old" front
		        //check if first item in queue
		if (back == 0)
			back = front;
	}
}

template <typename DataType>
DataType QueueLinked<DataType>::getRear() throw (logic_error){
	if (isEmpty())
		throw logic_error("Empty queue.");
	else {
		DataType itemToReturn = back->dataItem;
		QueueNode* curr = front;
		if (front == back) {  //only 1 item in queue
			delete front;
			front = 0;
			back = 0;

		}
		else {   //find item before back
			while (curr->next != back)
				curr = curr->next;
			curr->next = 0;  //set to point to null instead of back
			delete back;   //delete last item
			back = curr;   //set back to "new" back
		}
		return itemToReturn;
	}
}

template <typename DataType>
int QueueLinked<DataType>::getLength() const{
	int len = 0;
	QueueNode* curr = front;
	while (curr != 0) {
		len += 1;
		curr = curr->next;
	}
	return len;
}

template <typename DataType>
void QueueLinked<DataType>::showStructure() const
{
    QueueNode *p;   // Iterates through the queue

    if ( isEmpty() )
	cout << "Empty queue" << endl;
    else
    {
	cout << "Front\t";
	for ( p = front ; p != 0 ; p = p->next )
	{
	    if( p == front ) 
	    {
		cout << '[' << p->dataItem << "] ";
	    }
	    else
	    {
		cout << p->dataItem << " ";
	    }
	}
	cout << "\trear" << endl;
    }
}