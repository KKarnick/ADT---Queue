
#include "QueueArray.h"

template <typename DataType>
QueueArray<DataType>::QueueArray(int maxNumber){
    maxSize = maxNumber;
    front = -1; //init at empty
    back = -1;  //init at empty queue
    dataItems = new DataType[maxSize];
}

template <typename DataType>
QueueArray<DataType>::QueueArray(const QueueArray& other){
    if (this != &other) {  //check they are not ref same object
        if (dataItems.getLength() > 0)
            delete[]dataItems;   //delete current dataItems
        if (maxSize != other.maxSize) {
            maxSize = other.maxSize;  //allot space
            dataItems = new DataType[maxSize];
        }
        front = other.front;
        back = other.back;
        int currLoc = front + 1;
        if (front > -1) {  //there are items in dataItems
            dataItems[front] = other.dataItems[front];  //takes care of front item and full list possibility
            while (currLoc != (back + 1)) {
                if (curLoc == maxSize)  //need to cycle to begin of dataItems
                    curLoc = 0;
                dataItems[curLoc] = other.dataItems[curLoc];
                curLoc += 1;
            }
        }
    }
    return *this;
}

template <typename DataType>
QueueArray<DataType>& QueueArray<DataType>::operator=(const QueueArray& other){
    if (this != &other) {  //ensure not already same
        if (dataItems.getLength() > 0)
            delete[]dataItems;   //delete current dataItems
        if (maxSize != other.maxSize) {
            maxSize = other.maxSize;
            dataItems = new DataType[maxSize];  //allot new array w/new size
        }
                                            //copy over all contents
        front = other.front;
        back = other.back;
        int currLoc = front + 1;
        if (front > -1) {  //there are items in dataItems
            dataItems[front] = other.dataItems[front];  //takes care of front item and full list possibility
            while (currLoc != (back + 1)) {
                if (curLoc == maxSize)  //need to cycle to begin of dataItems
                    curLoc = 0;
                dataItems[curLoc] = other.dataItems[curLoc];
                curLoc += 1;
            }

        }
    }
    return *this;
}

template <typename DataType>
QueueArray<DataType>::~QueueArray(){
    delete[]dataItems;
}


template <typename DataType>
void QueueArray<DataType>::enqueue(const DataType& newDataItem) throw (logic_error){
    if (isFull())
        throw logic_error("Queue is full.");
    else {
        back = (back + 1) % maxSize;  //increment back and cycle if necessary
        dataItems[back] = newDataItem;
           //if queue was empty prior, change front to new item
        if (front == -1)
            front = back;   //set to single item location
    }
}

template <typename DataType>
DataType QueueArray<DataType>::dequeue() throw (logic_error){
    if (isEmpty())
        throw logic_error("Queue is empty.");
    else {
        int locToReturn = front;
        if (front == back) {   //dequeing only item
            front = -1;
            back = -1;
            return dataItems[locToReturn];
        }
        else {
            front = (front + 1) % maxSize;  //cycle to beg position if necessary
        }
        return dataItems[locToReturn];
    }
	DataType temp;
	return temp;
}

template <typename DataType>
void QueueArray<DataType>::clear(){
     //set all items to be able to be rewritten
    front = -1;
    back = -1;
}

template <typename DataType>
bool QueueArray<DataType>::isEmpty() const{
    if (front == -1)
        return true;
    else
        return false;
}

template <typename DataType>
bool QueueArray<DataType>::isFull() const{
    if (front == ((back + 1) % maxSize)) //%table size in case last item
        return true;
    else
        return false;
}

template <typename DataType>
void QueueArray<DataType>::putFront(const DataType& newDataItem) throw (logic_error){
        //inserts new item at the front instead of the back as normal
    if (isFull())
        throw logic_error("Queue full.");
    else {
        front = front - 1; //move front back to open space
        if (front < 0)   //if moved round cycle
            front = maxSize - 1;   //moved to last location in queue
        dataItems[front] = newDataItem;  //insert given param into "new" front
    }
}

template <typename DataType>
DataType QueueArray<DataType>::getRear() throw (logic_error){
       //will remove (and return) the rear item instead of front as usual
    if (isEmpty())
        throw logic_error("Queue is empty.");
    else {
        int locToReturn = back;
        if (back == front) {   //only 1 item in queue
            back = -1;
            front = -1;
            return dataItems[locToReturn];
        }
        //else, move back to "new" back element
        back -= 1;
        //verify new back location
        if (back < 0)
            back = maxSize - 1;  //if back was at first loc, move to last for cycle
        return dataItems[locToReturn];
    }
}

template <typename DataType>
int QueueArray<DataType>::getLength() const{
    if (isEmpty())
        return 0;
    else {   //check if order is linear
        if (back > front)
            return (back - front + 1);
        else if (back == front)
            return 1;
        else
            return (maxSize - (front - back) + 1);  //subtract unused from total
    }
}

//--------------------------------------------------------------------

template <typename DataType>
void QueueArray<DataType>::showStructure() const 
// Array implementation. Outputs the data items in a queue. If the
// queue is empty, outputs "Empty queue". This operation is intended
// for testing and debugging purposes only.

{
    int j;   // Loop counter

    if ( front == -1 )
       cout << "Empty queue" << endl;
    else
    {
       cout << "Front = " << front << "  Back = " << back << endl;
       for ( j = 0 ; j < maxSize ; j++ )
           cout << j << "\t";
       cout << endl;
       if ( back >= front )
          for ( j = 0 ; j < maxSize ; j++ )
              if ( ( j >= front ) && ( j <= back ) )
                 cout << dataItems[j] << "\t";
              else
                 cout << " \t";
       else
          for ( j = 0 ; j < maxSize ; j++ )
              if ( ( j >= front ) || ( j <= back ) )
                 cout << dataItems[j] << "\t";
              else
                 cout << " \t";
       cout << endl;
    }
}