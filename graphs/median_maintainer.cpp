#include <vector>
#include "heap.h"

class MedianMaintainer {
private:
    Heap<int, bool> inverted_heap{10};
    Heap<int, bool> heap{10};
public:
    MedianMaintainer() {};
    MedianMaintainer(int capacity) {
        inverted_heap = Heap<int, bool>(capacity/2+100);
        heap = Heap<int, bool>(capacity/2+100);
    }
    void insert(int k) {
        if (inverted_heap.size() == 0) {
            inverted_heap.insert(k * -1, false);
            return;
        }
        if (k < inverted_heap.find_min().first * -1) {
            inverted_heap.insert(k * -1, false);

            if (inverted_heap.size() - heap.size() >= 2) {
                //rebalance
                std::pair<int, bool> max = inverted_heap.extract_min();
                heap.insert(max.first * -1, max.second);
            }
        } else {
            heap.insert(k, false);
            if (heap.size() - inverted_heap.size() >= 2) {
                //rebalance
                std::pair<int, bool> min = heap.extract_min();
                inverted_heap.insert(min.first * -1, min.second);
            }
        }
    }
    int median() {
        if (inverted_heap.size() == heap.size()) {
            const std::pair<int, bool>& median_inverted = inverted_heap.find_min();
            return median_inverted.first * -1;
        } else if (inverted_heap.size() > heap.size()) {
            return inverted_heap.find_min().first * -1;
        } else {
            return heap.find_min().first;
        }
    }
};