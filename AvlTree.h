#pragma once
#include "Tree.h"
#include "Stack.h"

template<typename T>
class AvlTree : public Tree<T, AvlBlock<T>>{
    public:
    AvlTree() : Tree<T, AvlBlock<T>>(){}
    void Add(const T& data) override;
    void Remove(const T& id) override;

    private:
    AvlBlock<T>* Lroll(AvlBlock<T>* parent);
    AvlBlock<T>* Rroll(AvlBlock<T>* parent);
    AvlBlock<T>* LLroll(AvlBlock<T>*& parent, AvlBlock<T>* child);
    AvlBlock<T>* LRroll(AvlBlock<T>*& parent, AvlBlock<T>* child);
    AvlBlock<T>* RLroll(AvlBlock<T>*& parent, AvlBlock<T>* child);
    AvlBlock<T>* RRroll(AvlBlock<T>*& parent, AvlBlock<T>* child);
    void Update(Stack<AvlBlock<T>*>& path);
    void Reconnect(AvlBlock<T>* block, Stack<AvlBlock<T>*>& path);
    void Remove(AvlBlock<T>*& toRem, Stack<AvlBlock<T>*>& path);
    AvlBlock<T>*& GetMin(AvlBlock<T>* toRem, Stack<AvlBlock<T>*>& path);
};

//public funcs implementation:
template<typename T>
void AvlTree<T>::Add(const T& data) {
    Stack<AvlBlock<T>*> path;
    AvlBlock<T>* curr = this->root;

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


template <typename T>
void AvlTree<T>::Remove(const T& id){
    //note: throughout this func toRem is the AvlBlock with data id

    Stack<AvlBlock<T>*> path;

    //if toREm is root - Remove root
    if(this->root->data == id){
        Remove(this->root, path);
        Update(path);
        return;
    }
    
    //Search The Tree
    AvlBlock<T>* curr = this->root;
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

template<typename T>
AvlBlock<T>* AvlTree<T>::Lroll(AvlBlock<T>* parent){
    if(parent->left->BF() != -1){
        return LLroll(parent, parent->left);
    }
    else{
        return LRroll(parent, parent->left);
    }
}

template<typename T>
AvlBlock<T>* AvlTree<T>::Rroll(AvlBlock<T>* parent){
    if(parent->right->BF() != 1){
        return RRroll(parent, parent->right);
    }
    else{
        return RLroll(parent, parent->right);
    }
}

template<typename T>
AvlBlock<T>* AvlTree<T>::LLroll(AvlBlock<T>*& parent, AvlBlock<T>*child){
    AvlBlock<T>* temp = parent;
    parent = child;
    temp->left = child->right;
    child->right = temp;
    temp->UpdateHeight();
    child->UpdateHeight();
    return parent;
}

template<typename T>
AvlBlock<T>* AvlTree<T>::LRroll(AvlBlock<T>*& parent, AvlBlock<T>* child){
    AvlBlock<T>* grandChild = child->right;
    AvlBlock<T>* temp = parent;
    parent = grandChild;
    temp->left = grandChild->right;
    child->right = grandChild->left;
    grandChild->right = temp;
    grandChild->left = child;
    temp->UpdateHeight();
    child->UpdateHeight();
    grandChild->UpdateHeight();
    return parent;
}

template<typename T>
AvlBlock<T>* AvlTree<T>::RLroll(AvlBlock<T>*& parent, AvlBlock<T>* child){
    AvlBlock<T>* grandChild = child->left;
    AvlBlock<T>* temp = parent;
    parent = grandChild;
    temp->right = grandChild->left;
    child->left = grandChild->right;
    grandChild->left = temp;
    grandChild->right = child;
    temp->UpdateHeight();
    child->UpdateHeight();
    grandChild->UpdateHeight();
    return parent;
}

template<typename T>
AvlBlock<T>* AvlTree<T>::RRroll(AvlBlock<T>*& parent, AvlBlock<T>* child){
    AvlBlock<T>* temp = parent;
    parent = child;
    temp->right = child->left;
    child->left = temp;
    temp->UpdateHeight();
    child->UpdateHeight();
    return parent;
}

template<typename T>
void AvlTree<T>::Remove(AvlBlock<T>*& toRem, Stack<AvlBlock<T>*>& path){
    //if toRem has one or fewer children
    if(toRem->left == nullptr){
        const AvlBlock<T>* temp = toRem;
        toRem = toRem->right;
        //note that toRem is Block*& so the actual pointer in the parent will be changed
        delete temp;
        return;
    }
    else if(toRem->right == nullptr){
        AvlBlock<T>* temp = toRem;
        toRem = toRem->left;
        //similar to above
        delete temp;
        return;
    }

    //toRem has 2 children
    AvlBlock<T>* temp = toRem;

    //1: find substitute AvlBlock
    Stack<AvlBlock<T>*> top;
    AvlBlock<T>*& minRightSubtree = GetMin(toRem, top);
    AvlBlock<T>* substitute = minRightSubtree;
    path.Push(substitute);
    Stack<AvlBlock<T>*>::Merge(path, top);

    //2: substitution
    {
        minRightSubtree = minRightSubtree->right;
        substitute->right = toRem->right;
        substitute->left = toRem->left;
        toRem = substitute;
        delete temp;
    }
}

template<typename T>
void AvlTree<T>::Update(Stack<AvlBlock<T>*>& path){
    while(!path.IsEmpty()){
        AvlBlock<T>* curr = path.Pop();
        curr->UpdateHeight();
        int BF = curr->BF();
        if(BF == 2){
            AvlBlock<T>* newRoot = Lroll(curr);
            Reconnect(newRoot, path);
            continue;
        }
        if(BF == -2){
            AvlBlock<T>* newRoot = Rroll(curr);
            Reconnect(newRoot, path);
            continue;
        }
    }
}

template<typename T>
void AvlTree<T>::Reconnect(AvlBlock<T>* block, Stack<AvlBlock<T>*> &path){
    if(path.IsEmpty()){
        this->root = block;
        return;
    }
    AvlBlock<T>* temp = path.Peek();
    if(block->data < temp->data){
        temp->left = block;
    }
    else{
        temp->right = block;
    }
}

template<typename T>
AvlBlock<T>*& AvlTree<T>::GetMin(AvlBlock<T>* toRem, Stack<AvlBlock<T>*>& path){
    if(toRem->right->left == nullptr) return toRem->right;
    AvlBlock<T>* curr = toRem ->right;
    while(curr->left->left !=nullptr) { 
        path.Push(curr);
        curr = curr->left;
    }
    return curr->left;
}