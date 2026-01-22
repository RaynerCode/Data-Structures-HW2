#pragma once
#include<iostream>

struct Default{
    template<typename P>
    bool operator()(const P& p1, const P& p2) const {
    return p1.first < p2.first;
  }
};

template<typename T1, typename T2, typename Comp = Default>
struct Pair {
    T1 first;
    T2 second;
    Comp c;

    Pair(const T1& first, const T2& second, Comp comp = Comp()) : first(first), second(second), c(comp) {}
    Pair(const Pair& otehr) = default;
    Pair& operator=(const Pair& other) = delete;
    bool operator<(const Pair& other) const {
        return c(*this, other);
    }

    bool operator>(const Pair& other) const {
        return c(other, *this);
    }

    bool operator==(const Pair& other) const {return !( (*this < other) || (other < *this) );}
    
    friend std::ostream& operator<<(std::ostream& out, const Pair& p) {
        out << "(" << p.first << ", " << p.second << ")";
        return out;
    }
};