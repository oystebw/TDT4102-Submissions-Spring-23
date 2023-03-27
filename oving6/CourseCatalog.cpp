#include "CourseCatalog.h"

CourseCatalog::CourseCatalog(){

}

void CourseCatalog::addCourse(string code, string name){
    catalog[code] = name;
}

void CourseCatalog::removeCourse(string code){
    catalog.erase(code);
}

string CourseCatalog::getCourse(string code){
    return catalog.at(code);
}

ostream& operator<<(ostream& os, const CourseCatalog cat){
    for(auto& pair: cat.catalog){
        os << pair.first << ": " << pair.second << '\n';
    }
    return os;
}

void CourseCatalog::saveCat(string filename){
    ofstream file{filename};

    for(auto& pair: catalog){
        file << pair.first << '\n';
        file << pair.second << '\n';
    }
    file.close();
}

void CourseCatalog::loadCat(string filename){
    ifstream file{filename};

    if(!file){
        return;
    }

    string key;
    string value;

    while(getline(file, key)){
        getline(file, value);
        catalog[key] = value;
    }
}