#pragma once
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
    int initialHunterId = -1;
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
    int GetInitialHunterId() const;
    const NenAbility& GetSquadNen() const;
    void addHunter(const Hunter& hunter); //adds hunter's params to the squad's params
    void mergeSquad(const Squad& newSquad); //merges the new squad into this squad
    void addSquadExp(int amt);
    void setInitialHunterId(int id);
    bool operator<(const Squad& other) const;
    bool operator>(const Squad& other) const;
    bool operator==(const Squad& other) const;
    friend std::ostream& operator<<(std::ostream& out, const Squad& s) {
        out << "squad id: " << s.GetSquadId() << "squad Aura: " << s.GetSquadAura() << ".";
        return out;
    }
};

