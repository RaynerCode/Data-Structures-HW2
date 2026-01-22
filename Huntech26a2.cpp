// You can edit anything you want in this file.
// However, you need to implement all public Huntech functions, which are provided below as a template.

#include "Huntech26a2.h"

Huntech::Huntech() = default;

Huntech::~Huntech() = default;

StatusType Huntech::add_squad(int squadId) {
    //do squadTree.Add(squadId)
    // if(squadId <= 0) {
    //     return StatusType::INVALID_INPUT;
    // }
    try {
        std::shared_ptr<Squad> newSquad = std::make_shared<Squad>(squadId);
        this->squadIdTree.Add(newSquad);
        this->squadAuraTree.Add(Triplet<int,int,std::shared_ptr<Squad>,SquadComp>(0,squadId,newSquad,c));
    }
    catch (...) {
        throw std::bad_alloc();
    }


    return StatusType::FAILURE;
}

StatusType Huntech::remove_squad(int squadId) {
    //remove squad from Tree. the UF isn't changed because this squad becomes numb, it can't be
    //united with any other squad because union happens through SquadIds.
    return StatusType::FAILURE;
}

StatusType Huntech::add_hunter(int hunterId,
                               int squadId,
                               const NenAbility &nenType,
                               int aura,
                               int fightsHad)
{
    //find squadId in tree, if exists with zero hunters, add and change initialHunterId field
    //if it had hunters, go to the UF.find(initialHunterId) and UF.AddToSet the new hunter
    //if it had no hunters, do a UF.makeSet(new hunter, found squad);
    return StatusType::FAILURE;
}

output_t<int> Huntech::squad_duel(int squadId1, int squadId2) {
    //find both squads in SquadTree, compare in O(1). use Squad.addSquadExp accordingly.
    return 0;
}

output_t<int> Huntech::get_hunter_fights_number(int hunterId) {
    //do UF.GetNumberFightsHad(hunterId)
    return 0;
}

output_t<int> Huntech::get_squad_experience(int squadId) {
    //find squad in squadTree and return squad.GetSquadExp;
    return 0;
}

output_t<int> Huntech::get_ith_collective_aura_squad(int i) {
    //return Get_ithRank(i).GetSquadId() in a try catch.
    return 0;
}

output_t<NenAbility> Huntech::get_partial_nen_ability(int hunterId) {
    //return UF.GetPartialNen(id);
    return NenAbility();
}

StatusType Huntech::force_join(int forcingSquadId, int forcedSquadId) {
    /* check if the forcing is allowed (RAPE!)
     * set forcingHunter = forcing.GetInitialHunterId(), forcedHunter = forced.GetInitialHunterId();
     * do UF.union(forcingHunter,forcedHunter);
     * do forcing.merge(forced) in the squad Tree
     * remove forcedSquad from Tree using forcedSquadId
     */
    return StatusType::FAILURE;
}
