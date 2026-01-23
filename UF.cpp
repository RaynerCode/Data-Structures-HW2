#include "UF.h"

//public methods:

UF::UF(): parent(), item_data(), Set_data() {}

void UF::MakeSet(const int key, const std::shared_ptr<Hunter>& item, const std::shared_ptr<Squad>& Set){
  if(HunterExists(key)) {
    throw (std::invalid_argument("id already exists"));
  }
  parent.insert(key, -1); //-1 indicates that it is the root of the set.
  item_data.insert(key, hunterNode(item));
  Set_data.insert(key, Set);
}

void UF::AddToSet(const int key, const std::shared_ptr<Hunter>& item,const int group_member_key){
  Find(group_member_key); //Finds the set to add to
  MakeSet(key, item, std::make_shared<Squad>(-1)); //create an imaginary set
  Union(group_member_key, key);
  /*unite the imaginary set with the real one.
  /Note that the imaginary set's squad is the same as the real one's
  /so it has equal member count. this means the imaginary set will always be
  /united into the real one, keeping the real one's root.
  */
}

void UF::Union(const int key1,const int key2){
  const int parent_key1 = FindRoot(key1);
  const int parent_key2 = FindRoot(key2);

  if(Set_data.getValue(parent_key1) == nullptr || Set_data.getValue(parent_key2) == nullptr)
    throw std::runtime_error("one or more sets do not exist");

  if(parent_key1 == parent_key2) return; //already in the same set.

  std::shared_ptr<Squad> set1 = Set_data.getValue(parent_key1);
  std::shared_ptr<Squad> set2 = Set_data.getValue(parent_key2);

  //Get Nodes
  hunterNode& node1 = item_data.getValue(parent_key1);
  hunterNode& node2 = item_data.getValue(parent_key2);

  if(set1->GetSquadSize() >= set2->GetSquadSize()){
    //Update root
    parent.setData(parent_key2, parent_key1);

    //Update nen
    node2.hunter_nen += (node1.sub_group_nen - node1.hunter_nen);
    node1.sub_group_nen += node2.sub_group_nen;

    //Update fights had
    node2.hunter->SetFightsHad(node2.hunter->GetFightsHad() - node1.hunter->GetFightsHad());
    //Update sets
    Set_data.setData(parent_key2, nullptr);
  }
  else{
    //Update root
    parent.setData(parent_key1, parent_key2);

    //Update nen
    node2.hunter_nen += node1.sub_group_nen;
    node1.hunter_nen -= node2.hunter_nen;

    //Update fights had
    node1.hunter->AddFightsHad(-1 * node2.hunter->GetFightsHad());

    //Update sets
    set1->mergeSquad(set2);
    Set_data.setData(parent_key2, Set_data.getValue(parent_key1));
    Set_data.setData(parent_key1, nullptr);
  }
}

std::shared_ptr<Squad> UF::Find(const int key){
  return Set_data.getValue(FindRoot(key));
}

int UF::GetHunterFightsHad(int key){
  if(parent.getValue(key) == -1) 
    return item_data.getValue(key).hunter->GetFightsHad();
  int root = FindRoot(key); //also compresses path
  return item_data.getValue(key).hunter->GetFightsHad() +
    item_data.getValue(root).hunter->GetFightsHad();
}

NenAbility UF::GetPartialNen(int key){
  if(parent.getValue(key) == -1)
    return item_data.getValue(key).hunter_nen;
  int root = FindRoot(key); //also compresses path
  NenAbility nen(item_data.getValue(key).hunter_nen);
  nen += item_data.getValue(root).hunter_nen; 
  return nen;
}

//private helper methods:

void UF::PathCompress(Stack<int>& path){
  if(path.IsEmpty()) return;

  int curr = path.Pop(), parent_key = parent.getValue(curr);
  int fights_to_add = item_data.getValue(curr).hunter->GetFightsHad();
  NenAbility partial_nen(item_data.getValue(curr).hunter_nen);
  while(!path.IsEmpty()){
    //get hunter to update
    curr = path.Peek();
    Hunter& hunter = *(item_data.getValue(curr).hunter);

    //update fights had
    int temp = hunter.GetFightsHad();
    hunter.AddFightsHad(fights_to_add);
    fights_to_add += temp;

    //update partial nen
    item_data.getValue(curr).hunter_nen += partial_nen;
    partial_nen = item_data.getValue(curr).hunter_nen;

    //update parent
    parent.setData(path.Pop(), parent_key);
  }
}

int UF::FindRoot(const int key){
  Stack<int> path;
  int parent_key = key;
  while(parent.getValue(parent_key) != -1){
    path.Push(parent_key);
    parent_key = parent.getValue(parent_key);
  }
  PathCompress(path);
  return parent_key;
}

bool UF::HunterExists(const int hunterId){
    return item_data.doesExist(hunterId);
}
