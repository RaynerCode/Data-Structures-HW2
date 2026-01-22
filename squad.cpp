#include "squad.h"



Squad::Squad(const int squadId) : squadId(squadId) {}

bool Squad::operator<(const Squad& other) const {
    return c(*this, other);
}

bool Squad::operator>(const Squad& other) const {
    return c(other, *this);
}

bool Squad::operator==(const Squad& other) const {
    return !( (*this < other) || (other < *this) );
}



int Squad::GetSquadAura() const {
    return this->totalAura;
}

int Squad::GetSquadExp() const {
    return this->squadExp;
}

const NenAbility &Squad::GetSquadNen() const{
    return this->totalNen;
}

void Squad::addHunter(const Hunter &hunter) {
    this->squadSize++;
    this->totalAura += hunter.GetAura();
    this->totalNen += hunter.GetNenAbility();
}

void Squad::mergeSquad(const Squad &newSquad) {
    this->squadSize += newSquad.squadSize;
    this->totalAura += newSquad.GetSquadAura();
    this->totalNen += newSquad.totalNen;
    this->addSquadExp(newSquad.GetSquadExp());
}

void Squad::addSquadExp(const int amt) {
    this->squadExp += amt;
}

int Squad::GetSquadSize() const {
    return this->squadSize;
}

int Squad::GetSquadId() const {
    return this->squadId;
}

int Squad::GetInitialHunterId() const {
    return this->initialHunterId;
}

void Squad::setInitialHunterId(const int id) {
    if(this->initialHunterId >= 0) return;
    this->initialHunterId = id;
}






