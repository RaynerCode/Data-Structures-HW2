#include <iostream>

template<typename T>
struct BaseBlock{
  BaseBlock* right;
  BaseBlock* left;
  T data;

  explicit BaseBlock(const T& data) : right(nullptr), left(nullptr), data(data) {}
  virtual ~BaseBlock() = default;
  bool operator <(const BaseBlock* comp) const;
};

//BaseBlock methods

template<typename T>
bool BaseBlock<T>::operator <(const BaseBlock* comp) const{
  return this->data < comp->data;
}

template<typename T>
struct AvlBlock{
  AvlBlock* right;
  AvlBlock* left;
  T data;
  int height;
  explicit AvlBlock(const T& data) : right(nullptr), left(nullptr), data(data), height(0) {}
  void Update();
  int BF() const;
  bool operator <(const AvlBlock* comp) const;
};

//AvlBlock methods
template<typename T>
void AvlBlock<T>::Update(){
  int leftHeight = this->left == nullptr ? -1 : left->height;
  int rightHeight = this->right == nullptr ? -1 : right->height;
  this->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

template<typename T>
int AvlBlock<T>::BF() const{
  int leftHeight = this->left == nullptr ? -1 : static_cast<AvlBlock<T>*>(this->left)->height;
  int rightHeight = this->right == nullptr ? -1 : static_cast<AvlBlock<T>*>(this->right)->height;
  return leftHeight - rightHeight;
}

template<typename T>
bool AvlBlock<T>::operator<(const AvlBlock* comp)const {
  return this->data < comp->data;
}

//RankBlock
template<typename T>
struct RankBlock{
  RankBlock* right;
  RankBlock* left;
  T data;
  int height;
  int rank;
  int subTreeSize;


  int BF() const;
  bool operator <(const RankBlock* comp) const;
  explicit RankBlock(const T& data) : right(nullptr), left(nullptr), 
    data(data), height(0), rank(1), subTreeSize(1) {}
  void Update();

  friend std::ostream& operator<<(std::ostream& os, const RankBlock<T>& block){
    os << "(" << block.data << ", " << block.rank << ", " << block.subTreeSize << ")";
    return os;
  }
};

template<typename T>
bool RankBlock<T>::operator<(const RankBlock* comp) const{
  return this->data < comp->data;
}

template<typename T>
int RankBlock<T>::BF() const{
  int leftHeight = this->left == nullptr ? -1 : this->left->height;
  int rightHeight = this->right == nullptr ? -1 : this->right->height;
  return leftHeight - rightHeight;
}

//RankBlock methods
template<typename T>
void RankBlock<T>::Update() {
  int leftHeight = this->left == nullptr ? -1 : left->height;
  int rightHeight = this->right == nullptr ? -1 : right->height;
  this->height = 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
  
  subTreeSize = 1 + 
   (this->left == nullptr ? 0 : this->left->subTreeSize) +
   (this->right == nullptr ? 0 : this->right->subTreeSize);

  this->rank = (this->left == nullptr ? 0 : this->left->subTreeSize) + 1;
}