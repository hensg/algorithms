#if !defined(HEAP_H)
#define HEAP_H

#include <vector>
#include <iostream>

template <typename K, typename V>
class Heap {
private:
    std::vector<std::pair<K, V>> data;
    int _last_pos;
    void swap(int a, int b);
public:
    Heap(unsigned int capacity) {
        data.resize(capacity);
        for (int i = 0; i < capacity; i++)
            data[i].first = INT32_MAX;
        _last_pos = -1;
    }
    unsigned int size() { return _last_pos + 1; };
    std::pair<K, V> extract_min();
    const std::pair<K, V>& find_min();
    void insert(K k, V v);
    void print();
};


#endif