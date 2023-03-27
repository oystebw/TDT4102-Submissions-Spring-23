#include <assert.h>
#include <iostream>
#include <string.h>
#include "Matrix.h"

void fillInFibNumbers(int* result, int length){
    assert(length >= 1);
    if(length == 1){
        result[0] = 0;
        return;
    }
    result[0] = 0;
    result[1] = 1;

    for(int x{2}; x < length; x++){
        result[x] = result[x - 1] + result[x - 2];
    }
}

void printArr(int* arr, int length){
    for(int x{0}; x < length; x++){
        std::cout << arr[x] << '\n';
    }
}

void createFib(void){
    int size;
    int* arr;
    std::cout << "Size: ";
    std::cin >> size;
    arr = new int[size];
    fillInFibNumbers(arr, size);
    printArr(arr, size);
    delete[] arr;
}

int main(){
    Matrix m(5);

    m*=6;

    std::cout << m*5;
}