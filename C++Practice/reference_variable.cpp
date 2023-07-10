#include <iostream>
using namespace std;

void swap(int& num1, int& num2) {
    int Temp = num1;
    num1 = num2;
    num2 = Temp;
}



int main() {
    int m, n;
    std::cin >> m >> n;
    swap(m, n);
    std::cout << m << " " << n;
}