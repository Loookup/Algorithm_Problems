#include <iostream>
#include <string>
#include <vector>
#include <memory>
using namespace std;

struct STUDENT {

    std::string name;

    int age;

};



std::unique_ptr<STUDENT> createStudent (std::string name, int age) {

    auto student = std::unique_ptr<STUDENT> (new STUDENT());

    student->name = name;

    student->age = age;

    return student;

}



void printStudentInfo(const STUDENT& student){

    std::cout << student.name << " " << student.age << std::endl;

}


int main(){

    int num;
    cin >> num;

    STUDENT WholeStudent[num];

    for(int i=0; i <num; i++){

        string name;

        int age;

        cin >> name >> age;


        auto stu = createStudent(name,age);

        WholeStudent[i] = *stu;

    }

    for(auto& i : WholeStudent){
        cout << i.name << " " << i.age << endl;
    }


}
