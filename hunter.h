#pragma once
#include "wet2util.h" //REMEMBER TO REMOVE BEFORE SUBMISSION
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
    void SetFightsHad(int fights);
    int GetFightsHad() const;

    NenAbility& GetNenAbility();
    NenAbility& GetPartialNenAbility();

};

