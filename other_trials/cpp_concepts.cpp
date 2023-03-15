/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 other_trials/cpp_concepts.cpp -o .bin/other_trials@@cpp_concepts.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/other_trials@@cpp_concepts.bin
*/

#include <iostream>

using namespace std;

/** @brief trial of std::integral_constant */
template <int n> struct twice_cons : integral_constant<int, n*2> {};
void integral_constant_trial() {
  twice_cons<7> twice_v;
  cout << twice_v.value << endl;
}

int main() {
    integral_constant_trial();
    return 0;
}