#pragma once
#include "wet2util.h"
#include "Block.h"
#include <memory>

class Squad;

class Hunter {
private:
    int hunterId;
    NenAbility nenType;
    int aura;
    int fightsHad;

    int parent;
    std::shared_ptr<Squad> squad;
    NenAbility hunter_nen;
    NenAbility sub_group_nen;
public:
    Hunter(int hunterId, const NenAbility& type, int aura, int fightsHad);
    void AddFightsHad(int amt);
    int GetFightsHad() const;
    int GetAura() const;
    int GetHunterId() const;
    const NenAbility& GetNenAbility() const;


    void SetParent(int p);
    int GetParent();

    void SetSquad(std::shared_ptr<Squad> s);
    std::shared_ptr<Squad> GetSquad();

    void SetHunterNen(const NenAbility& n);
    const NenAbility& GetHunterNen();

    void SetSubGruopNen(const NenAbility& n);
    const NenAbility& GetSubGroupNen();
};

struct SquadComp{
    template<typename Squad>
    bool operator()(const Squad& s1, const Squad& s2) const {
        if(s1.GetSquadAura() != s2.GetSquadAura()) {
            return s1.GetSquadAura() < s2.GetSquadAura();
        }
        return s1.GetSquadId() < s2.GetSquadId();
    }
};
class Squad {
    int squadId;
    std::shared_ptr<Hunter> initialHunter = nullptr;
    int squadSize = 0;
    int squadExp = 0;
    int squadFightsHad = 0;
    int totalAura = 0;
    NenAbility totalNen;
    SquadComp c;
    bool dead = false;

public:
    explicit Squad(int squadId);
    int GetSquadExp() const;
    int GetSquadAura() const;
    int GetSquadSize() const;
    int GetSquadId() const;
    bool isDead() const;
    std::shared_ptr<Hunter> GetInitialHunter();
    const NenAbility& GetSquadNen() const;
    void addHunter(const std::shared_ptr<Hunter> &hunter); //adds hunter's params to the squad's params
    void mergeSquad(const std::shared_ptr<Squad>& newSquad); //merges the new squad into this squad
    void addSquadExp(int amt);
    void kill();
    bool setInitialHunter(const std::shared_ptr<Hunter>& initialHunter);
    bool operator<(const Squad& other) const;
     bool operator>(const Squad& other) const;
     bool operator==(const Squad& other) const;
     friend std::ostream& operator<<(std::ostream& out, const Squad& s) {
         out << "squad id: " << s.GetSquadId() << "squad Aura: " << s.GetSquadAura() << ".";
         return out;
     }
};