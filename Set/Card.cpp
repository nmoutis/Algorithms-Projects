
#include "Card.h"
#include <iostream>


using namespace std;

Card::Card(int i, string sym, string col, string shd)
{
    number = i;
    color = col;
    symbol = sym;
    shading = shd;
}

//Getters and setters for data members

void Card::SetColor(const string &speccolor)
{
    color = speccolor;
}

void Card::SetNumber(const int &specnumber)
{
    number = specnumber;
}

void Card::SetShading(const string &specshading)
{
    shading = specshading;
}

void Card::SetSymbol(const string &specsymbol)
{
    symbol = specsymbol;
}

string Card::GetColor() const
{
    return color;
}

int Card::GetNumber() const
{
    return number;
}

string Card::GetShading() const
{
    return shading;
}

string Card::GetSymbol() const
{
    return symbol;
}

void Card::PrintCard()const //Prints the properties of a card object
{
    cout<<number<<" "<<color<<" "<<shading<<" "<<symbol<<endl;
}

