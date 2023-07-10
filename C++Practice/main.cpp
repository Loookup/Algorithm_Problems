#include <iostream>

#include <vector>

#include <string>

using namespace std;



struct Student {

    Student(string name, float gpa) : name{name}, gpa{gpa} {}

    string name;

    float gpa;

};

//Student* getStudent();



shared_ptr<Student> getStudent();

void print(const vector<shared_ptr<Student>>& students);

float getAverage(const vector<shared_ptr<Student>> &students, int no);

void plusGPA(const vector<shared_ptr<Student>>& students, float bonus);



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