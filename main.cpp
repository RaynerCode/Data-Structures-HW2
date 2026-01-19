#include "hash.h"
#include <iostream>
#include <random>

int main() {
    std::random_device rd;

    // 2. Initialize the generator (Mersenne Twister) with the seed
    std::mt19937 gen(rd());

    // 3. Define the range [1, 10000] (inclusive)
    std::uniform_int_distribution<> distr(1, 100000);

    // 4. Generate and print the number

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
    a.setData(43, 7);
    std::cout << "new data: " << a.getValue(43) << std::endl;
    std::cout << a.getValue(43) << std::endl;
    a.setData(43, 666);
    std::cout << a.getValue(43) << std::endl;

    for(int i = 0; i < 1000; i++) {
        const int random_num = distr(gen);
        a.insert(random_num , i%7);
        std::cout << random_num << std::endl;
    }
    std::cout << a.getValue(555) << std::endl;



    return 0;
}