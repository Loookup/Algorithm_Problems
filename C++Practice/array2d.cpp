#include <iostream>
using namespace std;

int main(){
    int rowsize, columnsize;
    cout << "Enter the size of row and column of matrix : " << endl;
    cin >> rowsize >> columnsize;

    int intArray1[rowsize][columnsize];
    //int* const intArray = new int[rowsize];

    int* sum_row = new int[rowsize];
    for(int i=0; i<rowsize; i++){
        sum_row[i] = 0;
        for(int j=0; j<columnsize; j++) {
            cin >> intArray1[i][j];
            sum_row[i] += intArray1[i][j];
        }
    }
    int* sum_column = new int[columnsize];
    for(int j=0; j<columnsize; j++){
        sum_column[j] = 0;
        for(int i=0; i<rowsize; i++){
            sum_column[j] += intArray1[i][j];
        }
    }
    for(int i=0; i<rowsize; i++) cout << sum_row[i] << '\t';
    cout << endl;
    for(int j=0; j<columnsize; j++) cout << sum_column[j] << '\t';
    cout << endl;

    delete [] sum_row;
    delete [] sum_column; // Do not forget to delete 'new' components
}