#pragma once
#include "std_lib_facilities.h"

class Car{
    private:
        int freeSeats;
    public:
        Car(int);
        
        bool hasFreeSeats() const {return freeSeats;}
        void reserveFreeSeat() {freeSeats--;}
};