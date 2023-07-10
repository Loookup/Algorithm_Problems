#include <iostream>
#include <string>
using namespace std;

enum TYPE {INT=0, LONG, FLOAT, DOUBLE};

TYPE getType(std::string type) {
    int value =0;
    if (type == "int") {return INT;}
    else if (type == "long") {return LONG;}
    else if (type == "float") {return FLOAT;}
    else if (type == "double"){return DOUBLE;}
}

int main() {
    std::string str;
    std::cin >> str;
    TYPE type = getType(str);
    switch (type) {
        case INT:
            std::cout << "INT(" << type << ")" << std::endl;
            break;
        case LONG:
            std::cout << "LONG(" << type << ")" << std::endl;
            break;
        case FLOAT:
            std::cout << "FLOAT(" << type << ")" << std::endl;
            break;
        case DOUBLE:
            std::cout << "DOUBLE(" << type << ")" << std::endl;
            break;
    }
    return 0;
}
