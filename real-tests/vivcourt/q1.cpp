/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 real-tests/vivcourt/q1.cpp -o .bin/real-tests@@vivcourt@@q1.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/real-tests@@vivcourt@@q1.bin
*/

#include <vector>
#include <stdexcept>
#include <iostream>
#include <set>

using namespace std;

class MovingTotal
{
private:
    std::vector<int> nums;
    std::set<int> myset;

public:
    void append(const std::vector<int>& list)
    {
        // Append the new list to the end of the previous list
        nums.insert(nums.end(), list.begin(), list.end());
        
        // Compute the sums of 3 consecutive numbers and add them to myset
        int n = nums.size();
        for (int i = 0; i <= n - 3; i++) {
            int sum = nums[i] + nums[i + 1] + nums[i + 2];
            myset.insert(sum);
        }
        if (nums.size() >= 3) {
            nums.erase(nums.begin(), nums.begin() + (nums.size() - 3));
        }
    }

    bool contains(int total)
    {
        // Check if the total is in myset
        return myset.count(total) > 0;
    }
};

class MovingTotalUsePointers
{
private:
    int prevprev;
    int prev;
    int curr;
    short start_flag = false;
    std::set<int> myset;

public:
    void append(const std::vector<int>& list)
    {
        // Append the new list to the end of the previous list
        
        // Compute the sums of 3 consecutive numbers and add them to myset
        int n = list.size();
        for (int i = 0; i < n; ++i) {
            prevprev = prev;
            prev = curr;
            curr = list[i];
            if (start_flag < 2) {
                ++start_flag;
            } else {
                myset.insert(prevprev+prev+curr);
            }
        }
    }

    bool contains(int total)
    {
        // Check if the total is in myset
        return myset.count(total) > 0;
    }
};

#ifndef RunTests
int main()
{
    MovingTotalUsePointers movingTotal;

    std::vector<int> first;
    first.push_back(1);
    first.push_back(2);
    first.push_back(3);
    first.push_back(4);

    movingTotal.append(first);

    std::cout << movingTotal.contains(6) << std::endl;
    std::cout << movingTotal.contains(9) << std::endl;
    std::cout << movingTotal.contains(12) << std::endl;
    std::cout << movingTotal.contains(7) << std::endl;

    std::vector<int> second;
    second.push_back(5);
    movingTotal.append(second);

    std::cout << movingTotal.contains(6) << std::endl;
    std::cout << movingTotal.contains(9) << std::endl;
    std::cout << movingTotal.contains(12) << std::endl;
    std::cout << movingTotal.contains(7) << std::endl;
}
#endif