#include "Algorithm.h"
uint64_t randomize_board(std::mt19937 generator, std::uniform_int_distribution<int>distribution, int repetitions) {
    int r;
    auto tmp_board = produce_matrix_view(GOAL);
    int gap = find_gap(tmp_board);
    move last = NULL_MOVE;
    int i = 0;
    while (i < repetitions) {
        r = distribution(generator);
        if (r == 0 && gap > 3 and last != DOWN) {
            move_gap(tmp_board, UP, gap);
            last = UP;
            i++;
        }
        else if (r == 1 && gap < 12 and last != UP) {
            move_gap(tmp_board, DOWN, gap);
            last = DOWN;
            i++;
        }
        else if (r == 2 && gap%4 != 0 and last != RIGHT) {
            move_gap(tmp_board, LEFT, gap);
            last = LEFT;
            i++;
        }
        else if (r == 3 && gap%4 != 3 and last != LEFT) {
            move_gap(tmp_board, RIGHT, gap);
            last = RIGHT;
            i++;
        }
        gap = find_gap(tmp_board);
    }
    uint64_t state = compress_matrix(tmp_board);
    delete[] tmp_board;
    return state;
}
uint64_t xtreme_random(std::mt19937 generator, std::uniform_int_distribution<int>distribution) {
    auto matrix_view = produce_matrix_view(GOAL);
    uint64_t result = 0x391feb46d0ac2785;
    while (!is_solvable(result)) {
        std::cout << "in\n";
        for (int i = 0; i < 10; i++) {
            int p = distribution(generator);
            int q = distribution(generator);
            swap(matrix_view, p, q);
        }
        result = compress_matrix(matrix_view);
    }
    delete[] matrix_view;
    return result;
}
void call_a_star(std::string option, bool xtreme, Logger& stats, int repetitions) {
    uint64_t s;
    srand(time(nullptr));
    std::mt19937 generator(rand());
    if (xtreme) {
        std::uniform_int_distribution<int>distribution(0,15);
        s = xtreme_random(generator, distribution);
    } else {
        std::uniform_int_distribution<int>distribution(0,4);
        s = randomize_board(generator, distribution);
    }
    if (option == "manhattan") {
        Logger logger("../../logs/manhattan.log");
        //Logger stats("../../logs/manhattan_k=" + std::to_string(repetitions) + ".csv");
        std::list<ManhattanState*> safe_delete;
        ManhattanState* start = new ManhattanState(s);
        auto tmp = produce_matrix_view(s);
        std::cout << "initial state:\n" << print_board(tmp) << std::endl;
        delete[] tmp;
        safe_delete.push_back(start);
        logger.log("initializing algorithm...");
        int m = a_star_search_manhattan(start, safe_delete, logger);
        stats.log("", m);
        logger.log("deallocating graph with size: ", safe_delete.size());
        for (auto& vertex : safe_delete) {
            delete vertex;
        }
        logger.log("memory deallocated\n");
        logger.close_logger();
    } else if (option == "improved") {
        Logger logger("../../logs/improved.log");
        //Logger stats("../../logs/improved_k=" + std::to_string(repetitions) + ".csv");
        std::list<ImprovedState*> safe_delete;
        ImprovedState* start = new ImprovedState(s);

        auto tmp = produce_matrix_view(s);
        //std::cout << "initial state:\n" << print_board(tmp) << std::endl;
        delete[] tmp;
        safe_delete.push_back(start);
        logger.log("initializing algorithm...");
        int i = a_star_search_improved(start, safe_delete, logger);
        logger.log("number of states: ", i);
        logger.log("deallocating graph with size: ", safe_delete.size());
        for (auto& vertex : safe_delete) {
            delete vertex;
        }
        logger.log("memory deallocated\n");
        logger.close_logger();
    } else {
        std::cerr << "invalid call\n";
    }
}

std::string reconstruct_path(ManhattanState* state){
    std::stack<int> path;
    ManhattanState* curr = state;
    std::string out ="";
    int d = state->g_score;
    for (int i = 0; i < d; i++) {
        auto tmp = produce_matrix_view(curr->board);
        path.push(find_gap(tmp));
        delete[] tmp;
        curr = curr->predecessor;
    }
    while (!path.empty()) {
        out +="Move " + std::to_string(path.top()) + "->";
        path.pop();
    }
    return out;
}
std::string reconstruct_path(ImprovedState* state){
    std::stack<int> path;
    ImprovedState* curr = state;
    std::string out ="";
    int d = state->g_score;
    for (int i = 0; i < d; i++) {
        auto tmp = produce_matrix_view(curr->board);
        path.push(find_gap(tmp));
        delete[] tmp;
        curr = curr->predecessor;
    }
    while (!path.empty()) {
        out +="Move " + std::to_string(path.top()) + "->";
        //std::cout << "Move " << path.top() << "\n";
        path.pop();
    }
    return out;
}