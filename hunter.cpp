#include "hunter.h"

Hunter::Hunter(const int hunterId, const int squadId, const NenAbility& type, const int aura, const int fightsHad) :
hunterId(hunterId), squadId(squadId), nenType(type), aura(aura), fightsHad(fightsHad)  {};

int Hunter::GetFightsHad() const {
    return this->fightsHad;
}

const NenAbility& Hunter::GetNenAbility() const{
    return this->nenType;
}

const NenAbility& Hunter::GetPartialNenAbility() const{
    return this->pNen;
}

void Hunter::SetFightsHad(const int fights) {
    this->fightsHad = fights;
}

int Hunter::GetAura() const {
    return this->aura;
}





