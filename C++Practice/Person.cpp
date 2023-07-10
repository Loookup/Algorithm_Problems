//
// Created by 이철용 on 2022/07/04.
//

//Person.cpp (개별 멤버 함수를 구현하시오)

#include "Person.h"

Person::Person(std::string name, std::string number) {

    this->name = name;

    this ->number = number;

    // your code here
}

void Person::modifyNumber(std::string number) {

    this -> number = number;
    // your code here
}

void Person::print() const {

    std::cout << this->name << " " << this->number << std::endl;
    // your code here
}


Command getCommand (std::string str) {

    if     (str == "ADD") {return ADD;}
    else if(str == "DEL") {return DEL;}
    else if(str == "MOD") {return MOD;}
    else if(str == "FIN") {return FIN;}
    else if(str == "QUI") {return QUI;}
    else                  {return Invalid;}

}
