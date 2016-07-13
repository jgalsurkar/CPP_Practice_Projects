/**********************************************************
 Title:       ArrayList.h
 Author:      Jonathan Galsurkar
 Description: Array Based implementation of the List
 Purpose:     Array typed list with its functionality
 **********************************************************/

#ifndef ArrayList_h
#define ArrayList_h

#include "AbstractList.h"

template <class T>
class ArrayList : public AbstractList<T> {
private:
    T * array_list;
    int size;
    int MAX;
    
public:
    ArrayList (int MAXP);
    bool isEmpty () {return size == 0;}
    int  getLength () {return size;}
    void insert (T item);
    void remove (int pos);
    T    retrieve (int pos);
};


template <class T>
ArrayList<T>::ArrayList (int MAXP) {
    size = 0;
    array_list= new T [MAXP]; //Dynamically creating an array
    MAX = MAXP;
}

template <class T>
void ArrayList<T>::insert (T item) {
    if(size >= MAX)
        throw -1;
    
    array_list[size] = item; //place the item in the position of the size
    
    /*Bubble sort*/
    for(int j = 0; j < size; ++j){
        for(int i = 0; i<size-j; i++){
            if(array_list[i+1] < array_list[i]){ //if the next position is greater then the current one, swap them
                T temp = array_list[i+1];
                array_list[i+1] = array_list[i];
                array_list[i] = temp;
            }
        }
    }
    ++size;    
}

template <class T>
void ArrayList<T>::remove (int pos) {
    if (pos <= 0 || pos > size)
        throw -1;
    
    for(int i = pos; i < size; ++i){
        array_list[i-1] = array_list[i]; // shift from the size to the position moving everything down one
    }
    --size;
}

template <class T>
T ArrayList<T>::retrieve (int pos) {
    if (pos <= 0 || pos > size)
        throw -1;
    return array_list[pos - 1];
}

#endif /* ArrayList_h */
