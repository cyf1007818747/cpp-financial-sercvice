/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 other_trials/oa.cpp -o .bin/other_trials@@oa.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/other_trials@@oa.bin
*/

#include <iostream>
#include <string>
using namespace std;

int main() {
  string line;
  while (getline(cin, line)) {
    string longest_word = "";
    string curr_word = "";
    for (size_t pos = 0; pos <= line.size(); ++pos) {
        if (line[pos] != ' ' && pos != line.size()) {
            curr_word.push_back(line[pos]);
        } else {
            if (curr_word.size() > longest_word.size()) {
                longest_word = curr_word;
            }
            curr_word = "";
        }
    }
    cout << longest_word << endl;
  }
  return 0;
}