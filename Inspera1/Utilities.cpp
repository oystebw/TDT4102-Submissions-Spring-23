#include "Utilities.h"

string toGreek(string sentence)
{
    // BEGIN: 2a

    string greek;

    for(auto el: sentence){
        greek += el + 2;
    }
    return greek;
    
    // END: 2a
}

vector<vector<string>> loadSvada()
{
    // BEGIN: 2b

    ifstream file{"SvadaWords.txt"};
    vector<vector<string>> master;
    vector<string> slave;
    string line;

    while(getline(file, line)){
        if(!isalpha(line[0])){
            master.push_back(slave);
            slave.clear();
        }
        else{
            slave.push_back(line);
        }
    }
    slave.push_back(line);
    master.push_back(slave);

    return master;

    // END: 2b
}

string svadaGenerator(vector<vector<string>> svadaVec)
{
    // BEGIN: 2c1

    string svada;
    int idx;
    for(int x{0}; x < svadaVec.size(); x++){
        idx = randint(0, svadaVec[x].size());
        svada += svadaVec[x][idx];
    }
    return svada;
    
    // END: 2c1
}