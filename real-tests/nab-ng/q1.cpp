/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 real-tests/nab-ng/q1.cpp -o .bin/real-tests@@nab-ng@@q1.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/real-tests@@nab-ng@@q1.bin
*/

#include <vector>
#include <iostream>
#include <set>

using namespace std;

// you can use includes, for example:
// #include <algorithm>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

int countOccurrences(string s, string substr) {
    int count = 0;
    size_t pos = s.find(substr);
    while (pos != string::npos) {
        count++;
        pos = s.find(substr, pos + 1);
    }
    return count;
}

int solution(string &S) {
    
    // Implement your solution here
    int n = S.size();
    if (n < 2) {
        return n;
    }

    for (int len = 1; len <= n; ++len) {
        for (int i = 0; i + len <= n; ++i) {
            string substr = S.substr(i, len);
            int count = countOccurrences(S, substr);
            if (count == 1) {
                return len;
            }
        }
    }

    return n;
}

int main()
{
    return 0;
}