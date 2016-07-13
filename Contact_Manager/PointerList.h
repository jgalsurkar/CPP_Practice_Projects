/**********************************************************
 Title:       PBList.hpp
 Author:      Jonathan Galsurkar
 Description: Pointer Based implementation of the List
 Purpose:     Linked list with its functionality
 **********************************************************/

#ifndef PointerList_h
#define PointerList_h

#include "AbstractList.h"

template <class T>
struct Node {
    T data;
    Node * next;
};

template <class T>
class PointerList : public AbstractList<T> {
    
private:
    Node<T> * head;
    int       count;
    
    Node<T> * find (int pos); //returns the node at the given position
    
public:
    PointerList ();
    ~PointerList ();
    
    bool isEmpty () {return count == 0;}
    int  getLength () {return count;}
    void insert (T item);
    void remove (int pos);
    T    retrieve (int pos);
    
};

template <class T>
PointerList<T>::PointerList () {
    head = NULL; //sets head to NULL and the count to 0
    count = 0;
}

template <class T>
PointerList<T>::~PointerList () {
    while (!isEmpty()) //Removes everything from the list
        remove(1);
}

template <class T>
Node<T> * PointerList<T>::find (int pos) {
    if (pos < 1 || pos > count + 1)
        throw -1;
    
    Node<T> * temp = head; //make a temporary node to head and traverse until we hit the position
    for (int i = 1; i < pos; ++i) {
        temp = temp->next;
    }
    return temp;
}

template <class T>
void PointerList<T>::insert (T item){
    
    Node<T> * node = new Node<T>();
    //Inserting sorted. We first set nodes data equal to the item or contact in our case
    node->data = item;
    Node<T> * temp = head;
    //If the list is empty or the first positons last name is greates then our contacts last name we place it in the first position
    if(head == NULL || node->data < head->data){
        node->next = head;
        head = node;
    }
    //Otherwise we loop until temps nexts last name gets greater then nodes last name
    //which means temp is right before node so we place node right after it
    else{
        while(temp->next != NULL && temp->next->data < node->data)
            temp = temp->next;
        
        node->next = temp->next;
        temp->next = node;
    }
    
    ++count;
    
}

template <class T>
void PointerList<T>::remove (int pos) {
    if (pos < 1 || pos > count)
        throw -1;
    
    Node<T> * curr = find(pos);
    if (pos == 1) //If removing form the head, we just point head to whatever currents next was pointing to
        head = curr->next;
    else {
        Node<T> * prev = find(pos-1);// otherwise get the previous node and make its next point
        prev->next = curr->next;    //to whatever current was pointing too
    }
    
    delete curr; //delete curr and set it equal to null to avoid a memory leakr
    curr = NULL;
    
    --count;
    
}

template <class T>
T PointerList<T>::retrieve (int pos) {
    if (pos < 1 || pos > count)
        throw -1;
    
    return find(pos)->data;
}

#endif /* PointerList_h */
