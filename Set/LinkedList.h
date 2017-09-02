

#ifndef __Set__LinkedList__
#define __Set__LinkedList__

#include <stdio.h>
#include "Node.h"
#include "Card.h"
#include <vector>


template <typename T>

class LinkedList
{
private:
    Node<T> *phead;
    Node<T> *ptail;
    
    
public:
    LinkedList();
    ~LinkedList(); //add more
    void AddFront(T nodeval);
    void DeleteHead();
    void PrintList();
    vector<T> ReleaseList();
    T ReleaseFirst();

};

#endif /* defined(__Set__LinkedList__) */
