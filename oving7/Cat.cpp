#include "Cat.h"

    Cat::Cat(string name, int age): Animal(name, age){
        
    }

    string Cat::toString(){
        string cat = "Cat: " + name + ", ";
        string str_age = to_string(age);
        cat += str_age;

        return cat;
    }