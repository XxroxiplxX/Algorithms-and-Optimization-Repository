//
// Created by piotrkali on 4/4/23.
//
#include <iostream>
#include "random"
void random_keys(int n, std::mt19937 mt, std::uniform_int_distribution<int>dis) {

    for (int i = 0; i < n; i++) {
        std::cout << dis(mt) << std::endl;
    }
}
void random_ascending_keys(int n, std::mt19937 mt) {
    std::uniform_int_distribution<int>distro(0,100);
    int count = 0;
    int c = 0;
    while (count != n) {
        if (distro(mt) <= 70) {
            std::cout << c << std::endl;
            count++;
        }
        c++;
    }

}
void random_descending_keys(int n, std::mt19937 mt) {
    std::uniform_int_distribution<int>distro(0,100);
    int count = 0;
    int c = 2*n-1;
    while (count != n) {
        if (distro(mt) <= 70) {
            std::cout << c << std::endl;
            count++;
        }
        c--;
    }

}
int main(int argc, char** argv ) {
    srand(time(nullptr));
    std::mt19937 mt(rand());
    int n = std::stoi(argv[1]);
    std::uniform_int_distribution<int>dis(0,2*n-1);
    auto s = std::string(argv[2]);
    std::cout << n << std::endl;
    if (s == "--asc") {
        random_ascending_keys(n,mt);
    }
    if (s == "--desc") {
        random_descending_keys(n,mt);
    }
    if (s == "--rand") {
        random_keys(n,mt, dis);
    }
    return 0;
}



