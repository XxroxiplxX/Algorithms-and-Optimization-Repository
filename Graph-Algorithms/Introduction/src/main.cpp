#include <iostream>
#include <fstream>
#include "Graph.h"
#include "GraphReader.h"
#include "Algorithms.h"
#include <stack>
enum flags {
    ONE,
    TWO,
    THREE,
    FOUR,
    TREE,
    FILEN,
    NUMBER,
    NONE
};
int main(int argc, char** argv) {
    bool readfile = false;
    std::string directory;
    std::string filename;
    std::stack<flags> fs;
    flags f1;
    flags f2;
    flags f3;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            switch (argv[i][1]) {
                case 'f' :
                    fs.push(flags::FILEN);
                    break;
                case 'n' :
                    fs.push(flags::NUMBER);
                    break;
                case 't' :
                    f3 = flags::TREE;
                    break;
                default:
                    std::cerr << "unknown flag" << std::endl;
                    exit(1);
            }

        } else {
            flags flag = fs.top();
            switch (flag) {
                case flags::FILEN:
                    filename = std::string(argv[i]);
                    break;
                case flags::NUMBER:
                    switch (argv[i][0]) {
                        case '1' :
                            f2 = flags::ONE;
                            directory = "../../resources/";
                            break;
                        case '2' :
                            f2 = flags::TWO;
                            directory = "../../resources/2/";
                            break;
                        case '3' :
                            f2 = flags::THREE;
                            directory = "../../resources/3/";
                            break;
                        case '4' :
                            f2 = flags::FOUR;
                            directory = "../../resources/4/";
                            break;
                        default :
                            std::cerr << "unknown condition\n";
                            exit(1);
                    }

                    break;
                case flags::TREE :
                    break;
            }

        }
    }
    directory+=filename;

    auto gr = GraphReader(directory);
    gr.initialCheck();
    AbstractGraph* ag;
    ag = gr.buildDirectedGraph();
    return 0;
} //73,832
