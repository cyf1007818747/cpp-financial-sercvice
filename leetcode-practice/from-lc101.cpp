/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 leetcode-practice/from-lc101.cpp -o .bin/leetcode-practice@@from-lc101.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/leetcode-practice@@from-lc101.bin
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool canPlaceFlowers(vector<int>& flowerbed, int n) {
  int max_new_flowers = 0;
  int size = flowerbed.size();
  if (size == 1) {
    return flowerbed[0] == 0 ? n <= 1 : n <= 0;
  } else if (size == 2) {
    return flowerbed[0] + flowerbed[1] == 0 ? n <= 1 : n <= 0;
  } else {
    for (int i = 0; i < size - 2; i++) {
      if (i == 0 && flowerbed[i] == 0 && flowerbed[i+1] == 0) {
        flowerbed[i] = 1;
        max_new_flowers++;
      } else if (flowerbed[i] == 0 && flowerbed[i+1] == 0 && flowerbed[i+2] == 0) {
        flowerbed[i+1] = 1;
        max_new_flowers++;
      }
    }
    if (flowerbed[size-2] == 0 && flowerbed[size-1] == 0) {
      flowerbed[size-1] = 1;
      max_new_flowers++;
    }
  }
  return n <= max_new_flowers;
}

int main() {
  vector<int> flowerbed = {0,0,0,0,0,0,0,1,0,0,1,0,0,0,1,0,0,1,0,0};
  canPlaceFlowers(flowerbed, 5);
  for (int num: flowerbed) {
    cout << num << ' ';
  }
  cout << '\n';
  return 0;
}
