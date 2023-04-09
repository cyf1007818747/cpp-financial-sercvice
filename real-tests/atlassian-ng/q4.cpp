/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 real-tests/atlassian-ng/q4.cpp -o .bin/real-tests@@atlassian-ng@@q4.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/real-tests@@atlassian-ng@@q4.bin
*/

#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);



/*
 * Complete the 'getMinimumHealth' function below.
 *
 * The function is expected to return a LONG_INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER_ARRAY initial_players
 *  2. INTEGER_ARRAY new_players
 *  3. INTEGER rank
 */
long getMinimumHealth(vector<int> initial_players, vector<int> new_players, int k) {
    long min_health = 0;
    vector<int> myvec = initial_players;
    sort(myvec.begin(), myvec.end());
    min_health += k <= myvec.size() ? myvec[myvec.size() - k] : 0;
    for (int newp : new_players) {
        myvec.insert(lower_bound(myvec.begin(), myvec.end(), newp), newp);
        min_health += k <= myvec.size() ? myvec[myvec.size() - k] : 0;
    }
    return min_health;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string initial_players_count_temp;
    getline(cin, initial_players_count_temp);

    int initial_players_count = stoi(ltrim(rtrim(initial_players_count_temp)));

    vector<int> initial_players(initial_players_count);

    for (int i = 0; i < initial_players_count; i++) {
        string initial_players_item_temp;
        getline(cin, initial_players_item_temp);

        int initial_players_item = stoi(ltrim(rtrim(initial_players_item_temp)));

        initial_players[i] = initial_players_item;
    }

    string new_players_count_temp;
    getline(cin, new_players_count_temp);

    int new_players_count = stoi(ltrim(rtrim(new_players_count_temp)));

    vector<int> new_players(new_players_count);

    for (int i = 0; i < new_players_count; i++) {
        string new_players_item_temp;
        getline(cin, new_players_item_temp);

        int new_players_item = stoi(ltrim(rtrim(new_players_item_temp)));

        new_players[i] = new_players_item;
    }

    string rank_temp;
    getline(cin, rank_temp);

    int rank = stoi(ltrim(rtrim(rank_temp)));

    long result = getMinimumHealth(initial_players, new_players, rank);

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