//
// Created by 이철용 on 2022/06/28.
//
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <numeric>
#include <memory>
#include "student.h"
using namespace std;

/*const int SUBJECT_NO = 3;



struct StudentInfo {

    std::string name;

    int scores[SUBJECT_NO];

    int sum;

    double average;

};*/


unique_ptr<StudentInfo> make_student(){


    vector <StudentInfo> vec;
    int sum;
    string name;

    for (auto i=vec.begin(); i != vec.end(); i++){
        cout << "Enter the " << *i+1 << "th Student" << endl;
         cin >> name;
         vec.insert(begin(vec),name);
         sum=0;
         for(int j=0; j<SUBJECT_NO; j++) {
             int scores;
             cin >> scores;
             st[i].scores[j] = scores;
             sum += scores;
         }
         st[i].sum = sum;
         double aver = double(sum)/3;
         st[i].average = aver;
         //cout << aver << endl;

    }
}

void print(const StudentInfo& si) {

    cout << si.name << '\t';
    for(int i=0; i<SUBJECT_NO; i++) cout << si.scores[i] << '\t';
    cout << si.sum << '\t' << si.average << endl;

}

void print_all(const vector<unique_ptr<StudentInfo>>& vec) {

    //for(auto i= vec.begin(); i != vec.end(); ++i)
      //  cout << *i << '\t';
}

