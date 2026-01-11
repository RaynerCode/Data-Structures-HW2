#pragma once
#include "Pair.h"
#include <iostream>

unsigned int primesPowerOfTwo[] = {2u, 3u, 5u, 11u, 17u, 37u, 67u, 131u, 257u, 521u, 1031u, 2053u, 4099u, 8209u, 16411u, 32771u, 65537u, 131101u, 262147u, 524309u, 1048583u, 2097169u, 4194319u, 8388617u, 16777259u, 33554467u, 67108879u, 134217757u, 268435459u, 536870923u, 1073741827u, 2147483659u};

template<typename T>
struct BaseBlock{
    BaseBlock* next;
    T data;
    explicit BaseBlock(const T& data) : next(nullptr), data(data) {}
    virtual ~BaseBlock() = default;
};

template <typename T> //each cell will have one 'item' holding a head block with the first inserted T, and a last Block for easy inserting
struct item {
    BaseBlock<Pair<int,T>>* head = nullptr;
    BaseBlock<Pair<int,T>>* last = nullptr;

    item() = default;
    ~item();
};

template <typename T>
class hashedArray {
private:
    item<T>* m_array;
    int current_count;
    int prime_index;
    unsigned int m_size_array;
public:
    explicit hashedArray();
    void insert(int key, T value);
    T getValue(int key) const;
};

inline int hash(const int key, const int m) { //up to implementation, currently it is k%m.
    return key % m;
}


void doubleHashSize();
void halveHashSize();

template<typename T>
hashedArray<T>::hashedArray() {
    prime_index = 2;
    m_size_array = primesPowerOfTwo[prime_index];
    current_count = 0;
    m_array = new item<T>[m_size_array];
    std::cout << "m_array size: " << m_size_array << std::endl;
}

template<typename T>
void hashedArray<T>::insert(const int key, T value) {
    int index = hash(key, this->m_size_array);
    if(m_array[index].head == nullptr) {
        m_array[index].head = new BaseBlock<Pair<int,T>>(Pair<int,T>(key, value));
        m_array[index].last = m_array[index].head;
        std::cout << "inserting head" << std::endl;
    }
    else {
        m_array[index].last->next = new BaseBlock<Pair<int,T>>(Pair<int,T>(key, value));
        std::cout << "inserting last, last->next ptr: " << m_array[index].last->next << std::endl;
        m_array[index].last = m_array[index].last->next;
    }
}

template<typename T>
T hashedArray<T>::getValue(const int key) const {
    int index = hash(key, this->m_size_array);
    BaseBlock<Pair<int,T>>* curr = m_array[index].head;
    while(curr != nullptr) {
        if(curr->data.first == key) {
            return curr->data.second;
        }
        std::cout << "curr ptr: " << curr << std::endl;
        curr = curr->next;
    }
    return -1; //key not in array should really throw an exception
}

template<typename T>
item<T>::~item() {
    BaseBlock<Pair<int,T>>* curr = this->head;
    BaseBlock<Pair<int,T>>* next;
    while(curr != nullptr) {
        next = curr->next;
        delete curr;
        curr = next;
    }
}



