#include <vector>
#include <iostream>
#include "heap.h"

template<typename K, typename V>
void Heap<K, V>::swap(int a, int b) {
    std::pair<K, V> tmp = data[a];
    data[a] = data[b];
    data[b] = tmp;
}

template<typename K, typename V>
void Heap<K, V>::print() {
    for (int i = 0; i < size(); i++) {
        std::cout << data[i].first << ",";
    }
};

template<typename K, typename V>
void Heap<K, V>::insert(K k, V v) {
    std::pair<K, V> node(k, v);
    _last_pos++;
    data[_last_pos] = node;
    if (_last_pos >= 1) {
        int evaluating_pos = _last_pos;
        int parent_pos = ((evaluating_pos+1)/2)-1;
        while (parent_pos >= 0 && data[parent_pos].first > data[evaluating_pos].first) {
            swap(parent_pos, evaluating_pos);
            evaluating_pos = parent_pos;
            parent_pos = ((evaluating_pos+1)/2)-1;
        }
    }
};

template<typename K, typename V>
const std::pair<K, V>& Heap<K, V>::find_min() {
    if (size() == 0)
        throw std::runtime_error("Cannot find_min() in an empty heap");
    return data[0];
};

template<typename K, typename V>
std::pair<K, V> Heap<K, V>::extract_min() {
    if (size() == 0)
        throw std::runtime_error("Cannot extract_min() of an empty heap");

    std::pair<K,V> node = data[0];
    data[0] = data[_last_pos];
    data[_last_pos] = std::pair<K,V>();
    _last_pos--;
    if (_last_pos >= 1) {
        int parent_pos = 0, left = 1, right = 2;
        int evaluating_pos = _last_pos > 1 && data[left].first > data[right].first ? right : left;
        while (evaluating_pos <= _last_pos && data[parent_pos].first > data[evaluating_pos].first) {
            swap(parent_pos, evaluating_pos);
            left = evaluating_pos*2+1;
            right = evaluating_pos*2+2;
            parent_pos = evaluating_pos;
            if (left <= _last_pos && data[left].first < data[right].first)
                evaluating_pos = left;
            else
                evaluating_pos = right;
        } 
    }
    return node;
};

template class Heap<int, bool>;