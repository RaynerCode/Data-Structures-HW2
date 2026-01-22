// You can edit anything you want in this file.
// However, you need to implement all public Huntech functions, which are provided below as a template.

#include "Huntech26a2.h"

Huntech::Huntech() = default;

Huntech::~Huntech() = default;

StatusType Huntech::add_squad(int squadId) {
    if(squadId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        const std::shared_ptr<Squad> newSquad = std::make_shared<Squad>(squadId);
        this->squadIdTree.Add(newSquad);
        this->squadAuraTree.Add(Triplet<int,int,std::shared_ptr<Squad>,SquadComp>(0,squadId,newSquad,c));
    }
    catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const std::invalid_argument& e) {
        return StatusType::FAILURE;
    }
    catch (...) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType Huntech::remove_squad(int squadId) {
    //remove squad from Tree. the UF isn't changed because this squad becomes numb, it can't be
    //united with any other squad because union happens through SquadIds.
    if(squadId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        std::shared_ptr<Squad> squadToDelete = this->squadIdTree.Find(std::make_shared<Squad>(squadId));
        const int idToDelete = squadToDelete->GetSquadId();
        std::cout << "deleting Id: " << idToDelete << std::endl;
        squadAuraTree.Remove(Triplet<int,int,std::shared_ptr<Squad>,SquadComp>(squadToDelete->GetSquadAura(),idToDelete,squadToDelete,c));
        squadIdTree.Remove(squadToDelete);
    }
    catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const std::invalid_argument& e) {
        return StatusType::FAILURE;
    }
    catch (...) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

StatusType Huntech::add_hunter(int hunterId,
                               int squadId,
                               const NenAbility &nenType,
                               int aura,
                               int fightsHad) {

    if(squadId <= 0 || hunterId <=0 || !nenType.isValid() || aura < 0 || fightsHad < 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        const std::shared_ptr<Squad> squad = this->squadIdTree.Find(std::make_shared<Squad>(squadId));
        const std::shared_ptr<Hunter> newHunter(std::make_shared<Hunter>(hunterId, squadId, nenType, aura, fightsHad));
        if(squad->setInitialHunter(newHunter)) {
            //if returned true, we need to do a makeSet
            this->m_uf.MakeSet(hunterId,newHunter,squad);
        }
        else { //if returned false, we need to add the new hunter to the existing set
            this->m_uf.AddToSet(hunterId, newHunter, squad->GetInitialHunter()->GetHunterId());
        }
        squad->addHunter(newHunter); //change squad fields accordingly.
    }
    catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const std::invalid_argument& e) {
        return StatusType::FAILURE;
    }
    catch (...) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;

}

output_t<int> Huntech::squad_duel(int squadId1, int squadId2) {
    if(squadId1 <= 0 || squadId2 <= 0 || squadId1 == squadId2) {
        return StatusType::INVALID_INPUT;
    }
    try {
        std::shared_ptr<Squad> squad1 = squadIdTree.Find(std::make_shared<Squad>(squadId1));
        std::shared_ptr<Squad> squad2 = squadIdTree.Find(std::make_shared<Squad>(squadId2));
        if(squad1->GetSquadSize() <= 0 || squad2->GetSquadSize() <= 0) {
            return StatusType::FAILURE;
        }
        const int effectiveAura1 = squad1->GetSquadAura() + squad1->GetSquadExp();
        const int effectiveAura2 = squad2->GetSquadAura() + squad2->GetSquadExp();
        squad1->GetInitialHunter()->AddFightsHad(1);
        squad2->GetInitialHunter()->AddFightsHad(1);
        if(effectiveAura1 > effectiveAura2) {
            squad1->addSquadExp(3);
            return 1;
        }
        if(effectiveAura2 > effectiveAura1) {
            squad2->addSquadExp(3);
            return 3;
        }
        if(effectiveAura1 == effectiveAura2) {
            if(squad1->GetSquadNen() > squad2->GetSquadNen()) {
                squad1->addSquadExp(3);
                return 2;
            }
            if(squad2->GetSquadNen() > squad1->GetSquadNen()) {
                squad2->addSquadExp(3);
                return 4;
            }
            squad1->addSquadExp(1);
            squad2->addSquadExp(1);
            return 0;
        }
    }
    catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const std::invalid_argument& e) {
        return StatusType::FAILURE;
    }
    catch (...) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}

output_t<int> Huntech::get_hunter_fights_number(const int hunterId) {
    if(hunterId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        return m_uf.GetHunterFightsHad(hunterId);
    }
    catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const std::invalid_argument& e) {
        return StatusType::FAILURE;
    }
    catch (...) {
        return StatusType::FAILURE;
    }

}

output_t<int> Huntech::get_squad_experience(int squadId) {
    if(squadId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        return squadIdTree.Find(std::make_shared<Squad>(squadId))->GetSquadExp();
    }
    catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const std::invalid_argument& e) {
        return StatusType::FAILURE;
    }
    catch (...) {
        return StatusType::FAILURE;
    }
}

output_t<int> Huntech::get_ith_collective_aura_squad(const int i) const {
    try {
        return squadAuraTree.Get_ithRank(i).value->GetSquadId();
    }
    catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const std::out_of_range& e) {
        return StatusType::FAILURE;
    }
    catch (...) {
        return StatusType::FAILURE;
    }
}

output_t<NenAbility> Huntech::get_partial_nen_ability(const int hunterId) {
    //return UF.GetPartialNen(id);
    if(hunterId <= 0) {
        return StatusType::INVALID_INPUT;
    }
    try {
        if(m_uf.Find(hunterId)->isDead()) {
            return StatusType::FAILURE;
        }
        return m_uf.GetPartialNen(hunterId);
    }
    catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const std::invalid_argument& e) {
        return StatusType::FAILURE;
    }
    catch (...) {
        return StatusType::FAILURE;
    }
}

StatusType Huntech::force_join(int forcingSquadId, int forcedSquadId) {

    if(forcingSquadId <= 0 || forcedSquadId <= 0 || forcedSquadId == forcingSquadId) {
        return StatusType::INVALID_INPUT;
    }
    try {
        std::shared_ptr<Squad> forcingSquad = squadIdTree.Find(std::make_shared<Squad>(forcingSquadId));
        std::shared_ptr<Squad> forcedSquad = squadIdTree.Find(std::make_shared<Squad>(forcedSquadId));
        if(forcingSquad->GetSquadSize() <= 0) {
            return StatusType::FAILURE;
        }
        const int effectiveForcing = forcingSquad->GetSquadAura() + forcingSquad->GetSquadExp() + forcingSquad->GetSquadNen().getEffectiveNenAbility();
        const int effectiveForced = forcedSquad->GetSquadAura() + forcedSquad->GetSquadExp() + forcedSquad->GetSquadNen().getEffectiveNenAbility();
        if(effectiveForcing <= effectiveForced) {
            return StatusType::FAILURE;
        }
        std::shared_ptr<Hunter> forcingHunter = forcingSquad->GetInitialHunter();
        std::shared_ptr<Hunter> forcedHunter = forcedSquad->GetInitialHunter();
        m_uf.Union(forcingHunter->GetHunterId(), forcedHunter->GetHunterId());
        forcingSquad->mergeSquad(forcedSquad);
        const std::shared_ptr<Squad>& squadToDelete = forcedSquad;
        const int idToDelete = squadToDelete->GetSquadId();
        squadAuraTree.Remove(Triplet<int,int,std::shared_ptr<Squad>,SquadComp>(squadToDelete->GetSquadAura(),idToDelete,squadToDelete,c));
        squadIdTree.Remove(squadToDelete);
    }
    catch (const std::bad_alloc& e) {
        return StatusType::ALLOCATION_ERROR;
    }
    catch (const std::invalid_argument& e) {
        return StatusType::FAILURE;
    }
    catch (...) {
        return StatusType::FAILURE;
    }
    return StatusType::SUCCESS;
}
