/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 other_trials/codility.cpp -o .bin/other_trials@@codility.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/other_trials@@codility.bin
*/
#include <vector>

using namespace std;

// given an array A of N integers, returns the smallest positive integer (greater than 0) that does not occur in A.
int min_pos_num_not_in_array(vector<int> &A) {
    // Implement your solution here
    int n = A.size();
    if (n == 0) {
        return 1;
    } else if (n == 1) {
        return A[0] == 1 ? 2 : 1;
    }
    vector<int> vec;
    for (int num: A) {
      if (num > 0) {
        vec.push_back(num);
      }
    }
    sort(vec.begin(), vec.end());
    if (vec[0] > 1) {
        return 1;
    }
    for (int i = 0; i < n - 1; ++i) {
        if (vec[i] >= 0 && vec[i+1] - vec[i] > 1) {
          return vec[i] + 1;
        } 
    }
    return vec[n-1] + 1;
}

int main() {
  return 0;
}