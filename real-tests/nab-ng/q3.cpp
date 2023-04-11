/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 real-tests/nab-ng/q3.cpp -o .bin/real-tests@@nab-ng@@q3.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/real-tests@@nab-ng@@q3.bin
*/

#include <vector>
#include <iostream>
#include <set>

using namespace std;

// you can use includes, for example:
// #include <algorithm>
#include <set>

// you can write to stdout for debugging purposes, e.g.
// cout << "this is a debug message" << endl;

// int solution(vector<int> &A) {
//     // Implement your solution here
//     int N = A.size();
//     if (N <= 2) {
//         return N;
//     }
//     sort(A.begin(), A.end());
//     // create a 2d memoization for dynamic programming
//     vector<vector<int>> dp(N, vector<int>(N, 2));
//     int ans = 2;
//     for (int i = 2; i < N; ++i) {
//         for (int j = i - 1; j >= 1; --j) {
//             int diff = A[i] - A[j];
//             for (int k = j - 1; k >= 0; --k) {
//                 if (A[k] + diff == A[j]) {
//                     dp[j][diff] = max(dp[j][diff], dp[k][diff] + 1);
//                     ans = max(ans, dp[j][diff]);
//                 }
//             }
//         }
//     }
//     return ans;
// }

int solution(vector<int> A)
{
    int ans = 2;
    int n = A.size();
    if (n <= 2)
        return n;
 
    vector<int> llap(n, 2);
 
    sort(A.begin(), A.end());
 
    for (int j = n - 2; j >= 0; j--)
    {
        int i = j - 1;
        int k = j + 1;
        while (i >= 0 && k < n)
        {
            if (A[i] + A[k] == 2 * A[j])
            {
                llap[j] = max(llap[k] + 1, llap[j]);
                ans = max(ans, llap[j]);
                i -= 1;
                k += 1;
            }
            else if (A[i] + A[k] < 2 * A[j])
                k += 1;
            else
                i -= 1;
        }
    }
    return ans;
}


int main()
{
    vector<int> vec{1,31,61,71,91};
    // for (int i = 1; i*i <= 100; ++i) {
    //     vec.push_back(i*i);
    // }
    cout << solution(vec) << endl;
}