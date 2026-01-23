#pragma once
#include "AvlTree.h"

template<typename T, typename Block = RankBlock<T>>
class RankTree : public AvlTree<T, Block>{
  public:
    RankTree() : AvlTree<T, Block>(){}
    const T& Get_ithRank(int i) const;

    //debug only
    void PrintInOrder() const override;
    using AvlTree<T, Block>::PrintInOrder;
    using AvlTree<T, Block>::PrintPreOrder;
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
const T& RankTree<T, Block>::Get_ithRank(int i, Block* curr) const{
  //if we got here, the ith rank surly exists
  while(curr != nullptr){
    if (i == curr->rank) {
      return curr->data;
    }
    if (i < curr->rank) {
      curr = curr->left;
    }
    else {
      i -= curr->rank;
      curr = curr->right;
    }
  }
  throw(std::runtime_error("get ith rank hit a nullptr"));
}

template<typename T, typename Block>
void RankTree<T, Block>::PrintInOrder() const {
  PrintInOrder(this->root);
}

template<typename T, typename Block>
void RankTree<T, Block>::PrintInOrder(const Block* root) const {
    if(root == nullptr)
      return;
    std::cout << "left: ";
    PrintInOrder(root->left);
    std::cout << "aura: " << root->data.value->GetSquadAura() << "id: " << root->data.value->GetSquadId() << " right: ";
    PrintInOrder(root->right);
}

template<typename T, typename Block>
void RankTree<T, Block>::PrintPreOrder(const Block* root) const {
    if(root == nullptr)
      return;
    std::cout << *root << " ";
    PrintPreOrder(root->left);
    PrintPreOrder(root->right);

}