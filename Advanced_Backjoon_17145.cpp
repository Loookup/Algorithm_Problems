/*
 * This Code tells us Input Matrix is cover-able or not, and if it is cover-able, this figure out trace
 *
 * Goal : 1. Figure out Trace randomly determined ( Guarantee Object's autonomy)
 *        2. Minimize Calculating Time - Optimal Logic
 *        3. Sorting Cases
 *        4. Manifest actual Cleaning Robot's motion
 */


#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>
using namespace std;

enum Result {Stand_by, Failed, Succeed, Invalid};
enum Case {OddxOdd, OddxEven, EvenxOdd, EvenxEven};
enum Motion {Up, Down, Left, Right};

/*
 * Make Object 'Fenced' Because if we fenced outside of Input Matrix, it is easy to find out it reach edge of Matrix
 * Implements Object 'Area' from Real World
 */

class Fenced {
public:
    Fenced () = default;
    Fenced (size_t _Row_Size, size_t _Col_Size) : Row_Size(_Row_Size+2), Col_Size(_Col_Size+2) { // Constructor
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
        End_Pos = pair (0,0);
    }
    Fenced (const Fenced& _Fenced) : Matrix(_Fenced.Matrix), Row_Size(_Fenced.Row_Size), Col_Size(_Fenced.Col_Size), Pos(_Fenced.Pos), // Copy Constructor
                               Process(_Fenced.Process), Status(_Fenced.Status), TYPE(_Fenced.TYPE), End_Pos(_Fenced.End_Pos) {};
    Fenced operator = (const Fenced& _Fenced) { Matrix = _Fenced.Matrix; Row_Size = _Fenced.Row_Size; Col_Size = _Fenced.Col_Size; // Copy Semantics
        Pos = _Fenced.Pos; Process = _Fenced.Process ;  Status= _Fenced.Status; TYPE=_Fenced.TYPE; End_Pos=_Fenced.End_Pos;
        return *this;
    };
    Fenced (const Fenced&& _Fenced) : Matrix(_Fenced.Matrix), Row_Size(_Fenced.Row_Size), Col_Size(_Fenced.Col_Size), Pos(_Fenced.Pos), // Move Constructor
                                Process(_Fenced.Process), Status(_Fenced.Status), TYPE(_Fenced.TYPE), End_Pos(_Fenced.End_Pos){};
    Fenced operator = (const Fenced&& _Fenced) {
        cout << "Move Semantics" << endl;
        Matrix = _Fenced.Matrix;
        Row_Size = _Fenced.Row_Size;
        Col_Size = _Fenced.Col_Size;
        Pos = _Fenced.Pos;
        Process = _Fenced.Process;
        Status = _Fenced.Status;
        TYPE = _Fenced.TYPE;
        End_Pos = _Fenced.End_Pos;
        return *this;
    };
    ~Fenced() = default; // Destructor
    int& operator[] (pair<int,int> index){
        return Matrix[index.first][index.second];
    }
    Fenced Current_Pos_Set(int r, int c, int idx){ // Set Current Position and Check Current Status
        std::pair<int,int> _Pos = make_pair(r,c);
        Matrix[r][c] = idx;
        Pos = _Pos;
        return *this;
    }
    friend void Transcendence (std::vector <pair < vector <string> , std::vector <Fenced>>> _Phase);
    friend std::vector <pair < std::vector <string> , vector <Fenced>>> Phased_Fenced (Fenced _Fenced);
    friend Case Case_Deter (Fenced _Fenced);
    friend void Outcome (Fenced _Fenced);
    friend void Move (Fenced& _Fenced, int idx);
    friend std::ostream& operator << (std::ostream& os, const Fenced& _Fenced);

private:
    std::vector <std::vector <int>> Matrix;
    size_t Row_Size;
    size_t Col_Size;
    pair<int,int> Pos;
    std::vector <string> Process;
    Result Status;
    Case TYPE;
    pair <int,int> End_Pos; // Outside of Matrix
};

std::ostream& operator << (std::ostream& os, const Fenced& _Fenced){

    for(auto& it : _Fenced.Matrix) {
        std::copy(it.begin(), it.end(), std::ostream_iterator<int>(std::cout, " "));
        std::cout << std::endl;
    }
    return os;
}

// Receive Matrix Type and Sort Input Matrix is Cover-able or not, and classify ' Phase ' with it is Dividable or not with 2X2 Unit Matrix

std::vector < pair <std::vector <string> , std::vector <Fenced>>> Phased_Fenced (Fenced _Fenced) { // Solution, Sectional Area

    std::vector < pair <std::vector <string> , std::vector <Fenced>>> Phase;

    if(_Fenced.Row_Size > 5 && _Fenced.Col_Size > 5) { // If Fenced out of designated size

        int Row_index = _Fenced.Row_Size - 2, Col_index = _Fenced.Col_Size - 2;

        Fenced Low_Level_Fenced = _Fenced;

        while (Row_index > 3 && Col_index > 3) {

            cout << "Phase sorting" << std::endl;

            std::vector<Fenced> Sectioned_Fenced;

            Case _Case = Case_Deter(Low_Level_Fenced);

            switch (_Case) {

                case EvenxEven : {

                    cout << "Even and Even Case" << endl;

                    Fenced High_Level_Fenced (2,2);

                    int Divided_Row = Row_index / 2, Divided_Col = Col_index / 2;

                    int R = Low_Level_Fenced.Pos.first - 1;

                    int C = Low_Level_Fenced.Pos.second - 1;

                    int R2 = R / Divided_Row;
                    int C2 = C / Divided_Col;

                    cout << R2 << " " << C2 <<endl;

                    High_Level_Fenced.Current_Pos_Set(R2 + 1, C2 + 1, 1);

                    Outcome(High_Level_Fenced);

                    cout <<"Result : "<< endl;

                    for(auto it : High_Level_Fenced.Process)
                        cout <<it;

                    cout <<endl;

                    Fenced Temp(Divided_Row, Divided_Col);

                    for(int i = 0; i < 4; i++)
                        Sectioned_Fenced.push_back(Temp);

                    int Cur_Pos_Row = (R % Divided_Row) + 1;
                    int Cur_Pos_Col = (C % Divided_Col) + 1;

                    cout << Cur_Pos_Row << " " << Cur_Pos_Col << endl;

                    Sectioned_Fenced[0].Current_Pos_Set(Cur_Pos_Row,Cur_Pos_Col, 1);

                    Low_Level_Fenced = Sectioned_Fenced[0];

                    auto Pair_Temp = std::make_pair(High_Level_Fenced.Process, Sectioned_Fenced);

                    Phase.insert(Phase.begin(),Pair_Temp);

                    cout << "Copy Complete" << endl;

                    Row_index = Divided_Row, Col_index = Divided_Col;

                    break;
                }

                default : {
                    cout << "Error" << endl;
                    break;
                }
            }
        }
    }
    else { // R and C is Lower than 4

        std::vector <Fenced> Fenced_Temp;

        Fenced_Temp.push_back(_Fenced);

        Outcome(_Fenced);

        auto Pair_Temp = std::make_pair(_Fenced.Process, Fenced_Temp);

        Phase.push_back(Pair_Temp);
    }

    cout << "Phase Close" << endl;

    return Phase;
}

// Move beyond Phase, So it calls Transcendence

void Transcendence (std::vector <pair < vector <string> , std::vector <Fenced>>> _Phase) { // Fenced Vector is 2X2 size

    for(auto& iter : _Phase){ // First is Procedure and Second is Divided 'Fenced'

        std::vector <std::vector <string>> Whole_Process;

        for(int i = 0; i < 3; i++) {

            cout << i << "th Trans check point : " << endl;

            auto Motion = iter.first[i];

            cout << "GO " <<endl;

            std::vector <string> elements;

            if (Motion == "U"){

                while(iter.second[i].End_Pos.first != 1)
                    Outcome(iter.second[i]);

                cout << "Up sequence" << endl;

                int Transcend = iter.second[i].End_Pos.second;

                iter.second[i+1].Current_Pos_Set(iter.second[i].Row_Size-2,Transcend,1);
            }
            else if (Motion == "D"){

                while(iter.second[i].End_Pos.first != iter.second[i].Row_Size-2)
                    Outcome(iter.second[i]);

                cout << "Down sequence" << endl;

                int Transcend = iter.second[i].End_Pos.second;

                iter.second[i+1].Current_Pos_Set(1,Transcend,1);
            }
            else if (Motion == "L"){

                while(iter.second[i].End_Pos.second != 1)
                    Outcome(iter.second[i]);

                cout << "Left sequence" << endl;

                int Transcend = iter.second[i].End_Pos.first;

                iter.second[i+1].Current_Pos_Set(Transcend,iter.second[i].Col_Size-2,1);
            }
            else if(Motion == "R"){

                while(iter.second[i].End_Pos.second != iter.second[i].Col_Size-2)
                    Outcome(iter.second[i]);

                cout << "Right sequence" << endl;

                int Transcend = iter.second[i].End_Pos.first;

                iter.second[i+1].Current_Pos_Set(Transcend,1,1);
            }
            else
                cout << "Motion Analysis Failed" <<endl;

            cout << "End of Loop" << endl;

            elements = iter.second[i].Process;

            elements.push_back(Motion);

            Whole_Process.push_back(elements);
        }

        Outcome(iter.second[3]);

        Whole_Process.push_back(iter.second[3].Process);

        for(auto it : Whole_Process){
            for(auto i : it)
                cout << i;
        }

    }


}





// Determine Type of Input Matrix and send it to F Phase

Case Case_Deter (Fenced _Fenced) {

    Case _Case = OddxOdd;

    if(_Fenced.Row_Size % 2 != 0 && _Fenced.Col_Size % 2 != 0)
        _Case = OddxOdd;
    else if(_Fenced.Row_Size % 2 == 0 && _Fenced.Col_Size % 2 != 0)
        _Case = EvenxOdd;
    else if(_Fenced.Row_Size % 2 != 0 && _Fenced.Col_Size % 2 == 0)
        _Case = OddxEven;
    else
        _Case = EvenxEven;

    _Fenced.TYPE = _Case;

    return _Case;
}


// Receive Input Data and Save

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


// Check Input Data and Make Object 'Fenced'

std::vector <std::pair <Fenced,int>> Create_Fenced_Pair (std::vector <std::vector <int>> Fenced_Cond, int Num){

    std::vector <std::pair <Fenced, int>> _Fenced_Pair;

    for(int i=0; i<Num; i++){

        auto Temp_Fenced = new Fenced(Fenced_Cond[i][0], Fenced_Cond[i][1]);

        Temp_Fenced->Current_Pos_Set(Fenced_Cond[i][2], Fenced_Cond[i][3], 1);

        std::pair <Fenced, int> Temp_Fenced_Pair = std::make_pair (*Temp_Fenced, i);

        _Fenced_Pair.push_back(Temp_Fenced_Pair);

        delete Temp_Fenced;
    }


    return _Fenced_Pair;
}

// Determine next move and send it is Success or Fail

void Move (Fenced& _Fenced, int idx) {

    _Fenced.Status = Stand_by;

    int i = _Fenced.Pos.first, j = _Fenced.Pos.second;

    Result result = Stand_by;

    if(_Fenced.Matrix[i+1][j] != 0 && _Fenced.Matrix[i-1][j] != 0 && _Fenced.Matrix[i][j+1] != 0 && _Fenced.Matrix[i][j-1] != 0){ // This means it's not mov-able

        if(idx == (_Fenced.Row_Size-2)*(_Fenced.Col_Size-2)+1)
            result = Succeed;
        else
            result = Failed;

        _Fenced.End_Pos = _Fenced.Pos;

        _Fenced.Status = result;
    }
    else {

        string Index;

        int loop_move = 1;

        while (loop_move) {

            int i = _Fenced.Pos.first, j = _Fenced.Pos.second;

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

            if(i <= _Fenced.Row_Size -2 && i >= 1 && j <= _Fenced.Col_Size -2 && j >= 1) { // If moved Pos is in the Fence

                if (_Fenced.Matrix[i][j] == 0) {
                    _Fenced.Current_Pos_Set(i,j, idx);
                    loop_move = 0; // End of Loop
                }
            }
        }
        _Fenced.Process.push_back(Index);
    }
}

// Receive Result of Move and Eliminate Redundant Process

void Outcome (Fenced _Fenced){

    std::vector <std::vector <std::string>> Package;

    int loop = 1;

    Result status = Stand_by;


    while(loop < 50) {

        Fenced Temp = _Fenced;

        int idx = 1;

        while (status == Stand_by) {
            Move(Temp, idx + 1);
            status = Temp.Status;
            idx++;
        }


        auto find_it = std::find(Package.begin(), Package.end(), Temp.Process);

        if(find_it == Package.end()) { // If there's no repeated result

            Package.push_back(Temp.Process);

            switch (status) {
                case Failed : {
                    break;
                }

                case Succeed : {
                    for(auto it : Temp.Process) {
                        _Fenced.Process.push_back(it);
                        cout << it;
                    }
                    _Fenced.End_Pos = Temp.End_Pos;
                    cout << endl;
                    loop = 100;
                    break;
                }
            }
        }
        loop++;
        if(loop == 50)
            cout << "IMPOSSIBLE" <<endl;
    }
}



int main(){

    std::srand((unsigned int) time(NULL));

    int Num_Q = 0;

    std::cin >> Num_Q;

    std::vector <std::vector <int>> Input_Vec = Input(Num_Q);

    std::vector <std::pair <Fenced,int>> Fenced_Vec = Create_Fenced_Pair(Input_Vec, Num_Q);

    for (auto it : Fenced_Vec) {

        std::vector < pair <std::vector <string> , std::vector <Fenced>>> pp = Phased_Fenced(it.first);

        Transcendence(pp);
    }

}