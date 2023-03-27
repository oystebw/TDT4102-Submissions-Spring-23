#pragma once
#include "std_lib_facilities.h"

class Animal{
    private:
    protected:
        string name;
        int age;
    public:
        Animal(string name, int age): name{name}, age{age}{}
        virtual ~Animal(){}

        virtual string toString() = 0;
};