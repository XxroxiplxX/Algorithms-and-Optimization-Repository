//
// Created by piotrkali on 4/23/23.
//

#ifndef A_ALGORITHM_H
#define A_ALGORITHM_H
#define GOAL 0x123456789abcdef0
#include "State.h"
#include <list>
#include <set>
void a_star_search_improved(ImprovedState* start);
bool contains(std::list<ImprovedState*> list, uint64_t goal);
bool contains(std::set<ImprovedState*> set, uint64_t goal);

#endif //A_ALGORITHM_H
