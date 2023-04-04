/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 leetcode-practice/from-lc101.cpp -o .bin/leetcode-practice@@from-lc101.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/leetcode-practice@@from-lc101.bin
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <cmath>
#include <sstream>

using namespace std;

// #################################### Helper functions ######################################
template<typename T>
std::string coll_to_string(const T& iterable) {
    // static_assert(std::is_same_v<typename T::value_type, typename T::value_type>(), "Object must be iterable.");
    std::ostringstream oss;
    auto it = iterable.begin();
    if (it != iterable.end()) {
        oss << *it++;
    }
    for (; it != iterable.end(); ++it) {
        oss << ", " << *it;
    }
    return oss.str();
}

// q 605
bool canPlaceFlowers(vector<int>& flowerbed, int n) {
  int max_new_flowers = 0;
  int size = flowerbed.size();
  if (size == 1) {
    return flowerbed[0] == 0 ? n <= 1 : n <= 0;
  } else if (size == 2) {
    return flowerbed[0] + flowerbed[1] == 0 ? n <= 1 : n <= 0;
  } else {
    for (int i = 0; i < size - 2; i++) {
      if (max_new_flowers >= n) {
        return true;
      }
      if (i == 0 && flowerbed[i] == 0 && flowerbed[i+1] == 0) {
        flowerbed[i] = 1;
        max_new_flowers++;
      } else if (flowerbed[i] == 0 && flowerbed[i+1] == 0 && flowerbed[i+2] == 0) {
        flowerbed[i+1] = 1;
        max_new_flowers++;
      }
    }
    if (flowerbed[size-2] == 0 && flowerbed[size-1] == 0) {
      flowerbed[size-1] = 1;
      max_new_flowers++;
    }
  }
  return n <= max_new_flowers;
}

// q 452
int findMinArrowShots(vector<vector<int>>& points) {
    if (points.size() == 1) {
      return 1;
    }
    sort(points.begin(), points.end(), [](vector<int>& a, vector<int>& b){ return a[0] == b[0] ? a[1] < b[1] : a[0] < b[0]; });
    for (vector<int> vec: points) {
      cout << '[' << vec[0] << ", " << vec[1] << "], ";
    }
    int index = 0;
    int num_shots = 0;
    while (index < points.size()) {
      int overlap_start = points[index][0];
      int overlap_end = points[index][1];
      while (index < points.size()) {
        overlap_start = max(overlap_start, points[index][0]);
        overlap_end = min(overlap_end, points[index][1]);
        // This line is originally in the loop condition, which leads to wrong answer
        if (overlap_start > overlap_end) {
          break;
        }
        index++;
      }
      num_shots++;
    }
    return num_shots;
}

// q 763
// 0. get the letter list.
// 1. Get the first and last appearance of each letter.
// 2. Remove all the index between all first and last indices of all letters.
// 3. Calculate the length of each segment.
vector<int> partitionLabels(string s) {
  if (s.size() == 1) {
    return {(int) s.length()};
  }
  // step 1
    unordered_set<char> char_set;
    for (char c : s) {
      char_set.insert(c);
    }

    // step 2
    vector<vector<int>> start_end_vec;
    for (char ch: char_set) {
      int first_index = s.find(ch);
      int last_index = s.rfind(ch);
      start_end_vec.push_back({first_index, last_index});
    }

    // step 3
    vector<bool> can_split(s.size() - 1, true);
    for (vector<int> vec : start_end_vec) {
      fill(can_split.begin() + vec[0], can_split.begin() + vec[1], false);
    }
    for (int i: can_split) {
      cout << i <<",";
    }
    cout << endl;

    // step 4
    vector<int> output;
    int split_len = 1;
    for (int i = 0; i < can_split.size() +1; i++) {
      if (can_split[i] == 1 || i == can_split.size()) {
        output.push_back(split_len);
        split_len = 1;
      } else {
        split_len++;
      }
    }
    return output;
}

// q 122
// make full use of every rise, and avoid every drop
int maxProfit(vector<int>& prices) {
  if (prices.size() == 1) {
    return 0;
  }
  int profit = 0;
  for (int i = 0; i < prices.size() - 1; i++) {
    if (prices[i+1] > prices[i]) {
      profit += (prices[i+1] - prices[i]);
    }
  }
  return profit;
}

// q 76 (not solved)
// 0. Edge cases
// 1. Move the l and r pointers on s to have a first minimal window that contains all chars in t.
//  -- 1.1 Get the hash table of all the chars in t and their frequency.. 
//  -- 1.2 Make l to index 0, and move r to a index that make the window contains all the chars in t. (initial window)
//  -- 1.3 Record the minimal window's l and r.
// 2. Move l to the next one thus breaks the condition, and then move r to make the window satisfy the condition again. Repeat until there is no more window.
//  -- 2.1 Criteria of no more window: r reaches the end of s, but condition is still not satisfied || 
string minWindow(string s, string t) {
  // 0. Edge cases.
  if (s.size() < t.size()) {
    return "";
  } else if (t.size() == 1) {
    return s.find(t[0]) == string::npos ? "" : t;
  }

  // step 1
  // 1.1
  unordered_map<char, int> t_char_map;
  for (char c : t) {
    if (t_char_map.contains(c)) {
      t_char_map[c] += 1;
    } else {
      t_char_map.insert({c, 1});
    }
  }

  // 1.2
  int l = 0, r = 0;
  unordered_map<char, int> window_char_map;
  unordered_map<char, int> lacked_chars = t_char_map;


  while (r < s.size()) {
    cout << "r: " << r << endl;
    char r_char = s[r];
    if (window_char_map.contains(r_char)) {
      ++window_char_map[r_char];
    } else {
      window_char_map.insert({r_char, 1});
    }
    if (lacked_chars.contains(r_char)) {
      if (lacked_chars[r_char] == 1) {
        lacked_chars.erase(r_char);
      } else {
        --lacked_chars[r_char];
      }
    }
    if (lacked_chars.size() == 0) {
      break;
    }
    if (r >= s.size() - 1) {
      return "";
    }
    ++r;
  }

  cout << "l: " << l << ", r:" << r << ", min_window: " << s.substr(l, r + 1 - l) << endl;

  // 1.3
  int mw_l = l, mw_r = r;

  // 2
  while (r < s.size()) {
    while (l < r) {
      --window_char_map[s[l]];
      if (t_char_map.contains(window_char_map[s[l]]) && window_char_map[s[l]] < t_char_map[s[l]]) {
        mw_l = l;
        lacked_chars.insert({s[l], 1});
        break;
      }
      ++l;
    }
    while(r < s.size()) {
      char r_char = s[r];
      if (window_char_map.contains(r_char)) {
        ++window_char_map[r_char];
      } else {
        window_char_map.insert({r_char, 1});
      }
      if (lacked_chars.contains(r_char)) {
        if (lacked_chars[r_char] == 1) {
          lacked_chars.erase(r_char);
        } else {
          --lacked_chars[r_char];
        }
      }
      if (lacked_chars.size() == 0) {
        mw_r = r;
        break;
      }
      ++r;
    }
    if (r == s.size() - 1) {
      break;
    }
    cout << "l: " << l << ", r:" << r << ", min_window: " << s.substr(l, r + 1 - l) << endl;
  }
  return s.substr(mw_l, mw_r + 1 - mw_l);
}


// q 633
bool judgeSquareSum(int c) {
    if (c < 2) {
      return true;
    }
    for (int a = 0; a <= floor(sqrt(c)); a++) {
      int remain = c - a*a;
      int remain_sqrt = sqrt(remain);
      if (remain_sqrt * remain_sqrt == remain) {
        return true;
      }
    }
    return false;
}

// q680
// 1. 2 pointers l and r from begin and end
// 2. If encounterING 1 not equal char, try whether skipping each of them is ok.
bool validPalindrome(string s) {
    if (s.size() < 2) {
      return true;
    } else if (s.size() == 2) {
      return s[0] == s[1];
    }
    int l = 0, r = s.size() - 1;
    while (l < r) {
      if (s[l] == s[r]) {
        ++l;
        --r;
      } else {
        bool case1= true;
        int l1 = l+1;
        bool case2 = true;
        int r1 = r-1;
        while (l1 < r) {
          if (s[l1] != s[r]) {
            case1 = false;
            break;
          }
          ++l1;
          --r;
        }
        if (case1) {
          return true;
        }
        while (l < r1) {
          if (s[l] != s[r1]) {
            case2 = false;
            break;
          }
          ++l;
          --r1;
        }
        return case2;
      }
    }
    return true;
}

// helper function for q 540, to check whether the single element is to the left or right to mid, or at the mids
// return -1 if at left, 1 if at the right, and 0 if at the mid
// 1 <= nums.length <= 10^5
// 0 <= mid < 10^5
int posOfSingleNode(vector<int>& nums, int mid) {
  if (nums.size() == 1) {
    return 0;
  }
  if (mid == 0) {
    return nums[mid] == nums[mid + 1] ? 1 : 0;
  } else if (mid == nums.size() - 1) {
    return nums[mid] == nums[mid - 1] ? -1 : 0;
  }
  if (nums[mid] == nums[mid - 1]) {
    return mid % 2 == 0 ? -1 : 1;
  } else if (nums[mid] == nums[mid + 1]) {
    return mid % 2 == 0 ? 1 : -1;
  } else {
    // cout << "nums[mid] is the single node" << mid << ", " << nums[mid] << endl;
    return 0;
  }
}

// q 540
// 1 <= nums.length <= 10^5
// 0 <= nums[i] <= 10^5
int singleNonDuplicate(vector<int>& nums) {
    if (nums.size() == 1) {
      return nums[0];
    }
    int l = 0, r = nums.size() - 1;
    int mid;
    while (l <= r) {
      mid = l + (r - l) / 2;
      // cout << l << ", " << mid << ", " << r << endl;
      if (posOfSingleNode(nums, mid) == 0) {
        return nums[mid];
      } else if (posOfSingleNode(nums, mid) == -1) {
        r = mid - 1;
      } else {
        l = mid + 1;
      }
    }
    if (mid >= 0 && mid < nums.size()) {
      return nums[mid];
    }
    return -1;
}

// q 451
string frequencySort(string s) {
    if (s.size() < 2) {
      return s;
    }
    unordered_map<char, int> map;
    int max_count = 0;
    for (const char & c: s) {
      ++map[c];
      max_count = max(max_count, map[c]);
    }
    // for (auto p : map) {
    //   cout << p.first << ", " << p.second << endl;
    // }
    vector<vector<char>> bucket(max_count + 1);
    for (const auto & [key, value] : map) {
      bucket[value].push_back(key);
    }
    string strr = "";
    for (int i = max_count; i >= 0; --i) {
      for (const char & c : bucket[i]) {
        strr.append(string(i, c));
      }
    }
  return strr;
}

// q 75
void sortColors(vector<int>& nums) {
    vector<int> color_counts(3, 0);
    for (const int & color : nums) {
      ++color_counts[color];
    }
    color_counts[1] += color_counts [0];
    color_counts[2] += color_counts[1];
    // cout << to_string(color_counts) << endl;
    for (int i = 0; i < nums.size(); ++i) {
      if (i < color_counts[0]) {
        nums[i] = 0;
      } else if (i < color_counts[1]) {
        nums[i] = 1;
      } else {
        nums[i] = 2;
      }
    }
}

// q 257
// 1. Define a helpter function, that has inputs: a node, the path string till now, and the ref of answer vector, and has the output: void.
// 2. If the current node's both left and right pointer is null, append the current node's value to the path string and return.
// 3. If any of left or right node is not null, call the helper function to left or right node by add the current val to the path string.
struct TreeNode {
  int val;
  TreeNode *left;
  TreeNode *right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

void dfs_q257(TreeNode * node, string path, vector<string> & ans) {
  if (node->left == nullptr && node->right == nullptr) {
    ans.push_back(path);
    return;
  }
  if (node->left != nullptr) {
    dfs_q257(node->left, path+"->"+to_string(node->left->val), ans);
  }
  if (node->right != nullptr) {
    dfs_q257(node->right, path+"->"+to_string(node->right->val), ans);
  }
}
 
vector<string> binaryTreePaths(TreeNode * root) {
    vector<string> ans;
    if (root == nullptr) {
      return ans;
    }
    dfs_q257(root, to_string(root->val), ans);
    return ans;
}

// q 47
// 1. Define a search function that has the inputs: pos, list, ans
// 2. If pos != last: swap from pos till the last that do not duplicate
void dfs_q47(size_t pos, size_t n, vector<int> & nums, vector<vector<int>> & ans) {
  if (pos == n) {
    ans.push_back(nums);
    return;
  }
  unordered_set<int> iterated_elem;
  for (size_t i = pos; i < n; ++i) {
    if (iterated_elem.count(nums[i]) == 0) {
      swap(nums[pos], nums[i]);
      dfs_q47(pos+1, n, nums, ans);
      swap(nums[pos], nums[i]);
      iterated_elem.insert(nums[i]);
    }
  }
}

vector<vector<int>> permuteUnique(vector<int>& nums) {
  vector<vector<int>> ans;
  unordered_set<int> iterated_elem;
  dfs_q47(0, nums.size(), nums, ans);
  return ans;
}

// q 91 -- use O(n) space complexity
int numDecodings(string s) {
  int n = s.length();
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return s[0] > '0' ? 1 : 0;
  }
  vector<int> dp(n, 0);
  if (s[0] == '0') {
    return 0;
  }
  dp[0] = 1;
  int num = (s[0] - '0')*10 + s[1] - '0';
  if (num == 10 || num == 20) {
    dp[1] = 1;
  } else if (num > 26) {
    dp[1] = s[1] == '0' ? 0 : 1;
  } else {
    dp[1] = 2;
  }
  for (int i = 2; i < n; ++i) {
    int prev = s[i-1] - '0';
    int cur = s[i] - '0';
    if (cur == 0 && !(prev == 1 || prev == 2)) {
      return 0;
    } else if (cur == 0 && (prev == 1 || prev == 2)) {
      dp[i] = dp[i-2];
    } else if ((prev == 1 && cur > 0) || (prev == 2 && cur > 0 && cur < 7)) {
      dp[i] = dp[i-1] + dp[i-2];
    } else {
      dp[i] = dp[i-1];
    }
  }
  return dp[n - 1];
}

// q 91 -- use O(1) space complexity
int numDecodings_small_space(string s) {
  int n = s.length();
  if (n == 0) {
    return 0;
  } else if (n == 1) {
    return s[0] > '0' ? 1 : 0;
  }
  int dp_pprev = 0, dp_prev = 0, dp_curr = 0;
  if (s[0] == '0') {
    return 0;
  }
  dp_pprev = 1;
  int num = (s[0] - '0')*10 + s[1] - '0';
  if (num == 10 || num == 20) {
    dp_prev = 1;
  } else if (num > 26) {
    dp_prev = s[1] == '0' ? 0 : 1;
  } else {
    dp_prev = 2;
  }
  dp_curr = dp_prev;
  for (int i = 2; i < n; ++i) {
    int prev = s[i-1] - '0';
    int cur = s[i] - '0';
    if (cur == 0 && !(prev == 1 || prev == 2)) {
      return 0;
    } else if (cur == 0 && (prev == 1 || prev == 2)) {
      dp_curr = dp_pprev;
    } else if ((prev == 1 && cur > 0) || (prev == 2 && cur > 0 && cur < 7)) {
      dp_curr = dp_pprev + dp_prev;
    } else {
      dp_curr = dp_prev;
    }
    dp_pprev = dp_prev;
    dp_prev = dp_curr;
  }
  return dp_curr;
}

int main() {
  string s = "226";
  int output = numDecodings_small_space(s);
  cout << output << endl;
  return 0;
}
