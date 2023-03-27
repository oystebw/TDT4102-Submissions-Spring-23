#pragma once
#include "std_lib_facilities.h"
#include "Car.h"

class Person{
    private:
        string name;
        string email;
        unique_ptr<Car> car;
    public:
        Person(string, string, Car* = nullptr);

        string getName() const {return name;}
        string getEmail() const {return email;}

        void setEmail(string mail) {email = mail;}

        bool hasCar() const {return car.get();}
        bool hasAvailableSeats() const {
            if(!car){
                return 0;
            }
            return car->hasFreeSeats();
        }
};

ostream& operator<<(ostream&, const Person&);