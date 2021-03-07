/**
 * CIS4362
 * Intro to Cryptology
 * Ex4 - genKeys
 * Samuel Reina
 * 11/17/2020
 */

#include "bPlate.cpp"

int main(int argc, char* argv[]){

    if(argc < 2){
        cerr << "Missing number of rounds" << endl;
        return -1;
    }

    int numRounds = 0;
    string input;


    ///Check validity of command line input
    try{
        double temp = stod(argv[1]);
        int temp2 = (int)temp;
        bool s = (temp == temp2);

        if(!s){
            cerr << "Invalid number of rounds" << endl;
            return -1;
        }

        numRounds = temp2;

    }catch(invalid_argument &e){
        cerr << "Invalid number of rounds" << endl;
        return -1;
    }

    if(numRounds < 2 || numRounds > 10){
        cerr << "Invalid number of rounds" << endl;
        return -1;
    }

    ///Take user input (master key)
    getline(cin, input);
    input = input.substr(0,9);

    ///Check validity of key inputted
    for(int i = 0; i < 9; i++){
        char c = input.at(i);
        if( !isalnum(c) && c != '.'){
            cerr << "Invalid master key" << endl;
            return -1;
        }
    }

    vector<string> keys;
    keys.push_back(input.substr(0,3));
    keys.push_back(input.substr(3,3));
    keys.push_back(input.substr(6,3));

    for(int i = 0; i < numRounds; i++){
        keys.push_back(generate(keys, keys[i]));
        keys.push_back(sum(keys[i*3+1], keys[i*3+3]));
        keys.push_back(sum(keys[i*3+2], keys[i*3+4]));

    }

    for(int i = 0; i < keys.size(); i+=3){
        cout << keys[i] << keys[i+1] << keys[i+2] << endl;
    }

    return 0;
}

