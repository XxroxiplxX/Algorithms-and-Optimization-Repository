#include <iostream>
#include "Parsers.h"
#include <chrono>
#include "Dijkstra.h"
enum Flag {
    D,
    SS,
    P2P,
    OSS,
    OP2P
};
int main(int argc, char** argv) {

    if (argc != 7) {
        std::cerr << "arguments :(\n";
        exit(1);
    }

    Flag first, second, third;
    GraphParser* graphParser;
    SourceParser* sourceParser;
    PairToPairParser* pairToPairParser;
    std::string graph_dir, data_dir, output_dir;

    if (std::string(argv[1]) == "-d") {
        first = D;
        graph_dir = std::string(argv[2]);
    } else {
        std::cerr << "unknown flag\n";
        exit(1);
    }

    if (std::string(argv[3]) == "-ss") {
        data_dir = std::string(argv[4]);
        second = SS;
    } else if (std::string(argv[3]) == "-p2p") {
        data_dir = std::string(argv[4]);
        second = P2P;
    } else {
        std::cerr << "unknown flag\n";
        exit(1);
    }


    if (std::string(argv[5]) == "-oss") {
        third = OSS;
        output_dir = std::string(argv[6]);
    } else if (std::string(argv[5]) == "-op2p") {
        third = OP2P;
        output_dir = std::string(argv[6]);
    } else {
        std::cerr << "unknown flag\n";
        exit(1);
    }

    std::cout << "executing dial for\n" <<"graph file: " << graph_dir << std::endl;
    std::cout << "input file: " << data_dir << std::endl;
    std::cout << "output file: " << output_dir << std::endl;

    std::list<int> sources;
    std::list<std::pair<int,int>> pairs;
    if (second == SS) {
        sourceParser = new SourceParser(data_dir);
        sources = sourceParser->build_parameters();
        delete sourceParser;
    } else {
        pairToPairParser = new PairToPairParser(data_dir);
        pairs = pairToPairParser->build_parameters();

    }
    graphParser = new GraphParser(graph_dir);
    auto graph = graphParser->build_graph();
    delete graphParser;

    std::ofstream results(output_dir);
    long long avg_time = 0;
    int c = 0;
    for (auto source : sources) {
        //std::cout << "iteration: " << c++ << std::endl;
        auto start = std::chrono::high_resolution_clock::now();
        dijkstra_to_all_nodes(graph->get_vertex(source), *graph);
        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
        avg_time += duration.count();
        for (auto v : graph->get_vertices()) {
            v->dist = ULLONG_MAX;
        }
    }

    avg_time /= sources.size();
    std::cout << avg_time << std::endl;







    /*

     std::string name="";
    std::string tmp(argv[1]);
    for (int i = tmp.length() - 15; i < tmp.length(); i++) {
        name += tmp[i];
    }
    std::cout << "saving to " << name << std::endl;


    auto ss_parser = SourceParser(std::string(argv[1]));
    auto sources = ss_parser.build_parameters();
    std::ofstream out("sources/" + name + ".test");
    for (auto source : sources) {
        out << source << std::endl;
    }
    out.close();



    auto pp_parser = PairToPairParser(std::string(argv[1]));
    auto pairs = pp_parser.build_parameters();
    std::ofstream out("pairs/" + name + ".test");
    for (auto pair : pairs) {
        out << pair.first << "    " << pair.second << std::endl;
    }
    out.close();

     */



    return 0;
}
