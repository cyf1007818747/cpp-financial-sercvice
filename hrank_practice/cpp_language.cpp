/*
to compile this file, type in terminal in the root folder:
  g++ -std=c++20 hrank_practice/cpp_language.cpp -o .bin/hrank_practice@@cpp_language.bin
to run the compiled binary, type in terminal in the root folder:
  .bin/hrank_practice@@cpp_language.bin
*/

#include <iostream>
using namespace std;

// @brief - scanf and formatted printing
// @headerfile - #include <iostream>
void scan_and_printf() {
    // Complete the code.
    int intt;
    long longg;
    char charr;
    float floatt;
    double doublee;
    scanf("%d %ld %c %f %lf", &intt, &longg, &charr, &floatt, &doublee);
    printf("%d\n", intt);
    printf("%ld\n", longg);
    printf("%c\n", charr);
    printf("%.3f\n", floatt);
    printf("%.9lf\n", doublee);
    return;
}

int main() {
 scan_and_printf();
 return 0;
}