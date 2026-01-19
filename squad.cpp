#include "squad.h"

Squad::Squad(int squadId) : squadId(squadId) {}

int Squad::GetSquadAura() const {
    return this->totalAura;
}

int Squad::GetSquadExp() const {
    return this->squadExp;
}

NenAbility &Squad::GetSquadNen(){
    return this->totalNen;
}

void Squad::addHunter(const Hunter &hunter) {
    this->squadSize++;
    this->totalAura += hunter.GetAura();
    this->totalNen += hunter.GetNenAbility();
}




