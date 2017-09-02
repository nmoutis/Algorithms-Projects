

#ifndef __Set__Node__
#define __Set__Node__

#include <stdio.h>
template <typename T>
class Node
{
public:
    T nodeValue;
    Node<T> *next;
    Node(): next(NULL){}
    Node(const T &item, Node<T> *nextnode=NULL): nodeValue(item), next(nextnode){};
};

#endif /* defined(__Set__Node__) */
