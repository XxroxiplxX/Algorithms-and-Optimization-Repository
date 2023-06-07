//
// Created by korycki on 29.05.2023.
//

#ifndef DIAL_CIRCULARARRAY_H
#define DIAL_CIRCULARARRAY_H



#include <iostream>
#include "DirectedGraph.h"
#include <list>
class CircularArray {
    std::vector<std::list<int>> array;
    int size;
    DirectedGraph& graph;
public:
    int get_element(unsigned long long& key);
    void set_element(int element, unsigned long long& key);
    CircularArray() = default;
    explicit CircularArray(int _size, DirectedGraph& _graph);
    explicit CircularArray(DirectedGraph &graph);
    ~CircularArray() = default;
    void delete_element(unsigned long long& key, int element);
    int get_size();
    int get_full_size();
    bool empty(unsigned long long& key);
    int get_bucket_size(unsigned long long& key);
};
/*
template<class T>
CircularArray<T>::CircularArray(int _size, DirectedGraph& _graph) : size(_size), graph(_graph) {
    array = std::vector<std::list<T>>(_size, std::list<T>());
}

template<class T>
void CircularArray<T>::set_element(int element, T& key) {
    //std::cout << key << std::endl;
    array[key%size].push_front(element);
}

template<class T>
T CircularArray<T>::get_element(T& key) {
    return array[key%size].get_front();
}

template<class T>
CircularArray<T>::~CircularArray() {

}

template<class T>
void CircularArray<T>::delete_element(unsigned long long& key, T element) {
    array[key%size].remove_element(element);
}

template<class T>
int CircularArray<T>::get_size() {
    return size;
}

template<class T>
bool CircularArray<T>::empty(unsigned long long& key) {
    return array[key%size].empty();
}

template<class T>
int CircularArray<T>::get_full_size() {
    int sum_size = 0;
    for (int i = 0; i < size; i++) {
        sum_size += array[i].size();
    }
    return sum_size;
}

template<class T>
int CircularArray<T>::get_bucket_size(unsigned long long& key) {
    return array[key].get_size();
}
*/

#endif //DIAL_CIRCULARARRAY_H
