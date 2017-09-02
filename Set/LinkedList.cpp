

#include "LinkedList.h"
#include <vector>


template <typename T>
LinkedList<T>::LinkedList(void) //constructor
{
    phead = ptail = NULL;
}

template <typename T>
LinkedList<T>::~LinkedList(void) //destructor
{
    Node<T> *pdelete = phead;
    while(phead != NULL)
    {
        phead = phead->next;
        delete pdelete;
        pdelete = phead;
    }
    phead = ptail = NULL;
}

template <typename T>
void LinkedList<T>::AddFront(T nodeval) //replaces the head node with a new node that has nodeval
{
    if(phead == NULL)
    {
        ptail = phead = new Node<T>(nodeval);
    }
    else
    {
        Node<T> *node1;
        node1 = new Node<T>(nodeval);
        node1->next = phead;
        phead = node1;
    }
}

template <typename T>
void LinkedList<T>::DeleteHead() //remove the head node from the list
{
    if(phead != ptail)
    {
        Node<T> *Delete = NULL;
        Delete = phead;
        phead = Delete->next;
        delete Delete;
    }
}

template <typename T>
void LinkedList<T>::PrintList() //print the value of each node in the list
{
    Node<T> *p = phead;
    while(p != NULL)
    {
        cout<<p->nodeValue<<endl;
        p = p->next;
    }
}

template <typename T>
vector<T> LinkedList<T>::ReleaseList() //returns the contents of the linked list to a vector
{
    vector<T> cardvector;
    Node<T> *p = phead;
    while(p != NULL)
    {
        cardvector.push_back(p->nodeValue);
        p = p->next;
    }
    return cardvector;
}

template <typename T>
T LinkedList<T>::ReleaseFirst() //returns the head node's nodevalue
{
    Node<T> *p = phead;
    return p->nodeValue;
}







