#include<iostream>

template<typename T1, typename T2>
struct Pair {
    T1 first;
    T2 second;

    Pair(const T1& first, const T2& second) : first(first), second(second) {}
    Pair(const Pair& otehr) = default;
    Pair& operator=(const Pair& other) = delete;
    bool operator<(const Pair& other) const {
        if(this->first < other.first) return true;
        else if(other.first < this->first) return false;
        else return this->second < other.second;
    }

    bool operator>(const Pair& other) const {
        if(other.first < this->first) return true;
        else if(this->first < other.first) return false;
        else return other.second < this->second;
    }

    bool operator==(const Pair& other) const {return !( (*this < other) || (other < *this) );}
    
    friend std::ostream& operator<<(std::ostream& out, const Pair<T1, T2>& p) {
        out << "(" << p.first << ", " << p.second << ")";
        return out;
    }
};