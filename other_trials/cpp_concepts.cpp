/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 other_trials/cpp_concepts.cpp -o .bin/other_trials@@cpp_concepts.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/other_trials@@cpp_concepts.bin
*/

#include <iostream>
#include <typeinfo>
#include <vector>
#include <list>

using namespace std;

/** @brief trial of list insert */
void list_insert_trial() {
  list<int> mylist;
  list<int>::iterator it;

  // set some initial values:
  for (int i=1; i<=5; ++i) mylist.push_back(i); // 1 2 3 4 5

  it = mylist.begin();
  cout << "1. it: " << *it << endl;

  ++it;       // it points now to number 2           ^
  cout << "2. it: " << *it << endl;

  mylist.insert (it,10);                        // 1 10 2 3 4 5

  // "it" still points to number 2                      ^
  mylist.insert (it,2,20);                      // 1 10 20 20 2 3 4 5
  cout << "3. it: " << *it << endl;

  --it;       // it points now to the second 20            ^
  cout << "4. it: " << *it << endl;

  vector<int> myvector (2,30);
  mylist.insert (it,myvector.begin(),myvector.end());
  cout << "5. it: " << *it << endl;
                                                // 1 10 20 30 30 20 2 3 4 5
                                                //               ^

  --it;
  cout << "6. it: " << *it << endl;

  cout << "mylist contains:";
  for (it=mylist.begin(); it!=mylist.end(); ++it) {
    cout << ' ' << *it;
  }
  cout << '\n';
}

/** @brief trial of vector erase */
void vector_erase_trial() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  int n;
  cin >> n;
  vector<int> nums(n, 0);
  for (int i = 0; i < n; ++i) {
      cin >> nums[i];
  }
  int rm_sg, rm_l, rm_r;
  cin >> rm_sg >> rm_l >> rm_r;
  nums.erase(nums.begin()+rm_sg-1);

  cout << "after 1st change: " << endl;
  for (int i = 0; i < n - 1; ++i) {
      cout << nums[i] << " ";
  }
  cout << nums[n-1] << endl;

  nums.erase(nums.begin()+rm_l-1, nums.begin()+rm_r-1);

  cout << "after 2nd change: " << endl;
  for (int i = 0; i < n - 1; ++i) {
      cout << nums[i] << " ";
  }
  cout << nums[n-1] << endl;
  
  int nn = nums.size();
  cout << "final outpu: " << endl;
  cout << nn << endl;
  // printing of nums
  for (int i = 0; i < nn - 1; ++i) {
      cout << nums[i] << " ";
  }
  cout << nums[nn-1] << endl;
}

/** @brief trial of integral_constant */
template <int n> struct twice_cons : integral_constant<int, n*2> { inline static int triple_v = 100; };
void integral_constant_trial() {
  twice_cons<7> twice_v;
  cout << twice_cons<7>::triple_v << endl;
  cout << twice_v.value << endl;
  cout << typeid(twice_cons<7>::type).name() << endl;
  cout << twice_cons<7>::value;
  cout << typeid(twice_cons<7>::value_type).name() << endl;
  twice_cons<7>::triple_v = 101;
  cout << twice_cons<7>::triple_v << endl;
  twice_v.triple_v = 102;
  cout << twice_cons<7>::triple_v << endl;
  cout << twice_cons<8>::triple_v << endl;
  cout << twice_v.triple_v << endl;
}


/** @brief trial of bitwise operations */
void bitwise_operation_trial() {
  int a = 60;	/* 60 = 0011 1100 */  
  int b = 13;	/* 13 = 0000 1101 */
  int c = 0;           

  c = a & b;       /* 12 = 0000 1100 */ 
  cout << "Line 1 - Value of c is : " << c << endl ;

  c = a | b;       /* 61 = 0011 1101 */
  cout << "Line 2 - Value of c is: " << c << endl ;

  c = a ^ b;       /* 49 = 0011 0001 */
  cout << "Line 3 - Value of c is: " << c << endl ;

  c = ~a;          /*-61 = 1100 0011 */
  cout << "Line 4 - Value of c is: " << c << endl ;

  c = a << 2;     /* 240 = 1111 0000 */
  cout << "Line 5 - Value of c is: " << c << endl ;

  c = a >> 2;     /* 15 = 0000 1111 */
  cout << "Line 6 - Value of c is: " << c << endl ;

  c = a & 1;       /* 0 = 0000 0000 */
  cout << "Line 7 - Value of c is : " << c << endl ;
}


int main() {
    bitwise_operation_trial();
    return 0;
}