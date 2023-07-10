//
// Created by 이철용 on 2022/06/29.
//

#include <iostream>

#include <vector>

#include <string>

#include <iterator>

#include <cmath>

using namespace std;

struct Student {

    Student(string name, float gpa) : name{name}, gpa{gpa} {}

    string name;

    float gpa;

};

//Student* getStudent();


shared_ptr<Student> getStudent(){


    string name;

    float gpa;

    cin >> name >> gpa;

    auto student = shared_ptr <Student> (new Student(name,gpa));

    student -> name = name;

    student -> gpa = gpa;

    return student;

};

void print(const vector<shared_ptr<Student>>& students){

    for(auto& i : students){
        cout << "Name: " << i->name << ", " << "GPA: " << i->gpa  << endl;
    }

};

float getAverage(const vector<shared_ptr<Student>> &students, int no){

    float sum = 0.0;

    for(auto& i : students){
        sum += i->gpa;
    }

    float average = floor((sum / no)*10) / 10;



    return average;

};


void plusGPA(const vector<shared_ptr<Student>>& students, float bonus){

    for(auto& i : students){

        i -> gpa += bonus;

    }

};

int main() {

    cout << "Enter the # of students: ";

    int no;

    cin >> no;



    vector<shared_ptr<Student>> students;



    for (int i = 0; i < no; i++) {

        auto student = getStudent();

        students.emplace_back(student);

    }

    print(students);

    float average = getAverage(students, no);

    cout << "GPA Average: " << average << endl;



    plusGPA(students, 1);



    print(students);

    average = getAverage(students, no);

    cout << "GPA Average: " << average << endl;



    return 0;

}
