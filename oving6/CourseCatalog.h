#pragma once
#include "std_lib_facilities.h"

class CourseCatalog{
    private:
        map<string, string> catalog;
    public:
        CourseCatalog();
        void addCourse(string, string);
        void removeCourse(string);
        string getCourse(string);
        void saveCat(string);
        void loadCat(string);
        friend ostream& operator<<(ostream&, const CourseCatalog);
};