/* 
to compile this file, type in terminal in the root folder: 
  g++ -std=c++20 cplusplus_com_trials/basics_of_cpp.cpp -o .bin/basics_of_cpp.bin
to run the compiled binary, type in terminal in the root folder: 
  .bin/basics_of_cpp.bin
*/
 
#include <iostream>
#include <vector>
#include <string>

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
    char var = '5';
    output += "var: " + string(1, var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  { // to_string only converts an int to a string
    char var = 5;
    output += "var: " + to_string(var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  {
    char var = '5';
    output += "var: " + to_string(var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  {
    char16_t var = '5';
    output += "var: " + string(1, var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  {
    char32_t var = '5';
    output += "var: " + string(1, var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  {
    wchar_t var = '5';
    output += "var: " + string(1, var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }
  {
    signed char var = '5';
    output += "var: " + to_string(var) + ", type: " + typeid(var).name() + ", size of var: " + to_string(sizeof(var)) + "\n";
  }

  cout << output;
}

int main() {
    cpp_standard_ver_trial();
    return 0;
}