/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 leetcode101/samples.cpp -o .bin/leetcode101@@samples.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/leetcode101@@samples.bin
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

int findContentChildren(vector<int> &children, vector<int> &cookies)
{
  sort(children.begin(), children.end());
  sort(cookies.begin(), cookies.end());
  int child = 0, cookie = 0;
  while (child < children.size() && cookie < cookies.size())
  {
    if (children[child] <= cookies[cookie])
      ++child;
    ++cookie;
  }
  return child;
}

// ########################### binary search algorithms -- 默写 -- 左闭右闭方法 ########################
// 1. find the index of any number equals to the key.
int bin_search_any_equal(vector<int> arr,int key) {
  int l = 0, r = arr.size() - 1;
  int mid;
  while (l <= r) {
    mid = l + (r - l) / 2;
    if (key == arr[mid]) {
      return mid;
    } else if (key < arr[mid]) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  return -1;
}

// 2. find the index of the first number equals to the key.
int bin_search_first_equal(vector<int> arr,int key) {
  int l = 0, r = arr.size() - 1;
  int mid;
  while (l <= r) {
    mid = l + (r - l) / 2;
    if (key <= arr[mid]) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  if (l < arr.size() && arr[l] == key) {
    return l;
  }
  return -1;
}

// 3. find the index of the last number equals to the key.
int bin_search_last_equal(vector<int> arr,int key) {
  int l = 0, r = arr.size() - 1;
  int mid;
  while (l <= r) {
    mid = l + (r - l) / 2;
    if (key >= arr[mid]) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  if (r >= 0 && arr[r] == key) {
    return r;
  }
  return -1;
}

// 4. find the index of the first number greater or equal to the key.
int bin_search_first_gteq(vector<int> arr,int key) {
  int l = 0, r = arr.size() - 1;
  int mid;
  while (l <= r) {
    mid = l + (r - l) / 2;
    if (key <= arr[mid]) {
      r = mid - 1;
    } else {
      l = mid + 1;
    }
  }
  if (l < arr.size()) {
    return l;
  }
  return -1;
}

// 5. find the index of the last number less than or equal to the key.
int bin_search_first_gteq(vector<int> arr,int key) {
  int l = 0, r = arr.size() - 1;
  int mid;
  while (l <= r) {
    mid = l + (r - l) / 2;
    if (key >= arr[mid]) {
      l = mid + 1;
    } else {
      r = mid - 1;
    }
  }
  if (r >= 0) {
    return r;
  }
  return -1;
}




int main() {
  vector<int> arr = {1, 2,4,5,5,7, 7,7,7,7,7, 7,8,8,9,10};
  int key = 7;
  int index = bin_search_last_equal(arr, key);
  int target_num = index >= 0 && index < arr.size() ? arr[index] : -1;
  cout << index << ", " << target_num << endl;
  return 0;
}
