

#include <iostream>
#include "Card.h"
#include "Node.h"
#include "Node.cpp"
#include "LinkedList.h"
#include "LinkedList.cpp"
#include "Deck.h"

bool ReturnSet(Card c1, Card c2, Card c3)
{
    bool set = false;
    if(((c1.GetColor().compare(c2.GetColor())==0) && (c2.GetColor().compare(c3.GetColor())==0) && (c1.GetColor().compare(c3.GetColor())==0)) || ((c1.GetColor().compare(c2.GetColor())!=0) && (c2.GetColor().compare(c3.GetColor())!=0) && (c1.GetColor().compare(c3.GetColor())!=0)))
    {
        set = true;
    }
    else{
        return false;
    }
    if(((c1.GetShading().compare(c2.GetShading())==0) && (c2.GetShading().compare(c3.GetShading())==0) && (c1.GetShading().compare(c3.GetShading())==0)) || ((c1.GetShading().compare(c2.GetShading())!=0) && (c2.GetShading().compare(c3.GetShading())!=0) && (c1.GetShading().compare(c3.GetShading())!=0)))
    {
        set = true;
    }
    else{
        return false;
    }
    if(((c1.GetSymbol().compare(c2.GetSymbol())==0) && (c2.GetSymbol().compare(c3.GetSymbol())==0) && (c1.GetSymbol().compare(c3.GetSymbol())==0)) || ((c1.GetSymbol().compare(c2.GetSymbol())!=0) && (c2.GetSymbol().compare(c3.GetSymbol())!=0) && (c1.GetSymbol().compare(c3.GetSymbol())!=0)))
    {
        set = true;
    }
    else{
        return false;
    }
    if(((c1.GetNumber()==c2.GetNumber()) && (c2.GetNumber()==c3.GetNumber()) && (c1.GetNumber()==c3.GetNumber()))|| ((c1.GetNumber()!=c2.GetNumber()) && (c2.GetNumber()!=c3.GetNumber()) && (c1.GetNumber()!=c3.GetNumber())))
    {
        set = true;
    }
    else{
        return false;
    }
    return set;
}

void PlaySet()
{
    Deck gamedeck;
    gamedeck.CreateDeck();
    gamedeck.Shuffle();
    vector<Card> deal;
    gamedeck.Deal(12, deal);
    for(int i=0;i<12;i++)
    {
        deal[i].PrintCard();
    }
    cout<<endl;
    for(int i=0;i<10;i++)
    {
        for(int j=1;j<11;j++)
        {
            for(int k=2;k<12;k++)
            {
                if((j>i)&&(k>j))
                {
                    bool set;
                    set = ReturnSet(deal[i], deal[j], deal[k]);
                    if (set == true)
                    {
                        cout<<"Set:"<<endl;
                        deal[i].PrintCard();
                        deal[j].PrintCard();
                        deal[k].PrintCard();
                        cout<<endl;
                    }
                }
            }
        }
    }
}

vector<Card> FindLargestNonSet()
{
    Deck gamedeck;
    gamedeck.CreateDeck();
    gamedeck.Shuffle();
    vector<Card> largecard;
    vector<Card> realdeal;
    try{
    gamedeck.Deal(3, realdeal);
    }
    catch(const std::invalid_argument &ex){
        cout<<ex.what()<<endl;
    }
    for(int n=0;n<150;n++)
    {
        bool f = true;
        while(f ==true)
        {
            gamedeck.Shuffle();
            bool result = false;
            for(int i=0;i<(realdeal.size()-2);i++)
            {
                for(int j=1;j<(realdeal.size()-1);j++)
                {
                    for(int k=2;k<realdeal.size();k++)
                    {
                        if((j>i)&&(k>j))
                        {
                            bool set = ReturnSet(realdeal[i], realdeal[j], realdeal[k]);
                            if (set == true)
                            {
                                result = true;
                            }
                        }
                    }
                }
            }
            if (result == false)
            {
                if(realdeal.size()>largecard.size())
                {
                    largecard.clear();
                    for(int i=0;i<realdeal.size();i++)
                    {
                        largecard.push_back(realdeal[i]);
                    }
                }
                try{
                    gamedeck.Deal(1, realdeal);
                }
                catch(const std::invalid_argument &ex){
                    cout<<ex.what()<<endl;
                }
            }
            else if (result ==true){
                f = false;
            }
        }
    }
    return largecard;
}

int main(int argc, const char * argv[])
{
    PlaySet();
    vector<Card> v = FindLargestNonSet();
    cout<<"Largest card group with no sets: "<<v.size()<<endl;
    for(int i=0;i<v.size();i++)
    {
        v[i].PrintCard();
    }
    return 0;
}
