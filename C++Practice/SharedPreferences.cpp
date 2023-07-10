//
// Created by 이철용 on 2022/07/05.
//

#include "SharedPreferences.h"

static SharedPreferences& getInstance(){

    static SharedPreferences  ;

    return sharedPreferences;

};

void putInt(std::string key, int value){



};

int getInt(std::string key){

};

size_t size();
