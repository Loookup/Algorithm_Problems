#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <map>
using namespace std;

class Terrain {
public :
    Terrain() = default; // Default Constructor
    Terrain(std::vector <vector <int>> _Terrain, size_t _Row_Size, size_t _Col_Size) // Constructor
            : Components(_Terrain),Row_Size(_Row_Size), Col_Size(_Col_Size){};
    Terrain(int Value, size_t _Row_Size, size_t _Col_Size) : Row_Size(_Row_Size), Col_Size(_Col_Size){
        std::vector <std::vector<int>> Valued_Vec;
        for(int i=0; i<_Row_Size; i++){
            std::vector<int> temp;
            for(int j=0; j<_Col_Size; j++)
                temp.push_back(Value);
            Valued_Vec.push_back(temp);
        }
        Components = Valued_Vec;
    }

    Terrain (const Terrain& _Terrain) : Components(_Terrain.Components),Row_Size(_Terrain.Row_Size), Col_Size(_Terrain.Col_Size) {} // Copy Constructor
    Terrain (const Terrain&& _Terrain) : Row_Size(std::move(_Terrain.Row_Size)), Col_Size(std::move(_Terrain.Col_Size)){
        Components = std::move(_Terrain.Components);} // Move Constructor
    ~Terrain() noexcept = default; // Destructor
    int& operator[] (std::pair<int ,int> _Where){ // Index Operator

        int index_Row = _Where.first;

        int index_Col = _Where.second;

        return Components[index_Row][index_Col];

    }
    friend int MAX(Terrain _Terrain); // Top Layer Determinant
    friend int MIN(Terrain _Terrain, int Max); // Bottom Layer Determinant
    friend pair<int,int> Deter(Terrain _Terrain, int B); // (Worked Time, Top Layer Position)
    friend std::ostream& operator << (std::ostream& os, const Terrain& _Terrain);

private:
    std::vector <std::vector <int>> Components {0}; // Data of Terrain
    size_t Row_Size = 0;
    size_t Col_Size = 0;
};


std::ostream& operator << (std::ostream& os, const Terrain& _Terrain){

    for(auto it = _Terrain.Components.begin(); it != _Terrain.Components.end(); it++){

        std::copy(it->begin(),it->end(),std::ostream_iterator<int>(std::cout," "));
        std::cout << std::endl;

    }

    return os;
}


std::vector <std::vector <int>> Input (int M, int N){

    std::vector <std::vector <int>> Terrain;

    for(int i=0; i<M; i++){

        std::vector <int> Vec_Temp;

        for(int j=0; j<N; j++){

            int Temp;

            cin >> Temp;

            Vec_Temp.push_back(Temp);
        }

        Terrain.push_back(Vec_Temp);
    }

    return Terrain;
}


int MAX (Terrain _Terrain) {

    int Max = 0;

    for(auto it : _Terrain.Components){

        int Max_Temp = *std::max_element(it.begin(),it.end());

        if(Max_Temp > Max)
            Max = Max_Temp;
    }

    return Max;
}


int MIN(Terrain _Terrain, int Max){

    int Min = Max;

    for(auto it : _Terrain.Components){

        int Min_Temp = *std::min_element(it.begin(),it.end());

        if(Min_Temp < Min)
            Min = Min_Temp;
    }

    return Min;
}


pair<int,int> Deter (Terrain _Terrain, int B){

    int Max = MAX(_Terrain);

    int Min = MIN(_Terrain, Max);

    std::vector <std::pair <Terrain,int>> Layer_info; // Top -> Bottom Layers info (0 ~ Max-Min)

    for(int i= Max; i>Min; i--){

        Terrain Terrain_Temp (0, _Terrain.Row_Size, _Terrain.Col_Size);

        int Hole_Current_Layer = 0;

        for(int j=0; j<_Terrain.Row_Size; j++){

            for(int k=0; k<_Terrain.Col_Size; k++){

                auto pa = make_pair(j,k);

                if(i > _Terrain[pa]) {
                    Terrain_Temp[pa] = 1;
                    Hole_Current_Layer++;
                }
            }

        }

        auto Pair_Temp = make_pair(Terrain_Temp, Hole_Current_Layer);

        Layer_info.push_back(Pair_Temp);
    }

    int Whole_Hole = 0;

    for(auto it : Layer_info)
        Whole_Hole += it.second;

    std::cout << "The number of Holes in Whole Layers is : " << Whole_Hole << std::endl;



    pair <int, int> Result = {0,0};

    int Time = 0;
    int Level = Max;


    int Area = _Terrain.Row_Size*_Terrain.Col_Size;

    float Criterion = Area *2 / 3;




    int Hole_Left = Whole_Hole;

    for(int i=0; i<Max-Min; i++){

        if(B >= Hole_Left){ // There are enough Blocks to cover below Layers, so we have options, cover or cut

            if(Layer_info[i].second <= Criterion){ // Cover is a better option to save time
                Time += Layer_info[i].second; // Filling takes 1-sec
                B -= Layer_info[i].second; // The Inventory(B) is consumed equal to the number of Holes
            } else { // Cutting is a better option to save time
                Time += 2*(Area - Layer_info[i].second); // Cutting takes 2-sec
                Level--; // Top Layer is cut off
                B += (Area - Layer_info[i].second); // The Inventory(B) is filled equal with the number of Area - Holes
            }

        }

        else { // There aren't enough Blocks to cover below Layers, so we only have to cut top layers

            Time += 2*(Area - Layer_info[i].second); // Cutting takes 2-sec
            Level--; // Top Layer is cut off
            B += (Area - Layer_info[i].second); // The Inventory(B) is filled equal with the number of Area - Holes

        }

        Hole_Left -= Layer_info[i].second; // Eliminate Top Layer's Hole

    }


    Result.first = Time;
    Result.second = Level;

    return Result;
}



int main() {

    int M = 0, N = 0, B = 0;

    std::cin >> M >> N >> B;

    vector <vector <int>> input = Input(M,N);

    Terrain Terrain(input,M,N);

    pair<int, int> Result = Deter(Terrain, B);

    std::cout << "Worked Time is : " << Result.first <<" And the height of the Terrain is : " << Result.second << std::endl;

}
