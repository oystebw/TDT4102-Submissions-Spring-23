#include "files.h"

void toFile(void){
    string filename;
    cout << "Filename: ";
    cin >> filename;
    filename += ".txt";

    ofstream file{filename};

    string input;

    cout << "Write to " << filename << " :" << '\n';
    cin >> input;

    while (input != "quit"){
        file << input << '\n';
        cin >> input;
    }
    file.close();
}

void fromFile(string filename){
    ifstream stream{filename + ".txt"};
    if(!stream){
        return;
    }
    string new_file = filename + "_v2.txt";

    ofstream new_stream{new_file};

    string line;

    int x = 1;
    string y = to_string(x);

    while(getline(stream, line)){
        new_stream << y << ": " << line << '\n'; 
        x++;
        y = to_string(x);
    }
}

int intToAscii(int number){
    return '0' + number;
}

void countChars(string filename){
    ifstream file{filename};

    if(!file){
        return;
    }
    char ch;

    int letters[26] = {0};

    while(file >> ch){
        if(tolower(ch) > 96 && tolower(ch) < 123){
            letters[tolower(ch) - 97]++;
        }
    }

    file.close();

    char y;

    for(int x{0}; x < 26; x++){
        y = x + 97;
        cout << y << ": " << letters[x] << '\n';
    }
}