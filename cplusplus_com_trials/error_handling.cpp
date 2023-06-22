/* 
to compile this file, type in terminal in the root folder: 
  g++ -std=c++20 cplusplus_com_trials/error_handling.cpp -o .bin/cplusplus_com_trials@@error_handling.bin
to run the compiled binary, type in terminal in the root folder: 
  .bin/cplusplus_com_trials@@error_handling.bin
*/

#include <exception>
#include <iostream>

using namespace std;

class MyException : public std::exception {
public:
    virtual const char* what() const throw() {
        return "My Exception occurred";
    }
};

void process(int value) {
    if (value < 0) {
        throw MyException();
    }
    // Other code
}

int main() {
    try {
        process(1);
        cout << "process() successful." << endl;
    } catch (const MyException& e) {
        // Handle the exception
        std::cerr << "Exception occurred: " << e.what() << std::endl;
    }
    // Other code
    return 0;
}