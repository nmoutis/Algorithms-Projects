
#include "Deck.h"
#include <stdio.h>
#include <iostream>
#include <vector>
#include "Card.h"
#include "LinkedList.cpp"
#include "LinkedList.h"
#include <random>
#include <time.h>
#include <chrono>
#include <stdexcept>

using namespace std;


void Deck::CreateDeck() //initialises a sorted deck of 81 unique card objects
{
    vector<Card> cards;
    for(int i=0;i<81;i++)
    {
        Card card;
        cards.push_back(card);
    }
    for(int i=0; i<3;i++)
    {
        for(int j=0; j<3;j++)
        {
            for(int k=0;k<3;k++)
            {
                for(int l=0;l<3;l++)
                {
                    if(l==0){cards[((i*27)+(j*9)+(k*3)+l)].SetSymbol("Squiggle");}
                    if(l==1){cards[((i*27)+(j*9)+(k*3)+l)].SetSymbol("Diamond");}
                    if(l==2){cards[((i*27)+(j*9)+(k*3)+l)].SetSymbol("Oval");}
                    if(k==0){cards[((i*27)+(j*9)+(k*3)+l)].SetShading("Solid");}
                    if(k==1){cards[((i*27)+(j*9)+(k*3)+l)].SetShading("Striped");}
                    if(k==2){cards[((i*27)+(j*9)+(k*3)+l)].SetShading("Open");}
                    if(j==0){cards[((i*27)+(j*9)+(k*3)+l)].SetNumber(1);}
                    if(j==1){cards[((i*27)+(j*9)+(k*3)+l)].SetNumber(2);}
                    if(j==2){cards[((i*27)+(j*9)+(k*3)+l)].SetNumber(3);}
                    if(i==0){cards[((i*27)+(j*9)+(k*3)+l)].SetColor("Red");}
                    if(i==1){cards[((i*27)+(j*9)+(k*3)+l)].SetColor("Green");}
                    if(i==2){cards[((i*27)+(j*9)+(k*3)+l)].SetColor("Purple");}
                }
            }
        }
    }
    for(int i=0;i<81;i++)
    {
        decklist.AddFront(cards[i]);
    }
}

void Deck::Shuffle() //Shuffles the card objects in the deck linked list "decklist"
{
    vector<Card> cardvector = decklist.ReleaseList();
    for(int i=0;i<81;i++)
    {
        decklist.DeleteHead();
    }
    
    vector<int> vector81;
    for(int i=0;i<81;i++)
    {
        vector81.push_back(i);
    }
    
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    shuffle(vector81.begin(), vector81.end(), std::default_random_engine(seed));
    
    for(int i = 0;i<81;i++)
    {
        decklist.AddFront(cardvector[vector81[i]]);
    }
}

vector<Card> Deck::Deal(const int &num, vector<Card> &v) //Deals num cards into the vector passed to the function
{
    if(num<=0)
    {
        throw std::invalid_argument("Must input a positive number.");
    }
    for(int i=0;i<num;i++)
    {
        v.push_back(decklist.ReleaseFirst());
        decklist.DeleteHead();
    }
    return v;
}

void Deck::Replace(vector<Card> &v) //replaces all of the card objects in the passed vector into the linked list decklist
{
    for(int i=0;i<v.size();i++)
    {
        decklist.AddFront(v[i]);
    }
}




