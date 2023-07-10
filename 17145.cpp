#include <iostream>
#include <vector>
#include <iterator>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>
using namespace std;

enum Result {Stand_by, Failed, Succeed, Impossible};

class Grid {
public:
    Grid () = default;
    Grid (size_t _Row_Size, size_t _Col_Size) : Row_Size(_Row_Size+2), Col_Size(_Col_Size+2) {
        std::vector <std::vector <int>> _Matrix;
        std::vector <int> barrier;
        for(int i=0; i<Col_Size; i++)
            barrier.push_back(1);
        _Matrix.push_back(barrier);
        for(int i=0; i<_Row_Size; i++){
            std::vector <int> Temp;
            Temp.push_back(1);
            for(int j=0; j<_Col_Size; j++){
                Temp.push_back(0);
            }
            Temp.push_back(1);
            _Matrix.push_back(Temp);
        }
        _Matrix.push_back(barrier);
        Matrix = _Matrix;
    }
    Grid (const Grid& _Grid) : Matrix(_Grid.Matrix), Row_Size(_Grid.Row_Size), Col_Size(_Grid.Col_Size), Start(_Grid.Start),
                               Process(_Grid.Process), Status(_Grid.Status) {};
    Grid operator = (const Grid& _Grid) { Matrix = _Grid.Matrix; Row_Size = _Grid.Row_Size; Col_Size = _Grid.Col_Size;
        Start = _Grid.Start; Process = _Grid.Process ;  Status= _Grid.Status;};
    Grid (const Grid&& _Grid) : Matrix(_Grid.Matrix), Row_Size(_Grid.Row_Size), Col_Size(_Grid.Col_Size), Start(_Grid.Start),
                                Process(_Grid.Process), Status(_Grid.Status) {};
    ~Grid() = default;
    int& operator[] (pair<int,int> index){
        return Matrix[index.first][index.second];
    }
    Grid Set(int r, int c, int idx){
        std::pair<int,int> _Start = make_pair(r,c);
        Matrix[r][c] = idx;
        Start = _Start;
        return *this;
    }
    friend std::string Outcome (Grid _Grid);
    friend void Move (Grid& _Grid, int idx);
    friend std::ostream& operator << (std::ostream& os, const Grid& _Grid);

private:
    std::vector <std::vector <int>> Matrix;
    size_t Row_Size;
    size_t Col_Size;
    pair<int,int> Start;
    std::vector <string> Process;
    Result Status;
};

std::ostream& operator << (std::ostream& os, const Grid& _Grid){

    for(auto& it : _Grid.Matrix) {
        std::copy(it.begin(), it.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
    return os;
}


std::vector <std::vector <int>> Input (int _Num_Q) {

    std::vector <std::vector <int>> Input;

    int input = 0;

    for(int i=0; i<_Num_Q; i++){

        std::vector <int> Temp_Input;

        for(int j=0; j<4; j++){

            std::cin >> input;

            Temp_Input.push_back(input);
        }

        Input.push_back(Temp_Input);
    }

    return Input;
}

std::vector <std::pair <Grid,int>> Create_Grid_Pair (std::vector <std::vector <int>> Grid_Cond, int Num){

    std::vector <std::pair <Grid, int>> Gridded;

    for(int i=0; i<Num; i++){

        auto Temp_Grid = new Grid(Grid_Cond[i][0], Grid_Cond[i][1]);

        Temp_Grid->Set(Grid_Cond[i][2], Grid_Cond[i][3], 1);

        std::pair <Grid, int> Temp_Grid_Pair = std::make_pair (*Temp_Grid, i);

        Gridded.push_back(Temp_Grid_Pair);

        delete Temp_Grid;
    }

    return Gridded;
}

void Move (Grid& _Grid, int idx) {

    _Grid.Status = Stand_by;

    int i = _Grid.Start.first, j = _Grid.Start.second;

    Result result = Stand_by;

    if(_Grid.Matrix[i+1][j] != 0 && _Grid.Matrix[i-1][j] != 0 && _Grid.Matrix[i][j+1] != 0 && _Grid.Matrix[i][j-1] != 0){ 

        if(idx == (_Grid.Row_Size-2)*(_Grid.Col_Size-2)+1)
            result = Succeed;
        else
            result = Failed;
        _Grid.Status = result;
    }
    else {

        string Index;

        int loop_move = 1;

        while (loop_move) {

            int i = _Grid.Start.first, j = _Grid.Start.second;

            int Deter = rand() % 4;

            switch (Deter) {

                case 0 : { // Up
                    i -= 1;
                    Index = "U";
                    break;
                }
                case 1 : { // Down
                    i += 1;
                    Index = "D";
                    break;
                }
                case 2 : { // Right
                    j += 1;
                    Index = "R";
                    break;
                }
                case 3 : { // Left
                    j -= 1;
                    Index = "L";
                    break;
                }
            }

            if(i < _Grid.Row_Size -1 && i >= 1 && j < _Grid.Col_Size -1 && j >= 1) {

                if (_Grid.Matrix[i][j] == 0) {
                    _Grid.Set(i,j, idx);
                    loop_move = 0;
                }
            }
        }
        _Grid.Process.push_back(Index);
    }
}

std::string Outcome (Grid _Grid){

    std::string ss = "0";

    std::vector <std::vector <std::string>> Compilation;

    int loop = 1;

    Result status = Stand_by;

    while(loop <= 50) {

        Grid Temp = _Grid;

        int idx = 1;

        while (status == Stand_by) {
            Move(Temp, idx + 1);
            status = Temp.Status;
            idx++;
        }

        auto find_it = std::find(Compilation.begin(), Compilation.end(), Temp.Process);

        if(find_it == Compilation.end()) {

            Compilation.push_back(Temp.Process);

            switch (status) {
                case Failed : break;

                case Succeed : {
                    for(auto it : Temp.Process)
                        cout << it;
                    cout << endl;
                    ss = "Succeed";
                    loop = 100;
                    break;
                }
            }
        }

        loop++;
        if(loop == 50)
            ss = "IMPOSSIBLE";
    }

    return ss;
}


int main(){

    srand((unsigned int) time(NULL));

    int Num_Q = 0;

    std::cin >> Num_Q;

    std::vector <std::vector <int>> Input_Vec = Input(Num_Q);

    std::vector <std::pair <Grid,int>> Grid_Vec = Create_Grid_Pair(Input_Vec, Num_Q);


    for (auto it: Grid_Vec) {
        int fail = 0;
        for (int i = 0; i <300; i++) {
            std::string result = Outcome(it.first);
            if (result == "Succeed") {
                break;
            }
            else
                fail++;
        }
        if(fail == 300){
            cout << "IMPOSSIBLE" << endl;
        }
    }
}
