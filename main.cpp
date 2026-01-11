#include "hash.h"
#include <iostream>
int main() {
    hashedArray<double> a;
    a.insert(1234135, 3.14);
    a.insert(3, 2.718);
    a.insert(13, 2.7182);
    a.insert(23, 2.71828);
    a.insert(33, 4);
    a.insert(43, 5);
    std::cout << a.getValue(3) << std::endl;
    std::cout << a.getValue(13) << std::endl;
    std::cout << a.getValue(23) << std::endl;
    std::cout << a.getValue(33) << std::endl;
    std::cout << a.getValue(43) << std::endl;


    return 0;
}