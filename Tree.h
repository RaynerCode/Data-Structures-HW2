#pragma once
#include<stdexcept>
#include "Block.h"

template<typename T, typename Block = BaseBlock<T>>
class Tree{
  protected:
    Block* root;

  public:
    Tree() : root(nullptr) {}
    Tree(const Tree& other);
    virtual ~Tree();
    T& Find(const T& t);
    virtual void Add(const T& data);
    virtual void Remove(const T& t);
    virtual bool IsEmpty() const;

  protected:
  //helper functions
    Block* CopySubTree(const Block* otherRoot) const;
    void DeleteSubTree(Block* curr) noexcept;
    void Add(const T& data, Block* root);
    void Remove(const T& t, Block*& root);
    Block* CreateBlock(const T& data);
    Block* GetBlock(const T& t) const;
    Block*& GetMin(Block*& curr) const;
  };

//Tree methods
template<typename T, typename Block>
Tree<T, Block>::Tree(const Tree& other) : root(nullptr) {
  if(other.root == nullptr) return;
  //preorder traversal copy
  this->root = CreateBlock(other.root->data);
  this->root->left = CopySubTree(other.root->left);
  this->root->right = CopySubTree(other.root->right);
}

template<typename T, typename Block>
Tree<T,Block>::~Tree(){
  if(this->root == nullptr) return;
  DeleteSubTree(this->root);
}

template<typename T, typename Block>
T& Tree<T, Block>::Find(const T& t){
  Block* found = GetBlock(t);
  if(found == nullptr) {
    throw(std::invalid_argument("t not found"));
  }
  return found->data;
}

template<typename T, typename Block>
void Tree<T, Block>::Add(const T& data){
  if(this->root == nullptr){
    this->root = CreateBlock(data);
    return;
  }
  Add(data, this->root);
}

template<typename T, typename Block>
void Tree<T, Block>::Remove(const T& t) {
  Remove(t, this->root);
}

//helper functions
template<typename T, typename Block>
Block* Tree<T, Block>::CopySubTree(const Block* other) const{
  if(other == nullptr)
    return nullptr;
  Block* newRoot = CreateBlock(other->data);
  newRoot->left = CopySubTree(other->left);
  newRoot->right = CopySubTree(other->right);
  return newRoot;
}

template<typename T, typename Block>
void Tree<T, Block>::DeleteSubTree(Block* curr) noexcept{
  if(curr->left != nullptr)
    DeleteSubTree(curr->left);
  if(curr->right != nullptr)
    DeleteSubTree(curr->right);
  delete curr;
}

template<typename T, typename Block>
void Tree<T, Block>::Add(const T& t, Block* root){
  //left step
  if(t < root->data){
    if(root->left == nullptr){
      root->left = CreateBlock(t);
      return;
    }
  Add(t, root->left);
  return;
  }
  //right step
  if(root->data < t){
    if(root->right == nullptr){
      root->right = CreateBlock(t);
      return;
    }
    Add(t, root->right);
    return;
  }
  // !< and !> -> =
  throw(std::invalid_argument("id already exists"));
}

template<typename T, typename Block>
void Tree<T, Block>::Remove(const T& t, Block*& root){
  //no block with identifier t
  if(root == nullptr)
    throw(std::invalid_argument("data not found"));
  //recursive step
  if(t < root->data)
    Remove(t, root->left);
  else if(root->data < t)
    Remove(t, root->right);
  else{
    //root is the block to remove

    //1 or less children
    if(root->left == nullptr){
      Block* temp = root;
      root = root->right; 
      //note that root is Block*& so the actual pointer in the parent will be changed
      delete temp;
    }
    else if(root->right == nullptr){
      Block* temp = root;
      root = root->left; 
      //similar to above
      delete temp;
    }
    //2 children
    else{
      //get all needed pointers
      Block*& minRightSubtree = GetMin(root->right);
      Block* minPtr = minRightSubtree;
      Block* temp = root;
      //substitution
      minRightSubtree = minRightSubtree->right;
      /*
      note that the edge case of minRightSubTree being root->right is a non-issue
      because minRightSubtree = minRightSubtree->right; means root->right = root->right->right;
      */
      minPtr->right = root->right;
      minPtr->left = root->left;
      root = minPtr;
      //delete old root
      delete temp;
    }
  }
}

template<typename T, typename Block>
Block* Tree<T, Block>::CreateBlock(const T& data){
  return new Block(data);
}

template<typename T, typename Block>
Block* Tree<T, Block>::GetBlock(const T& t) const{
  Block* curr = root;
  while(curr != nullptr){
    if(t < curr->data) {
      curr = curr->left;
      continue;
    }
    if(t > curr->data) {
      curr = curr->right;
      continue;
    }
    return curr;
  }
  return nullptr;
}

template<typename T, typename Block>
Block*& Tree<T, Block>::GetMin(Block*& curr) const{
  if(curr->left == nullptr){
    return curr;
  }
  return GetMin(curr->left);
}

template<typename T, typename Block>
bool Tree<T, Block>::IsEmpty() const {
  return root == nullptr;
}
