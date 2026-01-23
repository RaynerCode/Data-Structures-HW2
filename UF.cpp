#include "UF.h"

//public methods:

UF::UF(): item_data() {}

void UF::MakeSet(const int key, const std::shared_ptr<Hunter>& item, const std::shared_ptr<Squad>& Set){
  try{
    item_data.getValue(key); //it should throw an error because key is not in system, if succeeds then WE throw an error
  }
  catch(std::invalid_argument& e) {
    Set->addHunter(item);
    item->SetParent(-1); //-1 indicates that it is the root of the set.
    item_data.insert (key, item);
    item->SetSquad(Set);
    return;
  }
  throw (std::invalid_argument("id already exists"));
}

void UF::AddToSet(const int key, const std::shared_ptr<Hunter>& item,const int group_member_key){
  Find(group_member_key); //Finds the set to add to
  MakeSet(key, item, std::make_shared<Squad>(-1)); //create an imaginary set
  Union(group_member_key, key);
  /*unite the imaginary set with the real one.
  Note that the imaginary set's squad is the same as the real one's
  so it has equal member count. this means the imaginary set will always be
  united into the real one, keeping the real one's root.
  */
}

void UF::Union(const int key1,const int key2){
  int parent_key1 = FindRoot(key1);
  int parent_key2 = FindRoot(key2);

  if(item_data.getValue(parent_key1)->GetSquad() == nullptr || item_data.getValue(parent_key2)->GetSquad() == nullptr)
    throw std::runtime_error("one or more sets do not exist");

  if(parent_key1 == parent_key2) return; //already in the same set.

  std::shared_ptr<Squad> set1 = item_data.getValue(parent_key1)->GetSquad();
  std::shared_ptr<Squad> set2 = item_data.getValue(parent_key2)->GetSquad();

  //Get Hunters
  Hunter& hunter1 = *item_data.getValue(parent_key1);
  Hunter& hunter2 = *item_data.getValue(parent_key2);

  if(set1->GetSquadSize() >= set2->GetSquadSize()){
    //Update root
    item_data.getValue(parent_key2)->SetParent(parent_key1);

    //Update nen
    hunter2.SetHunterNen(hunter2.GetHunterNen() + hunter1.GetSubGroupNen() - hunter1.GetHunterNen());
    hunter1.SetSubGruopNen(hunter1.GetSubGroupNen() + hunter2.GetSubGroupNen());

    //Update fights had
    hunter2.AddFightsHad(-1 * hunter1.GetFightsHad());

    //Update sets
    set1->mergeSquad(set2);
    hunter2.SetSquad(nullptr);
  }
  else{
    //Update root
    item_data.getValue(parent_key1)->SetParent(parent_key2);

    //Update nen
    hunter2.SetHunterNen(hunter2.GetHunterNen() + hunter1.GetHunterNen());
    hunter1.SetHunterNen(hunter1.GetHunterNen() - hunter2.GetHunterNen());

    //Update fights had
    hunter1.AddFightsHad(-1 * hunter2.GetFightsHad());

    //Update sets
    set1->mergeSquad(set2);
    hunter2.SetSquad(hunter1.GetSquad());
    hunter1.SetSquad(nullptr);
  }
}

void UF::ForceUnion(std::shared_ptr<Squad> set1, std::shared_ptr<Squad> set2){

  if(set1 == nullptr || set2 == nullptr) throw(std::invalid_argument("null set pointer"));
  if(set1->GetSquadId() == set2->GetSquadId()) return; //same set.

  Hunter& h1 = *set1->GetInitialHunter();
  Hunter& h2 = *set2->GetInitialHunter();
  if(set1->GetSquadSize() >= set2->GetSquadSize()){
    //Update root
    h2.SetParent(h1.GetHunterId());

    //Update nen
    h2.SetHunterNen(h2.GetHunterNen() + h1.GetSubGroupNen() - h1.GetHunterNen());
    h1.SetSubGruopNen(h1.GetSubGroupNen() + h2.GetSubGroupNen());

    //Update fights had
    h2.AddFightsHad(-1 * h1.GetFightsHad());

    //Update sets
    std::cout << "before" << std::endl;
    set1->mergeSquad(set2);
    std::cout << "after" << std::endl;
    h2.SetSquad(nullptr);
  }
  else{
    //Update root
    h1.SetParent(h2.GetHunterId());

    //Update nen
    h2.SetHunterNen(h2.GetHunterNen() + h1.GetSubGroupNen());
    h1.SetHunterNen(h1.GetHunterNen() - h2.GetHunterNen());

    //Update fights had
    h1.AddFightsHad(-1 * h2.GetFightsHad());

    //Update sets
    set1->mergeSquad(set2);
    h2.SetSquad(h1.GetSquad());
    h1.SetSquad(nullptr);
  }
}

std::shared_ptr<Squad> UF::Find(const int key){
  return item_data.getValue(FindRoot(key))->GetSquad();
}

int UF::GetHunterFightsHad(int key){
  if(item_data.getValue(key)->GetParent() == -1) 
    return item_data.getValue(key)->GetFightsHad();
  int root = FindRoot(key); //also compresses path
  return item_data.getValue(key)->GetFightsHad() +
    item_data.getValue(root)->GetFightsHad();
} 

NenAbility UF::GetPartialNen(int key){
  if(item_data.getValue(key)->GetParent() == -1)
    return item_data.getValue(key)->GetHunterNen();
  int root = FindRoot(key); //also compresses path
  NenAbility nen(item_data.getValue(key)->GetHunterNen());
  nen += item_data.getValue(root)->GetHunterNen(); 
  return nen;
}

//private helper methods:

void UF::PathCompress(Stack<int>& path){
  if(path.IsEmpty()) return;
  
  int curr = path.Pop(), parent_key = item_data.getValue(curr)->GetParent();
  int fights_to_add = item_data.getValue(curr)->GetFightsHad();
  NenAbility partial_nen(item_data.getValue(curr)->GetHunterNen());
  while(!path.IsEmpty()){
    //get hunter to update
    curr = path.Peek();
    Hunter& hunter = *(item_data.getValue(curr));

    //update fights had
    int temp = hunter.GetFightsHad();
    hunter.AddFightsHad(fights_to_add);
    fights_to_add += temp;

    //update partial nen
    const NenAbility& tempnen = item_data.getValue(curr)->GetHunterNen();
    item_data.getValue(curr)->SetHunterNen(item_data.getValue(curr)->GetHunterNen() + partial_nen);
    partial_nen = item_data.getValue(curr)->GetHunterNen();

    //update parent
    item_data.getValue(path.Pop())->SetParent(parent_key);
  }
}

int UF::FindRoot(const int key){
  Stack<int> path;
  int parent_key = key;
  while(item_data.getValue(parent_key)->GetParent() != -1){
    path.Push(parent_key);
    parent_key = item_data.getValue(parent_key)->GetParent();
  }
  PathCompress(path);
  return parent_key;
}