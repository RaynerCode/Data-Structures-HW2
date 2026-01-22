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

void Squad::addHunter(const std::shared_ptr<Hunter>&hunter) {
    this->squadSize++;
    this->totalAura += hunter->GetAura();
    this->totalNen += hunter->GetNenAbility();
}

void Squad::mergeSquad(const std::shared_ptr<Squad> &newSquad) {
    this->squadSize += newSquad->squadSize;
    this->totalAura += newSquad->GetSquadAura();
    this->totalNen += newSquad->totalNen;
    this->addSquadExp(newSquad->GetSquadExp());
}

void Squad::addSquadExp(const int amt) {
    this->squadExp += amt;
}

int Squad::GetSquadSize() const {
    return this->squadSize;
}

bool Squad::isDead() const {
    return this->dead;
}

void Squad::kill() {
    this->dead = true; //should only be accessed once.
}


int Squad::GetSquadId() const {
    return this->squadId;
}

std::shared_ptr<Hunter> Squad::GetInitialHunter() {
    return this->initialHunter;
}

bool Squad::setInitialHunter(const std::shared_ptr<Hunter>& initialHunter) {
    if(this->initialHunter != nullptr) return false;
    this->initialHunter = initialHunter;
    return true;
}








