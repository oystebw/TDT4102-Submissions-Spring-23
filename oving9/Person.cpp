#include "Person.h"

Person::Person(string name, string email, Car* c ): name{name}, email{email}{
    if(c){
        car = make_unique<Car>(*c);
    }
    else{
        car = nullptr;
    }
}

ostream& operator<<(ostream& os, const Person& p){
    os << "Name: " << p.getName() << '\n';
    os << "Email: " << p.getEmail() << '\n';
    if(!p.hasCar()){
        os << "Has car: No" << '\n';
        return os;
    }
    os << "Has car: Yes" << '\n';
    if(p.hasAvailableSeats()){
        os << "Has available seat(s): Yes";
    }
    else{
        os << "Has available seat: No";
    }
    os << '\n';
    return os;
}