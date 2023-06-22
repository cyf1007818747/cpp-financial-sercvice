/* 
to compile this file, type in terminal in the root folder: 
  g++ -std=c++20 cplusplus_com_trials/unit_testing.cpp -o .bin/cplusplus_com_trials@@unit_testing.bin
to run the compiled binary, type in terminal in the root folder: 
  .bin/cplusplus_com_trials@@unit_testing.bin
*/

#include <iostream>
#include <cassert>

using namespace std;

int mul_times_2_plus_3(int a, int b) {
    return 2*a*b+3;
}

template <typename T>
void myassert(const int test_id, int & passed_test_ct, const T expected, const T actual, const string & fail_mess = "") {
    if (actual == expected) {
        // cout << "Test #" << test_id << " passed." << endl;
        ++passed_test_ct;
    } else {
        cout << "!!!! Test #" << test_id << " faild, expected: " << expected << ", actual: " << actual << ", " << fail_mess << endl;
    }
}

void mul_times_2_plus_3_tests() {
    
    int passed_test_count = 0;
    myassert(1, passed_test_count, mul_times_2_plus_3(1, 3), 9, "0 inputs failed.");
    myassert(2, passed_test_count, mul_times_2_plus_3(1, 4), 9);
    myassert(3, passed_test_count, mul_times_2_plus_3(1, 5), 13);
    myassert(4, passed_test_count, mul_times_2_plus_3(1, 6), 13, "small positive input failed");
    myassert(5, passed_test_count, mul_times_2_plus_3(1, 7), 17);
    cout << "mul_times_2_plus_3_tests: " << passed_test_count << " / 5 tests passed." << endl;
}



int main() {
    mul_times_2_plus_3_tests();
}