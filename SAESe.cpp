/**
 * CIS4362
 * Intro to Cryptology
 * Ex4 - SAESe
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

    ///Encrypt shit

    for(int j = 0; j < blocks.size(); j+=3){

        string t1;
        string t2;
        string t3;

        ///First time whiten
        t1 = sum(keys[0],blocks[j]);
        t2 = sum(keys[1],blocks[j+1]);
        t3 = sum(keys[2],blocks[j+2]);

        int pos = 3;

        for(int i = 1; i <= numRounds; i++) {

            ///Sub
            sub(t1);
            sub(t2);
            sub(t3);

            ///Shift
            shift(t1, t2, t3);

            ///Mix
            if(i != numRounds){
                mix(t1);
                mix(t2);
                mix(t3);
            }

            ///Whiten
            t1 = sum(t1, keys[pos]);
            t2 = sum(t2, keys[pos+1]);
            t3 = sum(t3, keys[pos+2]);

            pos += 3;
        }
        output.append(t1);
        output.append(t2);
        output.append(t3);
    }

    printResult(output, true);

    return 0;
}