//
// Created by 이철용 on 2022/07/07.
//
//Logger.cpp ------------------------------

#include <iostream>
#include "Logger.h"
void printTicketInfo(std::string className, long size) {
    std::cout << "# of tickets in " << className << ": " << size<< std::endl;
}