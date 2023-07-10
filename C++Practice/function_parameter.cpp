#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <memory>
#include <regex>
using namespace std;

struct Champion {
    std::string name;
    int health;
    int attack;
};

//auto findChampionMoreThanHealth(std::vector<Champion> champions, int health);
//auto findChampionMoreThanAttack(std::vector<Champion> champions, int attack);
auto findChampionWithCondition(std::vector<Champion> champions, std::function<bool(Champion)> condition) {

    std::vector<Champion> result;
    for (auto& c : champions)
        if(condition(c))
            result.push_back(c);
    return result;

};

static int idx;

std::function<bool(Champion)> condition_health = [](Champion c){return c.health>idx;};
std::function<bool(Champion)> condition_attack = [](Champion c){return c.attack>idx;};



void printChampion(std::vector<Champion> champions){

    for (auto& i : champions)
        cout << i.name <<" " << i.health <<" " <<i.attack <<" " << endl;

};

std::vector<Champion> createChampion() {
    std::vector<Champion> champions;
    Champion tryndamere {"Tryndamere", 625, 72};
    Champion kled {"Kled", 740, 35};
    Champion garen {"Garen", 620, 66};
    champions.push_back(tryndamere);
    champions.push_back(kled);
    champions.push_back(garen);
    return champions;
}

int main(){

    vector champions = createChampion();

    string str;

    cin >> str;

    auto filtered {std::regex_replace(str, std::regex("[:]"), "")};

    string cond_str, cond_idx;

    for (auto& i :filtered){
        if(i  >= 65 && i <= 122)
            cond_str.push_back(i);
        else
            cond_idx.push_back(i);
    }

    idx = stoi(cond_idx);

    vector <Champion> result;

    if(cond_str == "health"){

        result = findChampionWithCondition (champions, condition_health);
        printChampion(result);

    }
    else if(cond_str == "attack"){

        result = findChampionWithCondition (champions, condition_attack);
        printChampion(result);
    }
    else{

        cout << "Invalid Command" << endl;

    }

}
