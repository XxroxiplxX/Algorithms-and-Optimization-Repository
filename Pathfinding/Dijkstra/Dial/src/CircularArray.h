//
// Created by korycki on 29.05.2023.
//

#ifndef DIAL_CIRCULARARRAY_H
#define DIAL_CIRCULARARRAY_H



#include <iostream>

template <class T> struct Node {
    Node<T>* next;
    T key;
    Node() : next(nullptr) {}
    ~Node() {
        //next = nullptr;
    }

};
template <class T> class List {
    Node<T>* head;
    void clear(Node<T>*);
    int size;
    int c = 0;
public:
    List() : head(nullptr), size(0) {}
    T get_front();
    void push_front(T element);
    bool empty();
    void remove_front();
    ~List();
    int get_size();
    void remove_element(T element);
};

template<class T>
T List<T>::get_front() {
    return head->key;
}

template<class T>
void List<T>::push_front(T element) {


    if (head != nullptr) {
        auto head_cp = head;
        head = new Node<T>();
        head->next = head_cp;
        head->key = element;
    } else {
        head = new Node<T>();
        head->key = element;
    }
    size++;
}

template<class T>
bool List<T>::empty() {
    return head == nullptr;
}

template<class T>
void List<T>::remove_front() {
    if (head) {
        auto tmp = head;
        head = head->next;
        tmp->next = nullptr;
        delete tmp;
        size--;
    }
    if (size == 0) {

        //head = nullptr;
    }
}

template<class T>
List<T>::~List() {
    clear(head);
}

template<class T>
void List<T>::clear(Node<T>* node) {
    if (node == nullptr) return;
    if (node->next == nullptr) {

        delete node;
    } else {
        clear(node->next);
    }
}

template<class T>
int List<T>::get_size() {
    return size;
}

template<class T>
void List<T>::remove_element(T element) {
    if (!head) {
        return;
    }
    if (!head->next) {
        remove_front();
        return;
    }
    if (head->key == element) {
        remove_front();
        return;
    }
    auto tmp = head;
    Node<T>* prev;
    while (tmp->next and tmp->key != element) {
        prev = tmp;
        tmp = tmp->next;
    }
    //tmp is a node with specified element
    if (tmp->next) {
        prev->next = tmp->next;
        delete tmp;
        size--;
    }
}


template <class T> class CircularArray {
    std::vector<List<T>> array;
    int size;
public:
    T get_element(unsigned long long& key);
    void set_element(T element, unsigned long long& key);
    CircularArray() = default;
    explicit CircularArray(int _size);
    ~CircularArray();
    void delete_element(unsigned long long& key, T element);
    int get_size();
    int get_full_size();
    bool empty(unsigned long long& key);
    int get_bucket_size(unsigned long long& key);
};

template<class T>
CircularArray<T>::CircularArray(int _size) : size(_size) {
    array = std::vector<List<T>>(_size, List<T>());
}

template<class T>
void CircularArray<T>::set_element(T element, unsigned long long& key) {
    //std::cout << key << std::endl;
    array[key%size].push_front(element);
}

template<class T>
T CircularArray<T>::get_element(unsigned long long& key) {
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
        sum_size += array[i].get_size();
    }
    return sum_size;
}

template<class T>
int CircularArray<T>::get_bucket_size(unsigned long long& key) {
    return array[key].get_size();
}


#endif //DIAL_CIRCULARARRAY_H
