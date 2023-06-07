//
// Created by korycki on 07.06.2023.
//
#include "CircularArray.h"

CircularArray::CircularArray(int _size, DirectedGraph &_graph) : size(_size), graph(_graph){
    array = std::vector<std::list<int>>(_size, std::list<int>());
}

int CircularArray::get_element(unsigned long long &key) {
    return array[key%size].front();
}

void CircularArray::set_element(int element, unsigned long long &key) {
    array[key%size].push_front(element);
    graph.get_vertex(element)->position_in_bucket = array[key%size].begin();
}

void CircularArray::delete_element(unsigned long long int &key, int element) {
    array[key%size].erase(graph.get_vertex(element)->position_in_bucket);
}

int CircularArray::get_size() {
    return size;
}

int CircularArray::get_full_size() {
    int sum = 0;
    for (auto list : array) {
        sum += list.size();
    }
    return sum;
}

bool CircularArray::empty(unsigned long long int &key) {
    return array[key%size].empty();
}

int CircularArray::get_bucket_size(unsigned long long int &key) {
    return array[key%size].size();
}

