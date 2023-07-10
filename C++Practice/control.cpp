#include <iostream>
#include <algorithm>
#include <map>
#include <string>
#include <vector>
#include <regex>
using namespace std;

int main(){

    vector<string> vec;
    string str;

    while(cin >> str && str!="^"){
        if(str == "EOF") break;
        else {
            auto filtered{std::regex_replace(str, std::regex("[.|,|:|;| ]"), "")};
            vec.push_back(filtered);
        }
        //vec.push_back(str);
    }

    map <string,size_t> words;
    for (auto& it : vec){
        ++words[it];
    }

    cout << "words : " << words.size() << endl;


    //vector <string> sear_vec;

    ;

    while(cin >> str){
        if(str == "QUIT") {
            cout << "Bye!";
            break;
        }
        else {
            cout << str <<": " << words[str] << endl;
        }
    }
    return 0;
}