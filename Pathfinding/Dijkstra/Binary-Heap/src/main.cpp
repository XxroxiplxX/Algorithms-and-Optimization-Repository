#include <iostream>
#include "Parsers.h"
#include <chrono>
#include "Dijkstra.h"
#include <algorithm>
#include <Logger.h>


#define TIMEOUT 14400
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

    Flag second;
    GraphParser* graphParser;
    SourceParser* sourceParser;
    PairToPairParser* pairToPairParser;
    std::string graph_dir, data_dir, output_dir;

    if (std::string(argv[1]) == "-d") {

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

        output_dir = std::string(argv[6]);
    } else if (std::string(argv[5]) == "-op2p") {

        output_dir = std::string(argv[6]);
    } else {
        std::cerr << "unknown flag\n";
        exit(1);
    }

    Parameters* parameters;
    if (second == SS) {
        sourceParser = new SourceParser(data_dir);
        parameters = sourceParser->build_parameters();
        delete sourceParser;
    } else {
        pairToPairParser = new PairToPairParser(data_dir);
        parameters = pairToPairParser->build_parameters();
        delete pairToPairParser;
    }


    graphParser = new GraphParser(graph_dir);
    auto graph = graphParser->build_graph();
    delete graphParser;


    std::ofstream results(output_dir);
    long long avg_time = 0;
    int c = 0;
    std::string clean_data;
    for (int i = data_dir.length() - 1; i > 0 and data_dir[i] != '/'; i--) {
        if (data_dir[i] == '.') {
            clean_data += '_';
        } else {
            clean_data += data_dir[i];
        }
    }
    std::reverse(clean_data.begin(), clean_data.end());
    auto log_name = "logs/Bin" + clean_data + ".log";
    auto logger = Logging::Logger(log_name);

    logger.log(log_name);
    if (graph->get_highest_cost() > 16777216) {
        logger.log("terminte, highest cost critical");
        logger.close_logger();
        results << "TERMINATE2\n";
        results.close();
        exit(3);
    }
    //std::cout << "executing dial for\n" <<"graph file: " << graph_dir << std::endl;
    //std::cout << "input file: " << data_dir << std::endl;
    //std::cout << "output file: " << output_dir << std::endl;
    logger.log("executing dial for\ngraph file: " + graph_dir);
    logger.log("input file: " + data_dir);
    logger.log("output file: " + output_dir);
    if (second == SS) {
        results << "c wyniki testu dla sieci zadanej w pliku " << graph_dir << std::endl;
        results << "c i zrodel " << data_dir << std::endl;
        results << "f " << graph_dir << " " << data_dir << std::endl << "c\n";
        results << "c siec sklada sie z " << graph->get_v() << "wierzcholkow, " << graph->get_e() << " lukow,\n";
        results << "c koszty naleza do przedzialu [0," << graph->get_highest_cost() << "]:\n";
        results << "g " << graph->get_v() << " " << graph->get_e() << " 0 " << graph->get_highest_cost() << std::endl;
        results << "c " << "sredni czas wyznaczenia najkrotszych sciezek miedzy zrodlem\n";
        auto time_start = std::chrono::high_resolution_clock::now();
        for (auto source : parameters->get_sources()) {
            c++;
            logger.log("iteration: ", c);
            //std::cout << "iteration: " << c++ << std::endl;
            auto start = std::chrono::high_resolution_clock::now();
            dijkstra_to_all_nodes(graph->get_vertex(source), graph);
            auto end = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
            avg_time += duration.count();
            auto time_duration = std::chrono::duration_cast<std::chrono::seconds>(end - time_start);
            if (time_duration.count() > TIMEOUT) {
                avg_time /= c;
                results << "c a wszystkimi wierzcholkami wynosi " << avg_time << " mikrosekund | " << (long double) avg_time/1000 << " milisekund | " << (long double) avg_time/1000000 << " sekund\n";
                results << "t " << avg_time << " " << (long double) avg_time/1000 << " " << (long double) avg_time/1000000 << "\n";
                results << "c TIMEOUT\n";
                results.close();
                logger.log("timeout call");
                logger.close_logger();
                exit(1);
            }

        }
        avg_time /= parameters->get_sources().size();
        results << "c a wszystkimi wierzcholkami wynosi " << avg_time << " mikrosekund | " << (long double) avg_time/1000 << " milisekund | " << (long double) avg_time/1000000 << " sekund\n";
        results << "t " << avg_time << " " << (long double) avg_time/1000 << " " << (long double) avg_time/1000000 << "\n";
        results.close();

    } else {
        results << "c wyniki testu dla sieci zadanej w pliku " << graph_dir << std::endl;
        results << "c i par zrodlo-ujscie podanych w pliku  " << data_dir << std::endl;
        results << "f " << graph_dir << " " << data_dir << std::endl << "c\n";
        results << "c siec sklada sie z " << graph->get_v() << " wierzcholkow, " << graph->get_e() << " lukow,\n";
        results << "c koszty naleza do przedzialu [0," << graph->get_highest_cost() << "]:\n";
        results << "g " << graph->get_v() << " " << graph->get_e() << " 0 " << graph->get_highest_cost() << std::endl;
        results << "c " << "dlugosci najkrotszych sciezek\n";

        auto time_start = std::chrono::high_resolution_clock::now();

        for (auto pair : parameters->get_pairs()) {
            c++;
            logger.log("iteration: ", c);
            //std::cout << "iteration: " << c++ << std::endl;
            dijkstra_to_all_nodes(graph->get_vertex(pair.first), graph);
            auto end = std::chrono::high_resolution_clock::now();
            auto time_duration = std::chrono::duration_cast<std::chrono::seconds>(end - time_start);
            if (time_duration.count() > TIMEOUT) {
                results << "c TIMEOUT\n";
                logger.log("timeout call");
                logger.close_logger();
                results.close();
                exit(1);
            }
            results << "d " << pair.first << " " << pair.second << " " << graph->get_vertex(pair.second)->dist << std::endl;

        }
    }

    //avg_time /= sources.size();


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


    logger.log("task completed");
    logger.close_logger();
    delete graph;
    return 0;
}
