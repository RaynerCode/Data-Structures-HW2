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
  void UpdateHeight();
  int BF() const;
  bool operator <(const AvlBlock* comp) const;
};

//AvlBlock methods
template<typename T>
void AvlBlock<T>::UpdateHeight(){
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