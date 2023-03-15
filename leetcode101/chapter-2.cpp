/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 leetcode101/chapter-2.cpp -o .bin/leetcode101@@chapter-2.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/leetcode101@@chapter-2.bin
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

int main() {
  return 0;
}
