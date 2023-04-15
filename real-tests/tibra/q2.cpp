/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 real-tests/tibra/q2.cpp -o .bin/real-tests@@tibra@@q2.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/real-tests@@tibra@@q2.bin
*/

#include <bits/stdc++.h>

using namespace std;


/*
 * Complete the 'maximum_path' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts INTEGER_ARRAY node_values as parameter.
 */

int maximum_path(vector<int> node_values) {
    long values_sz = node_values.size();
    
    if (values_sz == 0) {
        return 0;
    } else if (values_sz == 1) {
        return node_values[0];
    }
    
    int n = (sqrt(8*values_sz+ 1) - 1) / 2;
    vector<vector<int>> tri(n, vector<int>(n, 0));
    
    int idx = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            tri[i][j] = node_values[idx++];
        }
    }
    
    vector<vector<int>> dp(n, vector<int>(n, -1));
    
    vector<int> front(n, -1) , curr(n, -1) ;
    
    for(int j = 0; j < n; j++ ){
        front[j] = tri[n-1][j] ;
    }
        
    for(int i = n-2; i >= 0; i--){
        for(int j = i; j >= 0; j-- ){
            curr[j] = tri[i][j] + max(front[j] , front[j+1]) ;
        }
        front = curr ;
    }
         
    return front[0] ;
}

int main() {
    vector<int> node_values = {1, 2, 1, 2, 1, 1, -1, 0, 0, 10, 12, 0, 0, 0, 0};
    int output = maximum_path(node_values);
    cout << "expected output: 16, actual output: " << output << endl;
}