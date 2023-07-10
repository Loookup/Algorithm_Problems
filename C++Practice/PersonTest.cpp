#include <iostream>
#include "Person.h"
#include <map>
#include <vector>
#include <algorithm>
using namespace std;


int main() {

    int N;
    cin >> N;

    map <string, Person> persons;

    while( N--> 0){

        string name, number;

        cin >> name >> number;

        Person person (name,number);

        //auto find_it = persons.find(name);

        //if(find_it != persons.end()) {
            pair <string, Person> data = {name, person};
            persons.insert(data);
        //}

        //else
           // cout << "Enter other names" << endl;

    }

    int limit = 10;

    while(limit --> 0) {

        string control;

        cin >> control;

        auto command = getCommand(control);

        switch (command) {

            case ADD : {

                string name, number;

                cin >> name >> number;

                Person person(name, number);

                //auto find_it = persons.find(name);

                //if (find_it != persons.end()) {
                    pair<string, Person> data = {name, person};
                    persons.insert(data);
               // } else
                    //cout << "Enter other names" << endl;


                break;
            }

            case DEL : {
                string name;
                cin >> name;

                auto remove_it = persons.erase(name);

                break;
            }

            case MOD : {

                string name, number;

                cin >> name >> number;

                persons.at(name).modifyNumber(number);

                break;

            }

            case FIN : {

                string name;

                cin >> name;

                persons.at(name).print();

                break;

            }

            case QUI : {

                for(auto& i : persons){
                    i.second.print();
                }

                limit = 0;
                break;
            }

            case Invalid : {
                std::cout << "Invalid Command" << endl;
            }

        }


    }










}
