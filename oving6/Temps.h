#pragma once
#include "std_lib_facilities.h"

class Temps{
    private:
        float max;
        float min;
    public:
        Temps();
        friend istream& operator>>(istream&, Temps&);
        friend ostream& operator<<(ostream&, Temps&);
        friend void tempStats(vector<Temps>);
};

vector<Temps> readTemps(string);
void printTemps(vector<Temps>);
void tempStats(vector<Temps>);