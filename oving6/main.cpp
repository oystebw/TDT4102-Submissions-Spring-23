#include "files.h"
#include "CourseCatalog.h"
#include "Temps.h"

int main(void){
    vector<Temps> vec = readTemps("temperatures.txt");
    tempStats(vec);
    return 0;
}