#pragma once
#include "wet2util.h"
class Hunter {
private:
    int hunterId;
    int squadId;
    NenAbility nenType;
    NenAbility pNen;
    int aura;
    int fightsHad;
public:
    Hunter(int hunterId, int squadId, const NenAbility& type, int aura, int fightsHad);
    void AddFightsHad(int amt);
    int GetFightsHad() const;
    int GetAura() const;
    int GetHunterId() const;
    int GetSquadId() const;
    const NenAbility& GetNenAbility() const;
    const NenAbility& GetPartialNenAbility() const;

};

