#pragma once
#include "Pair.h"

template<typename T, typename U, typename V, typename Comp = Default>
struct Triplet{
  Pair<T, U, Comp> key;
  V value;
  explicit Triplet (const T& first, const U& second, const V& third, const Comp& comp = Comp())
      : key(Pair<T, U, Comp>(first, second, comp)), value(third) {}
  bool operator<(const Triplet& other) const;
  bool operator>(const Triplet& other) const;
  bool operator==(const Triplet& other) const;

  const Pair<T, U, Comp>& GetKey() const;
  const V& GetData() const;
  friend std::ostream& operator<<(std::ostream& out, const Triplet<T, U, V, Comp>& t) {
      out << "[" << t.key << ", " << t.value << "]";
      return out;
  }
};

template<typename T, typename U, typename V, typename Comp>
bool Triplet<T, U, V, Comp>::operator<(const Triplet& other) const {
  return this->key < other.key;
}

template<typename T, typename U, typename V, typename Comp>
bool Triplet<T, U, V, Comp>::operator>(const Triplet& other) const {
  return other.key < this->key;
}

template<typename T, typename U, typename V, typename Comp>
bool Triplet<T, U, V, Comp>::operator==(const Triplet& other) const {
  return !(*this < other || *this > other);
}


template<typename T, typename U, typename V, typename Comp>
const Pair<T, U, Comp>& Triplet<T, U, V, Comp>::GetKey() const {
  return this->key;
}

template<typename T, typename U, typename V, typename Comp>
const V& Triplet<T, U, V, Comp>::GetData() const {
  return this->value;
}