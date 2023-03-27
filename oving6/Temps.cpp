#include "Temps.h"

Temps::Temps(){

}

istream& operator>>(istream& is, Temps& t){
    is >> t.max >> t.min;
    return is;
}

ostream& operator<<(ostream& os, Temps& t){
    os << "Max: " << t.max << " - Min: " << t.min << '\n';
    return os;
}

vector<Temps> readTemps(string filename){
    vector<Temps> vec;
    ifstream file{filename};
    if(!file){
        return vec;
    }

    Temps t;

    while(file >> t){
        vec.push_back(t);
    }
    return vec;
}

void printTemps(vector<Temps> vec){
    for(auto& el: vec){
        cout << el;
    }
}

void tempStats(vector<Temps> vec){
    const int size = vec.size();
    
    int highestIndex;
    int lowestIndex;

    float highest = -INFINITY;
    float lowest = INFINITY;

    for(int x{0}; x < size; x++){
        if(vec[x].max > highest){
            highest = vec[x].max;
            highestIndex = x;
        }
        if(vec[x].min < lowest){
            lowest = vec[x].min;
            lowestIndex = x;
        }
    }
    cout << "Høyeste temperatur på indeks: " << highestIndex << ", med temperatur: " << highest << '\n';
    cout << "Lavest temperatur på indeks: " << lowestIndex << ", med temperatur: " << lowest << '\n';
}