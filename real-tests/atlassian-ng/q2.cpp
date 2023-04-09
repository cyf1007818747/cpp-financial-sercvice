/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 real-tests/atlassian-ng/q2.cpp -o .bin/real-tests@@atlassian-ng@@q2.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/real-tests@@atlassian-ng@@q2.bin
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);


/*
 * Complete the 'reductionCost' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY num as parameter.
 */

// int reductionCost(vector<int> num) {

// }

int reductionCost(vector<int> num) {
    int cost = 0;
    priority_queue<int, vector<int>, greater<int>> pq(num.begin(), num.end());
    
    while (pq.size() > 1) {
        int a = pq.top();
        pq.pop();
        int b = pq.top();
        pq.pop();
        int sum = a + b;
        pq.push(sum);
        cost += sum;
    }
    
    return cost;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string num_count_temp;
    getline(cin, num_count_temp);

    int num_count = stoi(ltrim(rtrim(num_count_temp)));

    vector<int> num(num_count);

    for (int i = 0; i < num_count; i++) {
        string num_item_temp;
        getline(cin, num_item_temp);

        int num_item = stoi(ltrim(rtrim(num_item_temp)));

        num[i] = num_item;
    }

    int result = reductionCost(num);

    fout << result << "\n";

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