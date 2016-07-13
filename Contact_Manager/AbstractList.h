/**********************************************************
 Title:       AbstractList.h
 Author:      Jonathan Galsurkar
 Description: Abstract Base Class for Lists
 Purpose:     Dynamic Binding
 **********************************************************/

#ifndef AbstractList_h
#define AbstractList_h

/* Abstract Base Class for the lists. The lists will have the
   following functionality and therefore I'll explain them here. */

template <class T>
class AbstractList {
public:
    virtual bool isEmpty () = 0;
    /*The lists derived will checks to see if the list is empty by seeing if the size
     of the list is equal to 0. If so it returns true, false otherwise*/
    
    virtual int  getLength () = 0;
    /*The lists derived will return their size (the amount of elements in the list)*/
    
    virtual void insert (T item) = 0;
    /*The item of any type will be inserted into the list sorted.*/
    virtual void remove (int pos) = 0;
    /*The item in the given position will be deleted from the list.*/
    virtual T    retrieve (int pos) = 0;
    /*The item in the given position will be returned from the list.*/
};

#endif /* AbstractList_h */
