#include "AvlTree.h"

template<typename T, typename Block = RankBlock<T>>
class RankTree : public AvlTree<T, Block>{
  public:
    RankTree() : AvlTree<T, Block>(){}
    const T& Get_ithRank(int i) const;
  private:
    const T& Get_ithRank(int i, Block* curr) const;

  //debug only
    void PrintInOrder(const Block* root) const override;
    void PrintPreOrder(const Block* root) const override;
};

//public funcs implementation:
template<typename T, typename Block>
const T& RankTree<T, Block>::Get_ithRank(int i) const{
  if(this->root == nullptr || i < 1 || i > this->root->subTreeSize){
    throw(std::out_of_range("i is out of range"));
  }
  return Get_ithRank(i, this->root);
}

//private funcs implementation:
template<typename T, typename Block>
const T& RankTree<T, Block>::Get_ithRank(int i, Block* curr){
  //if we got here, the ith rank surly exists
  while(true){
    if(curr->rank < i)
    {
      i -= curr->rank;
      curr = curr->right;
      continue;
    }
    if(i < curr->rank)
    {
      curr = curr->left;
      continue;
    }
    return curr->data;
  }
}