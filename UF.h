#include "hash.h"
#include "Stack.h"
#include "wet2util.h"
#include <memory>

class Hunter{
  public:
  void SetFightHad(int fights);
  int GetFightsHad() const;
  NenAbility& GetNenAbility();
};
class Squad;

class UF{
  hashedArray<int> parent;
  hashedArray<std::shared_ptr<Hunter>> item_data;
  hashedArray<std::shared_ptr<Squad>> Set_data;
  hashedArray<NenAbility> partial_nen_ability;
  public:

    UF();

    //Creates a new set. Make sure the key, item and group don't already exist (Data set doesn't check for that).
    void MakeSet(int key, std::shared_ptr<Hunter> item, std::shared_ptr<Squad> Set);

    //Adds a new item to an existing set.
    void AddToSet(int key, std::shared_ptr<Hunter> item, int group_member_key);

    //Unites key2's set into key1's set.
    void Union(int key1, int key2);

    //Finds the key's set.
    std::shared_ptr<Squad> Find(int key);

    //returns the number of fights a hunter had.
    int GetHunterFightsHad(int key);

    //returns the sum of nen ability of all hunters in the set up to key.
    NenAbility& GetPartialNenAbility(int key);

  private: //helper functions

  /*Compresses the paths of all items in the stack. 
  /It is asumed that the stack contanis a valid path  
  /from one of the roots direct children (not containing root) to a leaf.
  */
  void PathCompress(Stack<int>& path);

  //Updates the roots of two sets after union.
  void UpdateRoot(int root_key1, int root_key2);
};

//public methods:

UF::UF(): parent(), item_data(), Set_data() {}

void UF::MakeSet(int key, std::shared_ptr<Hunter> item, std::shared_ptr<Squad> Set){
  parent.insert(key, -1); //-1 indicates that it is the root of the set.
  item_data.insert(key, item);
  Set_data.insert(key, Set);
}

void UF::AddToSet(int key, std::shared_ptr<Hunter> item, int group_mermber_key){
  int parant_key = parent.getValue(group_mermber_key);
  while (parant_key != -1)
    parant_key = parent.getValue(parant_key);
  parent.insert(key, parant_key);
  item_data.insert(key, item);
  Set_data.insert(key, nullptr); //Set data is only stored at the root.

  item.get()->SetFightHad(item.get()->GetFightsHad() - item_data.getValue(parant_key).get()->GetFightsHad());
}

void UF::Union(int key1, int key2){
  Stack<int> path1, path2;
  int parant_key1 = key1, parant_key2 = key2;


  while(parent.getValue(parant_key1) != -1){
    path1.Push(parant_key1);
    parant_key1 = parent.getValue(parant_key1);
  }

  PathCompress(path1);

  while(parent.getValue(parant_key2) != -1){
    path2.Push(parant_key2);
    parant_key2 = parent.getValue(parant_key2);
  }

  if(parant_key1 == parant_key2) return; //already in the same set.

  PathCompress(path2); //If we recived the same set twice, can't gurentee path2's validity.

  UpdateRoot(parant_key1, parant_key2);
}

std::shared_ptr<Squad> UF::Find(int key){
  if(parent.getValue(key) == -1) return Set_data.getValue(key);

  Stack<int> path;
  int parant_key = key;
  while(parent.getValue(parant_key) != -1){
    path.Push(parant_key);
    parant_key = parent.getValue(parant_key);
  }

  PathCompress(path);

  return Set_data.getValue(parant_key);
}

int UF::GetHunterFightsHad(int key){
  if(parent.getValue(key) == -1) return item_data.getValue(key).get()->GetFightsHad();

  Stack<int> path;
  int parant_key = key;
  int total_fights = item_data.getValue(key).get()->GetFightsHad();
  while(parent.getValue(parant_key) != -1){
    path.Push(parant_key);
    parant_key = parent.getValue(parant_key);
    total_fights += item_data.getValue(parant_key).get()->GetFightsHad();
  }

  PathCompress(path);

  return total_fights;
}

NenAbility& UF::GetPartialNenAbility(int key){
  //ToDo
}

//private helper methods:

void UF::PathCompress(Stack<int>& path){
  if(path.IsEmpty()) return;
  
  int parant_key = parent.getValue(path.Peek());
  int fights_to_add = item_data.getValue(path.Pop()).get()->GetFightsHad();
  while(!path.IsEmpty()){
    Hunter& hunter = *(item_data.getValue(path.Peek()).get());
    int temp = hunter.GetFightsHad();
    hunter.SetFightHad(hunter.GetFightsHad() + fights_to_add);
    fights_to_add += temp;
    parent.SetData(path.Pop(), parant_key);
  }
}

void UF::UpdateRoot(int root_key1, int root_key2){

}