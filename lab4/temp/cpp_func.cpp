#include <iostream>
extern "C" void function_from_CPP(int a,char b[]) {
    std::cout << "This is a function from C++." << std::endl;
    std::cout << "id: "<< a <<" name: "<< b <<  std::endl;
}