/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 other_trials/cpp_concepts.cpp -o .bin/other_trials@@cpp_concepts.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/other_trials@@cpp_concepts.bin
*/

#include <iostream>
#include <typeinfo>

using namespace std;

/** @brief trial of std::integral_constant */
template <int n> struct twice_cons : integral_constant<int, n*2> { inline static int triple_v = 100; };
void integral_constant_trial() {
  twice_cons<7> twice_v;
  cout << twice_cons<7>::triple_v << endl;
  cout << twice_v.value << endl;
  cout << typeid(twice_cons<7>::type).name() << endl;
  cout << twice_cons<7>::value;
  cout << typeid(twice_cons<7>::value_type).name() << endl;
  twice_cons<7>::triple_v = 101;
  cout << twice_cons<7>::triple_v << endl;
  twice_v.triple_v = 102;
  cout << twice_cons<7>::triple_v << endl;
  cout << twice_cons<8>::triple_v << endl;
  cout << twice_v.triple_v << endl;
}

int main() {
    integral_constant_trial();
    return 0;
}