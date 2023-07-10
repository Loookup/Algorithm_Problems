#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

int main(){
    std::vector<int> vec;

    std::istream_iterator<int> cin_iter(std::cin);

    std::istream_iterator<int> eos;

    std::copy(cin_iter, eos, std::back_inserter(vec));

    std::sort(begin(vec), end(vec));

    std::ostream_iterator<int> cout_iter(std::cout, " ");

    std::copy(vec.begin(), vec.end(), cout_iter);

}
