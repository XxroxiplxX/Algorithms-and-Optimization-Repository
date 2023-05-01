//
// Created by piotrkali on 4/24/23.
//

#ifndef A_LOGGER_H
#define A_LOGGER_H


#include <fstream>
#include <iostream>
#include <vector>
//static int currentLine = 1;
namespace Logging {
    class Logger {
        std::string file_name;
        std::ofstream output;


    public:
        Logger(std::string filename) : file_name(filename) {
            output.open(file_name);
        }
        void log(std::string msg);
        void log(std::string msg, int param);
        ~Logger() {
            output.close();
        }
        void close_logger() {
            output.close();
        }
    };
}


#endif //A_LOGGER_H
