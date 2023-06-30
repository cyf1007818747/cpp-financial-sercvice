/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 real-tests/cisco.cpp -o .bin/real-tests@@cisco.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/real-tests@@cisco.bin
*/

#include <iostream>
#include <set>
#include <vector>
#include <stack>
#include <map>

using namespace std;

// ## Question from engenuis
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

// vector<string> matchingBraces(vector<string> braces) {
//     vector<string> output;
//     for (int i = 0; i < braces.size(); ++i) {
//       string s = braces[i];
//       stack<char> mystack;
//       for (int j = 0; j < s.size(); ++j) {
//         char c = s[j];
//         if (c == '{' || c == '[' || c == '(') {
//           mystack.push(c);
//         } else if (c == '}' || c == ']' || c == ')') {
//           if (mystack.empty()) {
//             output.push_back("NO");
//             break;
//           }
//           char top = mystack.top();
//           mystack.pop();
//           if ((c == '}' && top != '{') ||
//               (c == ']' && top != '[') ||
//               (c == ')' && top != '(')) {
//               output.push_back("NO");
//               break;
//           }
//         }
//       }
//       if (mystack.empty()) {
//         output.push_back("YES");
//       } else {
//         output.push_back("NO");
//       }
//     }
//     return output;
// }

template <typename T>
void myassert(const int test_id, int & passed_test_ct, const T expected, const T actual, const string & fail_mess = "") {
    if (actual == expected) {
        // cout << "Test #" << test_id << " passed." << endl;
        ++passed_test_ct;
    } else {
        cout << "!!!! Test #" << test_id << " faild, expected: " << expected << ", actual: " << actual << ", " << fail_mess << endl;
    }
}

// ---------------------------- question 1 -------------------------------------

bool balanced_string(const string & str) {
    stack<char> mystack;
    for (char c : str) {
        if (c == '{' || c == '[' || c == '(') {
            mystack.push(c);
        } else if (c == '}' || c == ']' || c == ')') {
            if (mystack.empty()) {
                return false; 
            }
            char top = mystack.top();
            mystack.pop();

            if ((c == '}' && top != '{') ||
                (c == ']' && top != '[') ||
                (c == ')' && top != '(')) {
                return false;
            }
        }
    }
    return mystack.empty();
}

vector<string> matchingBraces(const vector<string> & braces) {
    vector<string> output;
    for (string s: braces) {
      if (balanced_string(s)) {
        output.push_back("YES");
      } else {
        output.push_back("NO");
      }
    }
    return output;
}

void matchingBraces_tests() {

    // balanced string tests
    int passed_test_count = 0;
    myassert(1, passed_test_count, balanced_string(""), true, "empty string failed.");
    myassert(2, passed_test_count, balanced_string("["), false, "size 1 not matching string failed.");
    myassert(3, passed_test_count, balanced_string("[]"), true, "size 2 matching string failed.");
    myassert(4, passed_test_count, balanced_string("[({}[])]"), true, "long matching string failed.");
    myassert(5, passed_test_count, balanced_string("[({}[))]"), false, "long not string matching string failed.");
    vector<string> input = { "", "[", "{}", "[({}[])]", "[({}[))]"};
    // vector<string> expected = {"YES", "NO", "YES", "YES", "NO"};
    vector<string> output = matchingBraces(input);
    cout << "balanced_string: " << passed_test_count << " / 5 tests passed." << endl;
    cout << "matchingBraces printing test output: " << endl;
    for (string s: output) {
      cout << s << endl;
    }
}

// ---------------------------- question 2 -------------------------------------

string betterCompression(const string & s) {
  if (s.size() == 0) {
    return "";
  }
  map<char, int> charCountMap;
  string result;
  int count = 0;
  char prevChar = s[0];

  for (const char c : s) {
      if (isdigit(c)) {
          count = count * 10 + (c - '0');
          // cout << count << endl;
          continue;  // Skip the digits
      } else {
          charCountMap[prevChar]+= count;
          count = 0;
          prevChar = c;
      }
  }
  charCountMap[prevChar]+= count;

  for (const auto & entry : charCountMap) {
      result += entry.first + to_string(entry.second);
  }

  return result;
}

void betterCompression_tests() {

    // balanced string tests
    int passed_test_count = 0;
    {
      string input = "";
      string expected = "";
      myassert(1, passed_test_count, betterCompression(input), expected, "empty string failed.");
    }
    {
      string input = "1a";
      string expected = "1a";
      myassert(2, passed_test_count, betterCompression(input), expected, "1 char test failed.");
    }
    myassert(3, passed_test_count, betterCompression(string("1a2a")), string("3a"), "summing test failed.");
    myassert(4, passed_test_count, betterCompression(string("1b2a")), string("2a1b"), "ordering test failed.");
    cout << "balanced_string: " << passed_test_count << " / 4 tests passed." << endl;
}

int main() {
  // vector<string> input = {"{[]}", "{(})", "" };
  // vector<string> output = matchingBraces(input);
  // for (string s: output) {
  //   cout << s << endl;
  // }
  // cout << betterCompression("a12c56a1b5") << endl;
  matchingBraces_tests();
  // betterCompression_tests();
}