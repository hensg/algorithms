#include <iostream>
#include "nested_loop_inversion_counter.h"

//O(n^2)
unsigned long count_inversions(const std::vector<int> array) {
    unsigned long count = 0;
    for (int i = 0; i < array.size(); i++) {
        for (int j = i+1; j < array.size(); j++) {
            if (array[i] > array[j])
                count++;
        }
    }
    return count;
}

