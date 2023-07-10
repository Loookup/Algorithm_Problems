#include <cstring>
#include <iostream>
#include "String.h"

void printString(const String s){
    s.print("printString");
}

String createName(){
    String name{"Kim"};
    return name;
}

int main(){
    String s1;
    s1.print("s1");

    String s2 = "abc";
    s2.print("s2");

    String s3 {"def"};
    s3.print("s3");

    String s4 = s3;
    s4.print("s4");

    String s5;
    s5 = s4;   //problem: the data points to the same address
    //s5 = "abc";
    s5.print("s5");

    s4.at(1) = 'E';
    s4.print("s4");
    s5.print("s5");

    printString("hij");
    printString(s2);  // shallow copy ??

    String s6 = createName();
    s6.print("s6");

    String s7;
    s7 = createName();
    s7.print("s7");


    String s8 {s7};
    std::cout << std::strcmp(s7.data(), s8.data()) << std::endl;
    s7.at(1) = 'a';
    std::cout << std::strcmp(s7.data(), s8.data()) << std::endl;
    s8 = s8;
}