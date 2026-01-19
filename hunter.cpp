#include "hunter.h"

Hunter::Hunter(const int hunterId, const int squadId, const NenAbility& type, const int aura, const int fightsHad) :
hunterId(hunterId), squadId(squadId), nenType(type), aura(aura), fightsHad(fightsHad)  {};

int Hunter::GetFightsHad() const {
    return this->fightsHad;
}

NenAbility& Hunter::GetNenAbility() {
    return this->nenType;
}

NenAbility& Hunter::GetPartialNenAbility() {
    return this->pNen;
}

void Hunter::SetFightsHad(const int fights) {
    this->fightsHad = fights;
}





