#ifndef INTRODUCTION_LOGGER_H
#define INTRODUCTION_LOGGER_H

#include <fstream>
#include <iostream>
#include <vector>
//static int currentLine = 1;
namespace Logging {
    class Logger {
        std::vector<std::string> log_list;
        std::string file_name;
        std::ofstream output;


    public:
        Logger(std:: string filename) : file_name(filename) {
            output.open(file_name);
        }
        void log(std::string msg);
        void log(std::string msg, int param);
        void log(int x);
        ~Logger() {
            output.close();
        }
        void close_logger() {
            for (auto it : log_list) {
                std::cout << it << std::endl;
            }
            output.close();
        }
    };
}
#endif //COMPILER_LOGGER_H