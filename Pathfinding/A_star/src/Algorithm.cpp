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
bool contains(std::list<ManhattanState*> list, uint64_t goal){
    for (auto state : list) {
        if (state->board == goal) {
            return true;
        }
    }
    return false;
}

int a_star_search_improved(ImprovedState* start, std::list<ImprovedState*>& safe_delete, Logger& logger) {

    //logger.log("start:\n");
    std::set<ImprovedState*> open_set;
    std::list<ImprovedState*> closed_set;
    start->g_score = 0;
    open_set.insert(start);
    while (!open_set.empty()) {
        if (safe_delete.size() > 50000) {
            return -1;
        }
        auto x = *open_set.begin();
        logger.log("heuristic cost: ", x->g_score);
        if (x->board == GOAL) {
            //std::cout << "znalazlem";
            //std::cout << safe_delete.size() << std::endl;
            //logger.log("", safe_delete.size());
            //auto tmp = produce_matrix_view(x->board);
            //std::cout << "final state:\n" << print_board(tmp) << std::endl;
            //delete[] tmp;
            //std::cout << safe_delete.size() << std::endl;
            //std::cout << "moves: " << safe_delete.size() << std::endl;
            //std::cout << reconstruct_path(x);
            //logger.log(reconstruct_path(x));
            return safe_delete.size();
        }
        open_set.erase(x);
        closed_set.push_back(x);
        for (auto nbh : x->produce_neighbours()) {
            //logger.log("przechodze po sasiadach");
            safe_delete.push_back(nbh);
            //logger.log("dodano vertex, wielkosc grafu to: ", safe_delete.size());
            //std::cout << safe_delete.size() << std::endl;
            if (contains(closed_set, nbh->board)) {
                continue;
            }
            int tentative_g = x->g_score + 1;
            std::cout << x->g_score << std::endl;
            bool is_better = false;
            if (!contains(open_set, nbh->board)) {
                open_set.insert(nbh);
                is_better = true;
            } else if (tentative_g < nbh->g_score) {
                //std::cout << "eee\n";
                is_better = true;
            }
            if (is_better) {
                nbh->g_score = tentative_g;
            }
        }
    }
    return -1;
}
void erease(std::list<ManhattanState*>& list, uint64_t _to_erease) {
    std::list<ManhattanState*>::iterator itr1 = list.begin();
    while (itr1 != list.end()) {
        auto tmp = *itr1;
        if (tmp->board == _to_erease) {
            list.erase(itr1);
            return;
        }
        itr1++;
    }
}
int a_star_search_manhattan(ManhattanState* start, std::list<ManhattanState*>& safe_delete, Logger& logger) {

    //logger.log("start:\n");
    //logger.log(print_board(produce_matrix_view(start->board)));
    std::priority_queue<ManhattanState*> open_set;
    std::list<ManhattanState*> closed_set;
    std::list<ManhattanState*> open_set_copy;
    start->g_score = 0;
    open_set.push(start);
    open_set_copy.push_front(start);
    int expect = 1;
    while (!open_set.empty()) {
        if (safe_delete.size() > 30000) {
            return -1;
        }
        
        auto x = *open_set.top();
        //std::cout << x.f_score << std::endl;
        if (x.board == GOAL) {
            std::cout << "znalazlem";
            //std::cout << safe_delete.size() << std::endl;
            //logger.log("", safe_delete.size());
            //logger.log(reconstruct_path(x));
            return safe_delete.size();
        }
        open_set.pop();
        expect--;
        erease(open_set_copy, x.board);
        logger.log("open set    ", open_set.size());
        closed_set.push_back(&x);
        for (auto& nbh : x.produce_neighbours()) {
            //logger.log("przechodze po sasiadach");
            safe_delete.push_back(nbh);
            //logger.log("dodano vertex, wielkosc grafu to: ", safe_delete.size());
            if (contains(closed_set, nbh->board)) {
                std::cout << "to juz sprawdziulem\n";
                continue;
            }
            int tentative_g = x.g_score + 1;
            bool is_better = false;
            if (!contains(open_set_copy, nbh->board)) {
                open_set.push(nbh);
                open_set_copy.push_front(nbh);
                nbh->h_score = manhattan_heuristic_cost(*nbh);
                is_better = true;
            } else if (tentative_g < nbh->g_score) {
                is_better = true;
            }
            if (is_better) {
                nbh->g_score = tentative_g;
                nbh->f_score = nbh->g_score + nbh->h_score;
                std::cout << nbh->h_score << std::endl;
            }
        }
    }
    return -1;
}

