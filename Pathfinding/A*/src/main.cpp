#include <iostream>
#include <cstdint>
#include <list>
#include "State.h"
#include "Algorithm.h"
#include "ImprovedState.h"

int main(int argc, char** argv) {

    bool s = 0;
    if (s) {
        std::string heuristic = std::string(argv[1]);
        std::string rep = std::string(argv[2]);
        Logger log("../../logs/presentation.log");
        call_a_star(heuristic, 0, log, std::stoi(rep));
    } else {
        Logger log("../../logs/presentation.log");
        call_a_star("improved", 0, log);
    }

    //call_a_star(heuristic, 0, std::stoi(rep));
    return 0;
}
