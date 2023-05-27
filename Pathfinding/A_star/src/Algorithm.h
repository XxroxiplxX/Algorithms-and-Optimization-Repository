//
// Created by piotrkali on 4/23/23.
//

#ifndef A_ALGORITHM_H
#define A_ALGORITHM_H
#define GOAL 0x123456789abcdef0
#include "State.h"
#include <list>
#include <set>
#include "ImprovedState.h"
#include "ManhattanState.h"
#include "Logger.h"
#include <random>
#include <iostream>
#include <stack>
#include <queue>
using namespace Logging;
int a_star_search_improved(ImprovedState* start, std::list<ImprovedState*>& safe_delete, Logger& logger);
int a_star_search_manhattan(ManhattanState* start, std::list<ManhattanState*>& safe_delete, Logger& logger);
void call_a_star(std::string option, bool xtreme, Logger& stats, int repetitions=12  );
bool contains(std::list<ImprovedState*> list, uint64_t goal);
bool contains(std::set<ImprovedState*> set, uint64_t goal);
bool contains(std::list<ManhattanState*> list, uint64_t goal);
void erease(std::list<ManhattanState*>& list, uint64_t _to_erease);
std::string reconstruct_path(ManhattanState* state);
std::string reconstruct_path(ImprovedState* state);
uint64_t randomize_board(std::mt19937 generator, std::uniform_int_distribution<int>distribution, int repetitions=21);
uint64_t xtreme_random(std::mt19937 generator, std::uniform_int_distribution<int>distribution);
#endif //A_ALGORITHM_H
