/**
 * CIS4362
 * Intro to Cryptology
 * Ex4 - SAESd
 * Samuel Reina
 * 11/17/2020
 */

#include "bPlate.cpp"

using namespace std;

int main(int argc, char* argv[]) {

    if (argc != 3) {
        cerr << "Not enough arguments" << endl;
        return -1;
    }

    int numRounds = 0;
    string mKey;

    ///Check validity of command line input
    try {
        double temp = stod(argv[1]);
        int temp2 = (int) temp;
        bool s = (temp == temp2);

        if (!s) {
            cerr << "Invalid number of rounds" << endl;
            return -1;
        }

        numRounds = temp2;

    } catch (invalid_argument &e) {
        cerr << "Invalid number of rounds" << endl;
        return -1;
    }

    if (numRounds < 2 || numRounds > 10) {
        cerr << "Invalid number of rounds" << endl;
        return -1;
    }

    ///Master key
    mKey = argv[2];

    if(mKey.length() != 9){
        cerr << "Invalid master key" << endl;
        return -1;
    }

    ///Check validity of key inputted
    for (int i = 0; i < 9; i++) {
        char c = mKey.at(i);
        if (!isalnum(c) && c != '.') {
            cerr << "Invalid master key" << endl;
            return -1;
        }
    }

    vector<string> keys;
    keys.push_back(mKey.substr(0,3));
    keys.push_back(mKey.substr(3,3));
    keys.push_back(mKey.substr(6,3));

    for(int i = 0; i < numRounds; i++){
        keys.push_back(generate(keys, keys[i]));
        keys.push_back(sum(keys[i*3+1], keys[i*3+3]));
        keys.push_back(sum(keys[i*3+2], keys[i*3+4]));

    }

    string input = "";
    string temp;

    while(getline(cin, temp)){
        temp = sanitize(temp);
        input += temp;
    }

    pad9(input);
    vector<string> blocks = block9(input);
    string output;

    ///Decrypt shit

    for(int j = 0; j < blocks.size(); j+=3){

        string t1 = blocks[j];
        string t2 = blocks[j+1];
        string t3 = blocks[j+2];

        int pos = keys.size()-1;

        for(int i = numRounds; i > 0; i--) {

            ///Unsum
            t1 = unsum(t1, keys[pos-2]);
            t2 = unsum(t2, keys[pos-1]);
            t3 = unsum(t3, keys[pos]);

            ///Unmix
            if(i != numRounds){
                unmix(t1);
                unmix(t2);
                unmix(t3);
            }

            ///Shift
            unshift(t1, t2, t3);

            ///Unsub
            unsub(t1);
            unsub(t2);
            unsub(t3);

            pos -= 3;
        }

        ///Unsum
        t1 = unsum(t1, keys[pos-2]);
        t2 = unsum(t2, keys[pos-1]);
        t3 = unsum(t3, keys[pos]);

        output.append(t1);
        output.append(t2);
        output.append(t3);
    }

    printResult(output, false);

    return 0;
}