#include "ContractDataBase.h"

InsuranceContract ContractDataBase::getContract(int id)
{
    // BEGIN: 1b

    for(auto& contract: contracts){
        if(contract.getId() == id){
            return contract;
        }
    }

    // END: 1b

    // Returning an empty contract if no contract with the given id is found.
    return InsuranceContract{};
}

int ContractDataBase::numberOfInsuranceType(InsuranceType type)
{
    // BEGIN: 1c

    int total{0};
    for(auto& contract: contracts){
        if(contract.getInsuranceType() == type){
            total++;
        }
    }
    return total;

    // END: 1c
}

int ContractDataBase::addContract(string holderName, InsuranceType insType, int value)
{
    // BEGIN: 1d 
    int id{1};

    if(contracts.size()){
        id += contracts.back().getId();
    }
    contracts.emplace_back(holderName, insType, value, id);

    return id;

    // END: 1d
}

void ContractDataBase::saveContracts(string filename)
{
    // BEGIN: 1e

    ofstream file{filename};

    for(auto& contract: contracts){
        file << contract.getHolder() << ',' << insuranceTypeToString(contract.getInsuranceType()) << ',' << to_string(contract.getValue())
        << ',' << to_string(contract.getId()) << ',' << contract.getInsuranceText() << '\n';
    }
    file.close();

    // END: 1e
}

void ContractDataBase::loadContracts(string filename)
{
    ifstream inFile{filename};
    if (!inFile)
    {
        error("Couldn't open file: ", filename);
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss{line};
        char seperator;

        string holderName;
        getline(ss, holderName, ',');

        string insType;
        getline(ss, insType, ',');

        int value;
        ss >> value;
        ss >> seperator;

        int id;
        ss >> id;
        ss >> seperator;

        string insuranceText;
        getline(ss, insuranceText, ',');

        contracts.push_back({holderName, stringToInsuranceType.at(insType), value, id, insuranceText});
    }
}
