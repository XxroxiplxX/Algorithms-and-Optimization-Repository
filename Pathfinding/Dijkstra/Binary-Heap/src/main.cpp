#include <iostream>
#include "GrParser.h"
int main() {
    auto parser = new GrParser("../../../dataset/ch9-1.1/inputs/Random4-c/Random4-C.0.0.gr");
    auto g = parser->build_graph();
    //g->print_graph();
    return 0;
}
