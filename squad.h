#pragma once
#include <Block.h>
#include <memory>

#include "wet2util.h"
#include "hunter.h"

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

public:
    explicit Squad(int squadId);
    int GetSquadExp() const;
    int GetSquadAura() const;
    int GetSquadSize() const;
    int GetSquadId() const;
    std::shared_ptr<Hunter> GetInitialHunter();
    const NenAbility& GetSquadNen() const;
    void addHunter(const Hunter& hunter); //adds hunter's params to the squad's params
    void mergeSquad(const Squad& newSquad); //merges the new squad into this squad
    void addSquadExp(int amt);
    void setInitialHunter(const std::shared_ptr<Hunter>& initialHunter);
    bool operator<(const Squad& other) const;
     bool operator>(const Squad& other) const;
     bool operator==(const Squad& other) const;
     friend std::ostream& operator<<(std::ostream& out, const Squad& s) {
         out << "squad id: " << s.GetSquadId() << "squad Aura: " << s.GetSquadAura() << ".";
         return out;
     }
};
