

#ifndef __Set__Card__
#define __Set__Card__

#include <stdio.h>
#include <iostream>
#include <string>

using namespace std;

class Card{
    
private:
    string color;
    int number;
    string shading;
    string symbol;
    
public:
    Card(int i=1, string sym = "Squiggle", string col = "red", string shd = "solid");
    void SetColor(const string &speccolor);
    void SetNumber(const int &specnumber);
    void SetShading(const string &specshading);
    void SetSymbol(const string &specsymbol);
    string GetColor() const;
    int GetNumber() const;
    string GetShading() const;
    string GetSymbol() const;
    void PrintCard() const;
    

};

#endif /* defined(__Set__Card__) */
