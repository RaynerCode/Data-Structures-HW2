// 
// 234218 Data Structures 1.
// Semester: 2026A (Winter).
// Wet Exercise #2 - Huntech.
// 
// The following header file contains all methods we expect you to implement.
// You MAY add private methods and fields of your own.
// DO NOT erase or modify the signatures of the public methods.
// DO NOT modify the preprocessors in this file.
// DO NOT use the preprocessors in your other code files.
// 

#ifndef HUNTECH26A2_H_
#define HUNTECH26A2_H_
#pragma once
#include "wet2util.h"
#include "UF.h"
#include "RankTree.h"
#include "Triplet.h"


class Huntech {
private:
    //
    // Here you may add anything you need to implement your Huntech class
    struct SquadComp{
        template<typename T>
        bool operator()(const T& s1, const T& s2) const {
            if(s1.first != s2.first) {
                return s1.first < s2.first;
            }
            return s1.second < s2.second;
        }
    };
    //
    SquadComp c;
    UF m_uf;
    RankTree<Triplet<int , int, std::shared_ptr<Squad>, SquadComp>> squadAuraTree;
    AvlTree<std::shared_ptr<Squad>> squadIdTree;
    //squadAuraTree sorts squads by their aura first and then by their id. each node should hold the number of squads with less

public:
    // <DO-NOT-MODIFY> {

    Huntech();
    virtual ~Huntech();

    StatusType add_squad(int squadId);
    
    StatusType remove_squad(int squadId);
    
    StatusType add_hunter(int hunterId,
                          int squadId,
                          const NenAbility &nenType,
                          int aura,
                          int fightsHad);

    output_t<int> squad_duel(int squadId1, int squadId2);

    output_t<int> get_hunter_fights_number(int hunterId);

    output_t<int> get_squad_experience(int squadId);

    output_t<int> get_ith_collective_aura_squad(int i);

    output_t<NenAbility> get_partial_nen_ability(int hunterId);

    StatusType force_join(int forcingSquadId, int forcedSquadId);

    // } </DO-NOT-MODIFY>
};

#endif // HUNTECH26A2_H_
