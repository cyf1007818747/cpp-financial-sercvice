/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 useful_funcs/general_funcs.cpp -o .bin/useful_funcs@@general_funs.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/useful_funcs@@general_funs.bin
*/

#include <vector>
#include <numeric>

using namespace std;

// vector operations
void vector_funcs() {
    return;

    // @brief - sort a vector
    vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    std::sort(vec.begin(), vec.end());

    // @brief - sort with customised compare functions
    vector<int> vec = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    sort(vec.begin(), vec.end(), [](int a, int b) {
        return a > b; // compare function to sort in descending order
    });

    // @brief - calulate the sum of all emlements of a vector
    // @headerfile - #include <numeric>
    vector<int> v = {3, 1, 4, 1, 5, 9, 2, 6, 5};
    int sum = std::accumulate(v.begin(), v.end(), 0);

}

// number operations
void number_operations() {
  return;

  // @brief - get the max int
  int num = __INT_MAX__;
}

int main() {
    return 0;
}
