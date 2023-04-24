#include <iostream>
#include <cstdint>
#include <list>
#include "State.h"
#include "Algorithm.h"
struct shit {
    int a;
    shit (int c) : a(c){}
};
int main() {

    State* state = new State(0x123456789ab0defc);
    a_star_search_improved(state);

    return 0;
}
