//
// Created by piotrkali on 4/23/23.
//

#include "Algorithm.h"
#include "iostream"
bool contains(std::list<ImprovedState*> list, uint64_t goal) {
    for (auto state : list) {
        if (state->board == goal) {
            return true;
        }
    }
    return false;
}
bool contains(std::set<ImprovedState*> set, uint64_t goal) {
    ImprovedState state = ImprovedState(goal);
    auto pos = set.find(&state);
    if (pos != set.end()) {
        return true;
    } else {
        return false;
    }
}
void a_star_search_improved(ImprovedState* start) {
    std::set<ImprovedState*> open_set;
    std::list<ImprovedState* > closed_set;
    start->g_score = 0;
    open_set.insert(start);
    while (!open_set.empty()) {
        auto x = *open_set.begin();
        if (x->board == GOAL) {
            std::cout << "znalazlem";
            //return;
        }
        open_set.erase(x);
        closed_set.push_back(x);
        for (auto nbh : x->produce_neighbours()) {
            if (contains(closed_set, nbh->board)) {
                continue;
            }
            int tentative_g = x->g_score + 1;
            bool is_better = true;
            if (!contains(open_set, nbh->board)) {
                open_set.insert(nbh);
                is_better = true;
            } else if (tentative_g < nbh->g_score) {
                is_better = true;
            }
            if (is_better) {
                nbh->g_score = tentative_g;
            }
        }
    }
}