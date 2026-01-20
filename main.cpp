//#include <Huntech26a2.h>

//#include "hash.h"
#include "UF.h"
#include <iostream>
#include <random>

int main() {
    // std::random_device rd;
    //
    // // 2. Initialize the generator (Mersenne Twister) with the seed
    // std::mt19937 gen(rd());
    //
    // // 3. Define the range [1, 10000] (inclusive)
    // std::uniform_int_distribution<> distr(1, 100000);
    //
    // // 4. Generate and print the number
    //
    // hashedArray<double> a;
    // a.insert(1234135, 3.14);
    // a.insert(3, 2.718);
    // a.insert(13, 2.7182);
    // a.insert(23, 2.71828);
    // a.insert(33, 4);
    // a.insert(43, 5);
    // std::cout << a.getValue(3) << std::endl;
    // std::cout << a.getValue(13) << std::endl;
    // std::cout << a.getValue(23) << std::endl;
    // std::cout << a.getValue(33) << std::endl;
    // std::cout << a.getValue(43) << std::endl;
    // a.setData(43, 7);
    // std::cout << "new data: " << a.getValue(43) << std::endl;
    // std::cout << a.getValue(43) << std::endl;
    // a.setData(43, 666);
    // std::cout << a.getValue(43) << std::endl;
    //
    // for(int i = 0; i < 1000; i++) {
    //     const int random_num = distr(gen);
    //     a.insert(random_num , i%7);
    //     std::cout << random_num << std::endl;
    // }
    //std::cout << a.getValue(555) << std::endl;
    UF a;
    std::shared_ptr<Hunter> hunter1 = std::make_shared<Hunter>(123,15,NenAbility("Enchanter"),88,11);
    std::shared_ptr<Hunter> hunter2 = std::make_shared<Hunter>(1234,15,NenAbility("Enchanter"),88,12);
    std::shared_ptr<Hunter> hunter3 = std::make_shared<Hunter>(1235,15,NenAbility("Enchanter"),88,1322);
    std::shared_ptr<Hunter> hunter4 = std::make_shared<Hunter>(21,15,NenAbility("Enchanter"),88,12);
    std::shared_ptr<Hunter> hunter5 = std::make_shared<Hunter>(22,15,NenAbility("Enchanter"),88,1322);
    std::shared_ptr<Squad> squad1 = std::make_shared<Squad>(13);
    std::shared_ptr<Squad> squad2 = std::make_shared<Squad>(15);


    a.MakeSet(123,hunter1,squad1);
    std::cout << "created set: " << a.Find(123)->GetSquadId() << std::endl;
    a.AddToSet(1234, hunter2, 123);
    std::cout << "created set: " << a.Find(1234)->GetSquadId() << std::endl;
    a.AddToSet(1235, hunter3, 1234);
    std::cout << "created set: " << a.Find(1235)->GetSquadId() << std::endl;
    a.MakeSet(21,hunter4,squad2);
    std::cout << "created set: " << a.Find(21)->GetSquadId() << std::endl;
    a.AddToSet(22, hunter5, 21);
    std::cout << "created set: " << a.Find(22)->GetSquadId() << std::endl;
    a.Union(21, 1235);
    std::cout << "united set: " << a.Find(1235)->GetSquadId() << std::endl;






    return 0;
}