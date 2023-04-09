/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 real-tests/atlassian-ng/q1.cpp -o .bin/real-tests@@atlassian-ng@@q1.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/real-tests@@atlassian-ng@@q1.bin
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);

/*
 * Complete the 'minimumSteps' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts STRING_ARRAY loggedMoves as parameter.
 */

int minimumSteps(vector<string> loggedMoves) {
    int curr_depth = 0;
    for (string str: loggedMoves) {
        if (str[0] == '.' && str[1] == '.') {
            --curr_depth;
        } else if (!(str[0] == '.' && str[1] == '/')) {
            ++curr_depth;
        }
    }
    return curr_depth;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string loggedMoves_count_temp;
    getline(cin, loggedMoves_count_temp);

    int loggedMoves_count = stoi(ltrim(rtrim(loggedMoves_count_temp)));

    vector<string> loggedMoves(loggedMoves_count);

    for (int i = 0; i < loggedMoves_count; i++) {
        string loggedMoves_item;
        getline(cin, loggedMoves_item);

        loggedMoves[i] = loggedMoves_item;
    }

    int result = minimumSteps(loggedMoves);

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