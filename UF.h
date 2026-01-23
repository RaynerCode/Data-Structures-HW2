#pragma once
#include "hash.h"
#include "Stack.h"
#include "hunter.h"
#include <memory>

class UF{

  hashedArray<std::shared_ptr<Hunter>> item_data;

  public:

    UF();

    //Creates a new set. Make sure item and group don't already exist (Data set doesn't check for those. It does check for key duplication errors).
    void MakeSet(int key, const std::shared_ptr<Hunter> &item, const std::shared_ptr<Squad> &Set);

    //Adds a new item to an existing set.
    void AddToSet(int key, const std::shared_ptr<Hunter>& item, int group_member_key);

    //Unites key2's set into key1's set.
    void Union(int key1, int key2);

    void ForceUnion(std::shared_ptr<Squad> set1, std::shared_ptr<Squad> set2);

    //Finds the key's set.
    std::shared_ptr<Squad> Find(int key);

    //returns the number of fights a hunter had.
    int GetHunterFightsHad(int key);

    //returns the sum of nen ability of all hunters in the set up to key.
    NenAbility GetPartialNen(int key);

  private: //helper functions

  /*
  Compresses the paths of all items in the stack. 
  It is asumed that the stack contanis a valid path  
  from one of the roots direct children (not containing root) to a leaf.
  */
  void PathCompress(Stack<int>& path);

  int FindRoot(int key);
};