#include "merge_sort_inversion_count.h"

//O(n log n)
SortedArrayAndCount merge_sort_and_count_inversions(std::vector<int> &array_of_ints, unsigned long start, unsigned long end) {
    if (end - start == 0) {
        SortedArrayAndCount single;
        single.sorted_array.push_back(array_of_ints[start]);
        return single;
    }
    else if (end - start == 1) {
        SortedArrayAndCount sortedArrayAndCount;
        unsigned long a = start, b = end;
        if (array_of_ints[a] > array_of_ints[b]) {
            sortedArrayAndCount.sorted_array.push_back(array_of_ints[b]);
            sortedArrayAndCount.sorted_array.push_back(array_of_ints[a]);
            sortedArrayAndCount.inversions_count++;
        } else {
            sortedArrayAndCount.sorted_array.push_back(array_of_ints[a]);
            sortedArrayAndCount.sorted_array.push_back(array_of_ints[b]);
        }
        return sortedArrayAndCount;
    }

    int mid = start + ((end-start)/2);
    SortedArrayAndCount left = merge_sort_and_count_inversions(array_of_ints, start, mid);
    SortedArrayAndCount right = merge_sort_and_count_inversions(array_of_ints, mid+1, end);
    SortedArrayAndCount combined;

    combined.inversions_count = left.inversions_count + right.inversions_count;

    int i = 0, j = 0;
    bool is_left_empty = left.sorted_array.size() == 0, is_right_empty = right.sorted_array.size() == 0;

    while (!is_left_empty || !is_right_empty) {
        if (is_right_empty || (!is_left_empty && left.sorted_array[i] <= right.sorted_array[j])) {
            combined.sorted_array.push_back(left.sorted_array[i]);
            i++;
            is_left_empty = (left.sorted_array.size() <= i);
        } else {
            combined.sorted_array.push_back(right.sorted_array[j]);
            combined.inversions_count += left.sorted_array.size() - i;
            j++;
            is_right_empty = (right.sorted_array.size() <= j);
        }
    }
    return combined;
}
