

#ifndef __Set__Deck__
#define __Set__Deck__

#include <stdio.h>
#include <iostream>
#include "Card.h"
#include <vector>
//#include "LinkedList.cpp"
#include "LinkedList.h"

using namespace std;


class Deck{
    
private:
    LinkedList<Card> decklist;
    
public:
    void CreateDeck();
    void Shuffle();
    vector<Card> Deal(const int &num, vector<Card> &v);
    void Replace(vector<Card> &v);
    
};


#endif /* defined(__Set__Deck__) */
