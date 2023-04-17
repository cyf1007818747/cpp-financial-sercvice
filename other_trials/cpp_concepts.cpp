/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 other_trials/cpp_concepts.cpp -o .bin/other_trials@@cpp_concepts.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/other_trials@@cpp_concepts.bin
*/

#include <iostream>
#include <typeinfo>
#include <vector>

using namespace std;

/** @brief trial of vector erase */
void vector_erase_trial() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  int n;
  cin >> n;
  vector<int> nums(n, 0);
  for (int i = 0; i < n; ++i) {
      cin >> nums[i];
  }
  int rm_sg, rm_l, rm_r;
  cin >> rm_sg >> rm_l >> rm_r;
  nums.erase(nums.begin()+rm_sg-1);

  cout << "after 1st change: " << endl;
  for (int i = 0; i < n - 1; ++i) {
      cout << nums[i] << " ";
  }
  cout << nums[n-1] << endl;

  nums.erase(nums.begin()+rm_l-1, nums.begin()+rm_r-1);

  cout << "after 2nd change: " << endl;
  for (int i = 0; i < n - 1; ++i) {
      cout << nums[i] << " ";
  }
  cout << nums[n-1] << endl;
  
  int nn = nums.size();
  cout << "final outpu: " << endl;
  cout << nn << endl;
  // printing of nums
  for (int i = 0; i < nn - 1; ++i) {
      cout << nums[i] << " ";
  }
  cout << nums[nn-1] << endl;
}

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
    vector_erase_trial();
    return 0;
}