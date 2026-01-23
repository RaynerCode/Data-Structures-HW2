#include "hunter.h"

Hunter::Hunter(const int hunterId, const NenAbility& type, const int aura, const int fightsHad) :
hunterId(hunterId), nenType(type), aura(aura), fightsHad(fightsHad), parent(0), 
hunter_nen(nenType), sub_group_nen(nenType), squad(nullptr) {};

int Hunter::GetFightsHad() const {
    return this->fightsHad;
}

const NenAbility& Hunter::GetNenAbility() const{
    return this->nenType;
}

void Hunter::AddFightsHad(const int amt) {
    this->fightsHad += amt;
}

int Hunter::GetAura() const {
    return this->aura;
}

int Hunter::GetHunterId() const {
    return this->hunterId;
}



void Hunter::SetParent(int p){parent = p;}
int Hunter::GetParent(){return parent;}

void Hunter::SetSquad(std::shared_ptr<Squad> s){squad = s;}
std::shared_ptr<Squad> Hunter::GetSquad(){return squad;}

void Hunter::SetHunterNen(const NenAbility& n){hunter_nen = n;}
const NenAbility& Hunter::GetHunterNen(){return hunter_nen;}

void Hunter::SetSubGruopNen(const NenAbility& n){sub_group_nen = n;}
const NenAbility& Hunter::GetSubGroupNen(){return sub_group_nen;}