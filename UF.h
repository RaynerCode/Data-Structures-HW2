#include "hash.h"
#include "Stack.h"
#include "wet2util.h"
#include <memory>

class Hunter{
  public:
  Hunter(Hunter& hunter) = default;
  void SetFightHad(int fights);
  int GetFightsHad() const;
  NenAbility& GetNenAbility() const;
};
class Squad{
  public:
  int get_hunter_count() const;
};

class UF{
  struct hunterNode{
    std::shared_ptr<Hunter> hunter;
    NenAbility sub_group_nen;
    NenAbility hunter_nen;

    hunterNode(std::shared_ptr<Hunter> hunter)
     : hunter(hunter), sub_group_nen(hunter->GetNenAbility()), hunter_nen(hunter->GetNenAbility()) {}
  };

  hashedArray<int> parent;
  hashedArray<hunterNode> item_data;
  hashedArray<std::shared_ptr<Squad>> Set_data;

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
    NenAbility GetPartialNen(int key);

  private: //helper functions

  /*Compresses the paths of all items in the stack. 
  /It is asumed that the stack contanis a valid path  
  /from one of the roots direct children (not containing root) to a leaf.
  */
  void PathCompress(Stack<int>& path);

  int FindRoot(int key);
};