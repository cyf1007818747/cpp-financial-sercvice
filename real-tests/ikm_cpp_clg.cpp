/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 real-tests/ikm_cpp_clg.cpp -o .bin/real-tests@@ikm_cpp_clg.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/real-tests@@ikm_cpp_clg.bin
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include <iomanip>
#include <algorithm>

using namespace std;

void ikm_q1() {
  int num;
  while(cin >> num) {
    if (num == -1) {
      break;
    }
    int sum = 0;
    int speed, time;
    int time_prev = 0;
    for (int i = 0; i < num; ++i) {
      cin >> speed;
      cin >> time;
      sum += speed*(time - time_prev);
      time_prev = time;
    }
    cout << sum << " miles" << endl;
  }
}

void ikm_q2() {
  int a, b;
  int case_num = 1;
  while (cin >> a && cin >> b) {
    long n = 0;
    while (true) {
        if ((n % 687) == ((687 - b) % 687) && (n % 365) == ((365 - a) % 365)) {
          cout << "Case " << case_num << ": " << n << endl;
          break;
        }
        n++;
    }
    ++case_num;
  }
}

string getCatColor(const string& genes) {
  string color;

  // Extract individual genes
  char b1 = genes[0];  // can be B or b
  char b2 = genes[1];  // can be B or b
  char d1 = genes[2];  // can be D or d
  char d2 = genes[3];  // can be D or d
  char r1 = genes[4];  // can be O or o or .
  char r2 = genes[5];  // can be O or o or .

  // Determine coat color based on gene combinations
  if (r1 != 'O' && r2 != 'O') { // cases where red gene has no effect
    if (b1 == 'B' || b2 == 'B') {
      if (d1 == 'D' || d2 == 'D') {
        color = "Black";
      } else { // dd
        color = "Blue";
      }
    } else { // bb
      if (d1 == 'D' || d2 == 'D') {
        color = "Chocolate";
      } else { // dd
        color = "Lilac";
      }
    } 
  } else if (r1 == '.' || r2 == '.') { // male cat
    if (d1 == 'D' || d2 == 'D') {
      color = "Red";
    } else { // dd
      color = "Cream";
    }
  } else { // female cat
    if (r1 == 'O' && r2 == 'O') {
      if (d1 == 'D' || d2 == 'D') {
        color = "Red";
      } else { // dd
        color = "Cream";
      }
    } else { // r1 and r2 is one O and one o
      if (b1 == 'B' || b2 == 'B') {
        if (d1 == 'D' || d2 == 'D') {
          color = "Black-Red Tortie";
        } else { // dd
          color = "Blue-Cream Tortie";
        }
      } else { // bb
        if (d1 == 'D' || d2 == 'D') {
          color = "Chocolate-Red Tortie";
        } else { // dd
          color = "Lilac-Cream Tortie";
        }
      }
    }
  }

  return color;
}

string getCatGender(const string& genes) {
  string gender;

  // Extract individual genes
  char r1 = genes[4];  // can be O or o or .
  char r2 = genes[5];  // can be O or o or .

  if (r1 == '.' || r2 == '.') {
    gender = "male";
  } else {
    gender = "female";
  }

  return gender;
}

unordered_map<string, int> getOffspringColorCounts(string mom_color, string dad_color, long & total_cts) {

  const vector<string> black_gene_combs = {"BB", "Bb", "bb"};
  const vector<string> dilution_gene_combs = {"DD", "Dd", "dd"};
  // const vector<string> red_gene_combs = {"OO", "Oo", "O.", "oO", "oo", "o.", ".O", ".o"};
  const vector<string> red_gene_combs = {"OO", "Oo", "O.", "oo", "o."};
  vector<string> dad_poss_genes, mom_poss_genes;

  // generate all possible genes of dad and mom cat
  for (string black_gene: black_gene_combs) {
    for (string dilution_gene: dilution_gene_combs) {
      for (string red_gene: red_gene_combs) {
        string gene = black_gene + dilution_gene + red_gene;
        if (getCatColor(gene) == dad_color && getCatGender(gene) == "male") {
          dad_poss_genes.push_back(gene);
        } else if (getCatColor(gene) == mom_color && getCatGender(gene) == "female") {
          mom_poss_genes.push_back(gene);
        }
      }
    }
  }
  
  // for (string g: dad_poss_genes) {
  //   cout << "dad poss gene: " << g << ", color: " << getCatColor(g) << endl;
  // }

  // for (string g: mom_poss_genes) {
  //   cout << "mom poss gene: " << g << ", color: " << getCatColor(g) << endl;
  // }

  long total_counts = 0;
  unordered_map<string, int> count_map;
  for (string & dad_gene: dad_poss_genes) {
    for (string & mom_gene: mom_poss_genes) {
      string estr = "";
      vector<string> poss_black_genes = 
        {estr+dad_gene[0]+mom_gene[0], estr+dad_gene[0]+mom_gene[1], estr+dad_gene[1]+mom_gene[0], estr+dad_gene[1]+mom_gene[1]};
      vector<string> poss_diluton_genes = 
        {estr+dad_gene[2]+mom_gene[2], estr+dad_gene[2]+mom_gene[3], estr+dad_gene[3]+mom_gene[2], estr+dad_gene[3]+mom_gene[3]};
      vector<string> poss_red_genes = 
        {estr+dad_gene[4]+mom_gene[4], estr+dad_gene[4]+mom_gene[5], estr+dad_gene[5]+mom_gene[4], estr+dad_gene[5]+mom_gene[5]};
      for (string & b_gene: poss_black_genes) {
        for (string & d_gene: poss_diluton_genes) {
          for (string & r_gene: poss_red_genes) {
            string child_gene = "" + b_gene + d_gene + r_gene;
            string child_color = getCatColor(child_gene);
            count_map[child_color]++;
            total_counts++;
          }
        }
      }
    }
  }
  total_cts = total_counts;
  return count_map;
}

bool pairComparator(const pair<string, double>& pair1, const pair<string, double>& pair2) {
    if (pair1.second == pair2.second) {
        return pair1.first < pair2.first;
    }
    return pair1.second > pair2.second;
}

void ikm_q3() {
  // long total_counts = 0;
  // unordered_map<string, int> count_map = getOffspringColorCounts("Blue", "Red", total_counts);
  // for (auto it = count_map.begin(); it != count_map.end(); ++it) {
  //   cout << "color: " << it->first << ", count: " << it->second << endl;
  // }
  // cout << "total_counts: " << total_counts << endl;
  // cout << getCatColor("bbddOo") << " " << getCatGender("bbddOo") << endl;
  string mom_color, dad_color;
  while (getline(cin, mom_color) && getline(cin, dad_color)) {
    long total_counts = 0;
    vector<pair<string, double>> prob_data;
    unordered_map<string, int> count_map = getOffspringColorCounts(mom_color, dad_color, total_counts);
    for (auto it = count_map.begin(); it != count_map.end(); ++it) {
      prob_data.emplace_back(it->first, ((double) it->second) / ((double) total_counts));
    }
    sort(prob_data.begin(), prob_data.end(), pairComparator);
    for (auto it = prob_data.begin(); it != prob_data.end(); ++it) {
      cout << it->first << " " << setprecision(9) << it->second << endl;
    }
  }
}

int main() {
  ikm_q3();
}