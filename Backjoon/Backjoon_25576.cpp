#include <iostream>
#include <stdio.h>
#include <vector>
using namespace std;


int main() {

    int N = 0, M = 0;

    scanf("%d %d", &N, &M);

    int temp = 0;

    std::vector <int> Ralpa;

    for(int i  = 0; i < M; i++) {
        scanf("%d", &temp);
        Ralpa.push_back(temp);
    }

    int Bad = 0, Good = 0;

    for(int i = 0; i < N - 1; i++){ // except Ralpa

        int Differ = 0;

        for(int j = 0; j < M; j++) {
            scanf("%d", &temp);
            Differ += abs(Ralpa[j] - temp);
        }

        if(Differ > 2000)
            Bad += 1;
        else
            Good += 1;
    }
    
    if(Bad >= N/2)
        printf("%s", "YES");
    else
        printf("%s", "NO");
}
