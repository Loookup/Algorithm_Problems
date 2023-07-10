//
// Created by 이철용 on 2022/07/07.
//

#include "String.h"
#include <cstring>
#include <iostream>

// int len;
//    char* s;

String::String() {
    len = 0;
    s = new char[len+1];
    s[len] = '\0';
}

String::String(const char* str) {
    len = strlen(str);
    s = new char[len+1];
    std::copy(str,str+len,s);
    s[len] = '\0';
}

String::String(const String& str){
    len = str.len;
    s = new char[len+1];
    std::copy(str.s,str.s+len,s);

}

String& String::operator=(const String& str){ // copy

    if(s == str.s)
        return *this;
    else {
        String tmp(str);
        String::swap(tmp);
        return *this;
    }

}

String::~String() {
    if(s)
        delete [] s;
}

const char* String::data() const {

    return s;

}

char& String::at(size_t pos) {

    if(len!=0 && 0<= pos && pos < len)
        return s[pos];
}

size_t String::size() const{

    return len;


}

void String::print(const char* str) const{

    std::cout << str << ": " << s << ", size: " << len << std::endl;

}

void String::swap(String& str) {

    std::swap(str.s,s);
    std::swap(str.len,len);

}