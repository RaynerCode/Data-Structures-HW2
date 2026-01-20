#pragma once
#include "wet2util.h"
#include "hunter.h"

class Squad {
    int squadId;
    int squadSize = 0;
    int squadExp = 0;
    int squadFightsHad = 0;
    int totalAura = 0;
    NenAbility totalNen;

public:
    explicit Squad(int squadId);
    int GetSquadExp() const;
    int GetSquadAura() const;
    int GetSquadSize() const;
    const NenAbility& GetSquadNen() const;
    void addHunter(const Hunter& hunter); //adds hunter's params to the squad's params
    void mergeSquad(const Squad& newSquad); //merges the new squad into this squad
    void addSquadExp(int amt);
};
