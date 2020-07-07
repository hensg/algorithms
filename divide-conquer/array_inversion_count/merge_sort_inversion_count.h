//
// Created by Henrique Goulart on 16/06/20.
//

#ifndef ARRAY_INVERSION_COUNT_MERGE_SORT_INVERSION_COUNT_H
#define ARRAY_INVERSION_COUNT_MERGE_SORT_INVERSION_COUNT_H

#include <vector>

struct SortedArrayAndCount {
    unsigned long inversions_count = 0;
    std::vector<int> sorted_array;
};

SortedArrayAndCount merge_sort_and_count_inversions(std::vector<int> &array_of_ints, unsigned long start, unsigned long end);

#endif //ARRAY_INVERSION_COUNT_MERGE_SORT_INVERSION_COUNT_H
