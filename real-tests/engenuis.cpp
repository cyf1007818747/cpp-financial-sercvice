/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 real-tests/engenuis.cpp -o .bin/real-tests@@engenuis.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/real-tests@@engenuis.bin
*/

#include <iostream>
#include <set>

using namespace std;

// Note that I assume that users input integer numbers.
// If a user may input decimal numbers, just change the set<long> to set<double> to make it work. 
// Also, I assume that I only have to print each number once if there are duplicates. 
// If I need to print all the duplicates, just by changing the set data structure to multiset can make it work.
void command_num_sorting() {
  set<long> num_set;
  long num;
  while (cin >> num) {
    num_set.insert(num);
  }
  cout << "myoutput:" << endl;
  for (auto it = num_set.rbegin(); it != num_set.rend(); ++it) {
    cout << *it << endl;
  }
}

int main() {
  command_num_sorting();
}