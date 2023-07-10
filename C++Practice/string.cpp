#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

int main(){
    string str;
    cin >> str;
    auto len = str.length();

    string alphabet = "abcdefghijklmnopqrstuvwxyz";
    int zeroArr [26] = {0};
    for (int i=0; i<26; i++){
        auto find1 = find(begin(str), end(str),alphabet[i]);
        //cout << *find1 << '\t';
        //cout << distance(begin(str),find1) <<endl;
        if(*find1 != 0){
            zeroArr[i] = distance(begin(str),find1) + 1;
            /*for (int j=0; j<len; j++){
                auto find2 = find(begin(str), begin(str)+j, alphabet[i]);
                if(*find2 != 0){
                    zeroArr[i] = j;
                }
            }*/
        }
    }

    for (int i=0; i<26; i++) cout << zeroArr[i]<< '\t';
}