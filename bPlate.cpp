/**
 * CIS4362
 * Intro to Cryptology
 * Ex4 - Boiler Plate Code
 * Samuel Reina
 * 11/17/2020
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

char v[37] = {'a','b','c','d','e','f','g','h','i','j','k','l','m',
              'n','o','p','q','r','s','t','u','v','w','x','y','z',
              '0','1','2','3','4','5','6','7','8','9','.'};


int getVocabPos(char c){

    for(int i = 0; i < 37; i++){
        if(tolower(c) == v[i])
            return i;
    }

    return -1;
}

string rotateUp(string s){

    string toRet;
    char c = s.at(0);

    for(int i = 1; i < s.length(); i++)
        toRet.push_back(s.at(i));

    toRet.push_back(c);
    return toRet;
}

void sub(string &s){

    for(int i = 0; i < s.length(); i++)
        s[i] = v[ (getVocabPos(s[i])*13 + 17) % 37];

}

void unsub(string &s){

    for(int i = 0; i < s.length(); i++){
        int temp = (20*(getVocabPos(s[i]) - 17)) % 37;

        if(temp < 0)
            temp+=37;

        s[i] = v[temp];
    }


}

string sum(string &x, string &y){

    string toRet;
    for(int i = 0; i < x.length(); i++){
        int temp = (getVocabPos(x.at(i)) + getVocabPos(y.at(i))) % 37;
        toRet.push_back(v[temp]);
    }

    return toRet;
}

string unsum(string &x, string &y){

    string toRet;
    for(int i = 0; i < x.length(); i++){
        int temp = (getVocabPos(x.at(i)) - getVocabPos(y.at(i))) % 37;

        if(temp < 0)
            temp += 37;

        toRet.push_back(v[temp]);
    }

    return toRet;
}

string generate(vector<string> &x, string &c){
    string temp = rotateUp(x[x.size()-1]); //i-1
    sub(temp);
    temp = sum(temp, c); // i-3
    temp = sum(temp, x[x.size()-3]);
    return temp;
}

string sanitize(string &x){

    string toRet;
    for(int i = 0; i < x.length(); i++){

        char c = x.at(i);
        if(isalnum(c) ||  c == '.')
            toRet.push_back(c);
    }

    return toRet;
}

void pad9(string &x){
    while(x.length() % 9 != 0)
        x += 'x';
}

vector<string> block9(string &x){
    vector<string> toRet;
    int pos = 0;

    while(pos != x.length()){
        toRet.push_back(x.substr(pos, 3));
        pos+=3;
        toRet.push_back(x.substr(pos, 3));
        pos+=3;
        toRet.push_back(x.substr(pos, 3));
        pos+=3;
    }

    return toRet;
}

void shift(string &x, string &y, string &z){

    string temp1;
    string temp2;
    string temp3;

    temp1.push_back(x[0]);
    temp1.push_back(y[1]);
    temp1.push_back(z[2]);

    temp2.push_back(y[0]);
    temp2.push_back(z[1]);
    temp2.push_back(x[2]);

    temp3.push_back(z[0]);
    temp3.push_back(x[1]);
    temp3.push_back(y[2]);

    x = temp1;
    y = temp2;
    z = temp3;
}

void unshift(string &x, string &y, string &z){

    string temp1;
    string temp2;
    string temp3;

    temp1.push_back(x[0]);
    temp1.push_back(z[1]);
    temp1.push_back(y[2]);

    temp2.push_back(y[0]);
    temp2.push_back(x[1]);
    temp2.push_back(z[2]);

    temp3.push_back(z[0]);
    temp3.push_back(y[1]);
    temp3.push_back(x[2]);

    x = temp1;
    y = temp2;
    z = temp3;
}

void mix(string &s){

    string temp;

    int t1 = ( getVocabPos(s[0])*1 + getVocabPos(s[1])*3 + getVocabPos(s[2])*5) % 37;
    int t2 = ( getVocabPos(s[0])*7 + getVocabPos(s[1])*11 + getVocabPos(s[2])*13) % 37;
    int t3 = ( getVocabPos(s[0])*17 + getVocabPos(s[1])*19 + getVocabPos(s[2])*23) % 37;

    s[0] = v[t1];
    s[1] = v[t2];
    s[2] = v[t3];

}

void unmix(string &s){

    string temp;

    int t1 = ( getVocabPos(s[0])*29 + getVocabPos(s[1])*27 + getVocabPos(s[2])*9) % 37;
    int t2 = ( getVocabPos(s[0])*31 + getVocabPos(s[1])*21 + getVocabPos(s[2])*20) % 37;
    int t3 = ( getVocabPos(s[0])*35 + getVocabPos(s[1])*19 + getVocabPos(s[2])*1) % 37;

    s[0] = v[t1];
    s[1] = v[t2];
    s[2] = v[t3];

}

void printResult(string &s, bool upper){

    int pos = 0;

    if(upper){
        for(int i = 0; i < s.length(); i++){
            s[i] = toupper(s[i]);
        }
    }

    for(pos; pos < s.length(); pos+=5){
        string temp = s.substr(pos,5);
        cout << temp << " ";
    }

    cout << endl;

}

//cout << getVocabPos(keys[pos-2][0]) << " " << getVocabPos(keys[pos-1][0]) << " " << getVocabPos(keys[pos][0]) << endl;
//cout << getVocabPos(keys[pos-2][1]) << " " << getVocabPos(keys[pos-1][1]) << " " << getVocabPos(keys[pos][1]) << endl;
//cout << getVocabPos(keys[pos-2][2]) << " " << getVocabPos(keys[pos-1][2]) << " " << getVocabPos(keys[pos][2]) << endl << endl;

/*cout << getVocabPos(t1[0]) << " " << getVocabPos(t2[0]) << " " << getVocabPos(t3[0]) << endl;
            cout << getVocabPos(t1[1]) << " " << getVocabPos(t2[1]) << " " << getVocabPos(t3[1]) << endl;
            cout << getVocabPos(t1[2]) << " " << getVocabPos(t2[2]) << " " << getVocabPos(t3[2]) << endl << endl;*/