#pragma once
#include "Pair.h"
#include "Block.h"

constexpr unsigned int primesPowerOfTwo[] = {2u, 3u, 5u, 11u, 17u, 37u, 67u, 131u, 257u, 521u, 1031u, 2053u, 4099u, 8209u, 16411u, 32771u, 65537u, 131101u, 262147u, 524309u, 1048583u, 2097169u, 4194319u, 8388617u, 16777259u, 33554467u, 67108879u, 134217757u, 268435459u, 536870923u, 1073741827u, 2147483659u};

//template<typename T>
// struct BaseBlock{
//     BaseBlock* next;
//     T data;
//
//     explicit BaseBlock(const T& data) : next(nullptr), data(data) {}
//     virtual ~BaseBlock() = default;
// };

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
    unsigned int current_count;
    int prime_index;
    unsigned int m_size_array;
    void doubleHashSize();
public:
    ~hashedArray();
    explicit hashedArray();
    void insert(int key, T value);
    void setData(int key, T value);
    hashedArray(const hashedArray& other);
    hashedArray& operator=(const hashedArray& other);
    T& getValue(int key) const;
    bool doesExist(int key) const;
};

inline int hash(const int key, const int m) { //up to implementation, currently it is k%m.
    return key % m;
}

template<typename T>
hashedArray<T>::~hashedArray() {
    delete[] m_array;
}


template<typename T>
hashedArray<T>::hashedArray(const hashedArray &other) :
current_count(other.current_count), prime_index(other.prime_index) , m_size_array(other.m_size_array)
{
    m_array = new item<T>[m_size_array];
    for(unsigned int i = 0; i < m_size_array; i++) {
        m_array[i] = other.m_array[i];
    }
}

template<typename T>
hashedArray<T> &hashedArray<T>::operator=(const hashedArray &other) {
    if(this != &other) {
        delete[] m_array;
        current_count = other.current_count;
        prime_index = other.prime_index;
        m_size_array = other.m_size_array;
        m_array = new item<T>[m_size_array];
        for(unsigned int i = 0; i < m_size_array; i++) {
            m_array[i] = other.m_array[i];
        }
    }
    return *this;
}


template<typename T>
hashedArray<T>::hashedArray() {
    prime_index = 2;
    m_size_array = primesPowerOfTwo[prime_index];
    current_count = 0;
    m_array = new item<T>[m_size_array];
}

template<typename T>
void hashedArray<T>::insert(const int key, T value) {
    int index = hash(key, this->m_size_array);
    if(m_array[index].head == nullptr) {
        m_array[index].head = new BaseBlock<Pair<int,T>>(Pair<int,T>(key, value));
        m_array[index].last = m_array[index].head;
    }
    else {
        m_array[index].last->right = new BaseBlock<Pair<int,T>>(Pair<int,T>(key, value));
        m_array[index].last = m_array[index].last->right;
    }
    current_count++;
    if(current_count == m_size_array) {
        doubleHashSize();
    }
}

template<typename T>
T& hashedArray<T>::getValue(const int key) const {
    int index = hash(key, this->m_size_array);
    BaseBlock<Pair<int,T>>* curr = m_array[index].head;
    while(curr != nullptr) {
        if(curr->data.first == key) {
            return curr->data.second;
        }
        curr = curr->right;
    }
    throw(std::invalid_argument("key not found")); //key not in array should really throw an exception
}

template<typename T>
bool hashedArray<T>::doesExist(int key) const {
    int index = hash(key, this->m_size_array);
    BaseBlock<Pair<int,T>>* curr = m_array[index].head;
    while(curr != nullptr) {
        if(curr->data.first == key) {
            return true;
        }
        curr = curr->right;
    }
    return false;
}

template<typename T>
item<T>::~item() {
    BaseBlock<Pair<int,T>>* curr = this->head;
    BaseBlock<Pair<int,T>>* next;
    while(curr != nullptr) {
        next = curr->right;
        delete curr;
        curr = next;
    }
}

template<typename T>
void hashedArray<T>::doubleHashSize() {
    //static_assert(current_count > m_size_array / 2, "can double only if count exceeds half");
    item<T>*  old_array = m_array;
    unsigned int new_array_size = primesPowerOfTwo[++prime_index];
    m_array = new item<T>[new_array_size];
    unsigned int old_array_size = m_size_array;
    this->m_size_array = new_array_size; //no bad_alloc, can procede
    this->current_count = 0;
    BaseBlock<Pair<int,T>>* current;
    int max_depth = 0;
    int current_depth = 0;
    for(unsigned int i = 0; i < old_array_size; i++) {
        if((current = old_array[i].head) != nullptr) {
            current_depth = 0;
            while(current != nullptr) {
                this->insert(current->data.first, current->data.second);
                current = current->right;
                current_depth++;
                if(current_depth > max_depth) max_depth = current_depth;
            }
        }
    }
    //all is inserted to new array
    delete[] old_array;
}

template<typename T>
void hashedArray<T>::setData(int key, T value) {
    unsigned int index = hash(key, this->m_size_array);
    auto current = this->m_array[index].head;
    while(current != nullptr) {
        if(current->data.first == key) {
            current->data.second = value;
            return;
        }
        current = current->right;
    }
    throw(std::invalid_argument("key not found"));
}
