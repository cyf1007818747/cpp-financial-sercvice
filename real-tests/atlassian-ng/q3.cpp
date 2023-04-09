/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 real-tests/atlassian-ng/q3.cpp -o .bin/real-tests@@atlassian-ng@@q3.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/real-tests@@atlassian-ng@@q3.bin
*/

#include <bits/stdc++.h>
#include <map>
#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'groupTransactions' function below.
 *
 * The function is expected to return a STRING_ARRAY.
 * The function accepts STRING_ARRAY transactions as parameter.
 */

vector<string> groupTransactions(vector<string> transactions) {
    map<string, int> count_map;
    for (string str: transactions) {
        if (count_map.count(str)) {
            count_map[str]++;
        } else {
            count_map[str] = 1;
        }
    }
    vector<pair<string, int>> pairs;
    for (pair<string, int> tu: count_map) {
        pairs.push_back(tu);
    }
    sort(pairs.begin(), pairs.end(), [](pair<string, int> a, pair<string, int> b) {
        if (a.second == b.second) {
            return a.first < b.first;    
        }
        return a.second > b.second;
    });
    vector<string> output;
    for (auto& [key, value] : pairs) {
        string str = key + " " + to_string(value);
        output.push_back(str);
    }
    return output;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string transactions_count_temp;
    getline(cin, transactions_count_temp);

    int transactions_count = stoi(ltrim(rtrim(transactions_count_temp)));

    vector<string> transactions(transactions_count);

    for (int i = 0; i < transactions_count; i++) {
        string transactions_item;
        getline(cin, transactions_item);

        transactions[i] = transactions_item;
    }

    vector<string> result = groupTransactions(transactions);

    for (size_t i = 0; i < result.size(); i++) {
        fout << result[i];

        if (i != result.size() - 1) {
            fout << "\n";
        }
    }

    fout << "\n";

    fout.close();

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace)))
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), not1(ptr_fun<int, int>(isspace))).base(),
        s.end()
    );

    return s;
}