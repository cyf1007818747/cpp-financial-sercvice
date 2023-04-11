/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 real-tests/nab-ng/q2.cpp -o .bin/real-tests@@nab-ng@@q2.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/real-tests@@nab-ng@@q2.bin
*/

#include <vector>
#include <iostream>
#include <set>

using namespace std;

// you can use includes, for example:
// #include <algorithm>
#include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int solution(vector<int> &P, vector<int> &S) {
    // Implement your solution here
    int N = P.size();
    if (N < 2) {
        return N;
    }
    // make it long to avoid overloading
    long num_people = 0;
    for (int person: P) {
        num_people += person;
    }
    sort(S.begin(), S.end());
    int num_cars_needed = 0;
    // use greedy approach
    for (int i = N-1; i >= 0; --i) {
        num_people -= S[i];
        ++num_cars_needed;
        if (num_people <= 0) {
            // return the result ASAP
            return num_cars_needed;
        }
    }
    return num_cars_needed;
}

int main()
{
    return 0;
}