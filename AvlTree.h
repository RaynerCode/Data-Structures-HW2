#pragma once
#include "Tree.h"
#include "Stack.h"

template<typename T, typename Block = AvlBlock<T>>
class AvlTree : public Tree<T, Block>{
    public:
    AvlTree() : Tree<T, Block>(){}
    void Add(const T& data) override;
    void Remove(const T& id) override;

    private:
    Block* Lroll(Block* parent);
    Block* Rroll(Block* parent);
    Block* LLroll(Block*& parent, Block* child);
    Block* LRroll(Block*& parent, Block* child);
    Block* RLroll(Block*& parent, Block* child);
    Block* RRroll(Block*& parent, Block* child);
    void Update(Stack<Block*>& path);
    void Reconnect(Block* block, Stack<Block*>& path);
    virtual void Remove(Block*& toRem, Stack<Block*>& path);
    Block*& GetMin(Block* toRem, Stack<Block*>& path);
};

//public funcs implementation:
template<typename T, typename Block>
void AvlTree<T, Block>::Add(const T& data) {
    Stack<Block*> path;
    Block* curr = this->root;

    //empty AvlTree
    if(curr == nullptr){
        this->root = this->CreateBlock(data);
        return;
    }

    //Search where the new Block needs to be added
    while(true){
        if(data < curr->data){
            path.Push(curr);
            if(curr->left == nullptr){
                curr->left = this->CreateBlock(data);
                break;
            }
            curr = curr->left;
            continue;
        }
        if(curr->data < data){
            path.Push(curr);
            if(curr->right == nullptr){
                curr->right = this->CreateBlock(data);
                break;
            }
            curr = curr->right;
            continue;
        }
        throw(std::invalid_argument("id already exists"));
    }

    //update block heights and insure structure integrity
    Update(path);
}

template<typename T, typename Block>
void AvlTree<T, Block>::Remove(const T& id){
    //note: throughout this func toRem is the AvlBlock with data id

    Stack<Block*> path;

    //if toREm is root - Remove root
    if(this->root->data == id){
        Remove(this->root, path);
        Update(path);
        return;
    }
    
    //Search The Tree
    Block* curr = this->root;
    while(true){
        if(curr == nullptr)
            throw(std::invalid_argument("data not found"));

        //if toRem is left of curr
        if(id < curr->data){
            path.Push(curr);

            //if toRem is curr's left child
            if(curr->left != nullptr && curr->left->data == id){
                Remove(curr->left, path);
                break;
            }

            //otherwise
            curr = curr->left;
            continue;
        }

        //otherwise, if toRem is right of curr
        if(curr->data < id){
            path.Push(curr);

            //if toRem is curr's right child
            if(curr->right != nullptr && curr->right->data == id){
                Remove(curr->right, path);
                break;
            }

            //otherwise
            curr = curr->right;
        }
    }
    //when the while loop above ends, toRem is not in AvlTree
    
    Update(path);

}

//private funcs implementation:

template<typename T, typename Block>
Block* AvlTree<T, Block>::Lroll(Block* parent){
    if(parent->left->BF() != -1){
        return LLroll(parent, parent->left);
    }
    else{
        return LRroll(parent, parent->left);
    }
}

template<typename T, typename Block>
Block* AvlTree<T, Block>::Rroll(Block* parent){
    if(parent->right->BF() != 1){
        return RRroll(parent, parent->right);
    }
    else{
        return RLroll(parent, parent->right);
    }
}

template<typename T, typename Block>
Block* AvlTree<T, Block>::LLroll(Block*& parent, Block*child){
    Block* temp = parent;
    parent = child;
    temp->left = child->right;
    child->right = temp;
    temp->Update();
    child->Update();
    return parent;
}

template<typename T, typename Block>
Block* AvlTree<T, Block>::LRroll(Block*& parent, Block* child){
    Block* grandChild = child->right;
    Block* temp = parent;
    parent = grandChild;
    temp->left = grandChild->right;
    child->right = grandChild->left;
    grandChild->right = temp;
    grandChild->left = child;
    temp->Update();
    child->Update();
    grandChild->Update();
    return parent;
}

template<typename T, typename Block>
Block* AvlTree<T, Block>::RLroll(Block*& parent, Block* child){
    Block* grandChild = child->left;
    Block* temp = parent;
    parent = grandChild;
    temp->right = grandChild->left;
    child->left = grandChild->right;
    grandChild->left = temp;
    grandChild->right = child;
    temp->Update();
    child->Update();
    grandChild->Update();
    return parent;
}

template<typename T, typename Block>
Block* AvlTree<T, Block>::RRroll(Block*& parent, Block* child){
    Block* temp = parent;
    parent = child;
    temp->right = child->left;
    child->left = temp;
    temp->Update();
    child->Update();
    return parent;
}

template<typename T, typename Block>
void AvlTree<T, Block>::Remove(Block*& toRem, Stack<Block*>& path){
    //if toRem has one or fewer children
    if(toRem->left == nullptr){
        const Block* temp = toRem;
        toRem = toRem->right;
        //note that toRem is Block*& so the actual pointer in the parent will be changed
        delete temp;
        return;
    }
    else if(toRem->right == nullptr){
        Block* temp = toRem;
        toRem = toRem->left;
        //similar to above
        delete temp;
        return;
    }

    //toRem has 2 children
    Block* temp = toRem;

    //1: find substitute AvlBlock
    Stack<Block*> top;
    Block*& minRightSubtree = GetMin(toRem, top);
    Block* substitute = minRightSubtree;
    path.Push(substitute);
    Stack<Block*>::Merge(path, top);

    //2: substitution
    {
        minRightSubtree = minRightSubtree->right;
        substitute->right = toRem->right;
        substitute->left = toRem->left;
        toRem = substitute;
        delete temp;
    }
}

template<typename T, typename Block>
void AvlTree<T, Block>::Update(Stack<Block*>& path){
    while(!path.IsEmpty()){
        Block* curr = path.Pop();
        curr->Update();
        int BF = curr->BF();
        if(BF == 2){
            Block* newRoot = Lroll(curr);
            Reconnect(newRoot, path);
            continue;
        }
        if(BF == -2){
            Block* newRoot = Rroll(curr);
            Reconnect(newRoot, path);
            continue;
        }
    }
}

template<typename T, typename Block>
void AvlTree<T, Block>::Reconnect(Block* block, Stack<Block*> &path){
    if(path.IsEmpty()){
        this->root = block;
        return;
    }
    Block* temp = path.Peek();
    if(block->data < temp->data){
        temp->left = block;
    }
    else{
        temp->right = block;
    }
}

template<typename T, typename Block>
Block*& AvlTree<T, Block>::GetMin(Block* toRem, Stack<Block*>& path){
    if(toRem->right->left == nullptr) return toRem->right;
    Block* curr = toRem ->right;
    if(curr->left->left == nullptr)
        path.Push(curr);
    while(curr->left->left !=nullptr) { 
        path.Push(curr);
        curr = curr->left;
    }
    return curr->left;
}