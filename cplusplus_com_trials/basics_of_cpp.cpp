/* 
to compile this file, type in terminal in the root folder: 
  g++ -std=c++20 cplusplus_com_trials/basics_of_cpp.cpp -o .bin/basics_of_cpp.bin
to run the compiled binary, type in terminal in the root folder: 
  .bin/basics_of_cpp.bin
*/
 
#include <iostream>
#include <vector>
#include <string>
#include <limits>

using namespace std;

/** @brief Print the version of the current c++ standard of the compiler in the command line.*/
void cpp_standard_ver_trial() {
    if (__cplusplus == 202002L) std::cout << "**C++20\n";
    else if (__cplusplus == 201703L) std::cout << "**C++17\n";
    else if (__cplusplus == 201402L) std::cout << "**C++14\n";
    else if (__cplusplus == 201103L) std::cout << "**C++11\n";
    else if (__cplusplus == 199711L) std::cout << "**C++98\n";
    else std::cout << "pre-standard C++\n";
}

/** @brief This feature is specific to c++20 or plus. Older standard, such as c++17, will show error for this function.*/
void feature_of_cpp20_trial() {
  auto result = (10 <=> 20) > 0;
  cout << "result: " << result << std::endl;
}

/** @brief Print out the c++ types.*/
void cpp_types_trial() {
  string output  = "";
  
  { // string(1, var) converts a char to a string
    char var = 5; // this assigned the char with ascii code 0
    output += "var: " + string(1, var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  {
    signed char var = -'5';
    output += "var: " + to_string(var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  {
    unsigned char var = -5;
    output += "var: " + to_string(var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  {
    unsigned long var = -5;
    output += "var: " + to_string(var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  {
    signed int var = 64;
    output += "var: " + to_string(var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  {
    signed char var = 64;
    output += "var: " + string(1, var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  {
    signed char var = -64;
    output += "var: " + string(1, var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  {
    unsigned short var = -1;
    output += "var: " + to_string(var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  {
    signed short var = __SHRT_MAX__;
    output += "var: " + to_string(var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  {
    unsigned int var = -1;
    output += "var: " + to_string(var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  {
    long double var = -1;
    output += "var: " + to_string(var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  {
    bool var = false;
    output += "var: " + to_string(var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  // decltype will be discussed later in the cplusplus.com

  cout << output;
}

template <typename T> constexpr T sum_of_2(T a, T b) {
  a += 1;
  return a + b;
}

/** @brief Test the methods in std::numeric_limits */
void numeric_limits_trial() {
  cout << int() << endl;
  int i = 2023;
  i += 1;
  constexpr int j = 2023;
  constexpr int k = 1 + j;
  cout << k << endl;
  int sum = sum_of_2(i, 3);
  cout << "i: " << i << ", sum: " << sum << endl;
  cout << "4. " << numeric_limits<unsigned int>::digits10 << endl;
  cout << "5. " << numeric_limits<double>::epsilon << endl;
}

int main() {
    numeric_limits_trial();
    return 0;
}