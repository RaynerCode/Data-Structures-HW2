#include "Pair.h"

template<typename T>
struct Default{
  bool operator()(const T& t1, const T& t2) const {
    return t1 < t2;
  }
};

template<typename T, typename U, typename V, typename Comp = Default<Pair<T, U>>>
struct Triplet{
  Pair<T, U> key;
  V value;
  Comp c;
  explicit Triplet (const T& first, const U& second, const V& third, const Comp& comp = Comp())
      : key(Pair<T, U>(first, second)), value(third), c(comp) {}
  bool operator<(const Triplet& other) const;
  const Pair<T, U>& GetKey() const;
  const V& GetData() const;
  friend std::ostream& operator<<(std::ostream& out, const Triplet<T, U, V, Comp>& t) {
      out << "[" << t.key << ", " << t.value << "]";
      return out;
  }
};

template<typename T, typename U, typename V, typename Comp>
bool Triplet<T, U, V, Comp>::operator<(const Triplet& other) const {
  return c(this->key, other.key);
}

template<typename T, typename U, typename V, typename Comp>
const Pair<T, U>& Triplet<T, U, V, Comp>::GetKey() const {
  return this->key;
}

template<typename T, typename U, typename V, typename Comp>
const V& Triplet<T, U, V, Comp>::GetData() const {
  return this->value;
}