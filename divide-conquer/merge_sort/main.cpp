#include <iostream>
#include <vector>
#include <cmath>

std::vector<int> merge_sort(std::vector<int> &vector_of_ints, unsigned long begin, unsigned long end) {
    if (end - begin == 2) {
        std::vector<int> ints;
        int a = begin, b = end - 1;
        if (vector_of_ints[a] <= vector_of_ints[b]) {
            ints.push_back(vector_of_ints[a]);
            ints.push_back(vector_of_ints[b]);
        } else {
            ints.push_back(vector_of_ints[b]);
            ints.push_back(vector_of_ints[a]);
        }
        return ints;
    }

    std::vector<int> left = merge_sort(vector_of_ints, begin, begin + ((end - begin) / 2));
    std::vector<int> right = merge_sort(vector_of_ints, begin + ((end - begin) / 2), end);
    std::vector<int> combined;

    int i = 0, j = 0;
    while (i < left.size() || j < left.size()) {
        if ((i < left.size() && left[i] <= right[j]) || j >= right.size()) {
            combined.push_back(left[i]);
            i++;
        } else {
            combined.push_back(right[j]);
            j++;
        }
    }
    return combined;
}

void bubble_sort(std::vector<int> &vec_ints) {
    int tmp;
    for (int i = 0; i < vec_ints.size(); i++) {
        for (int j = i+1; j < vec_ints.size(); j++) {
            if (vec_ints[i] > vec_ints[j]) {
                tmp = vec_ints[i];
                vec_ints[i] = vec_ints[j];
                vec_ints[j] = tmp;
            }
        }
    }
}

void print_sample(std::vector<int> &vec_ints, size_t size) {
    size_t n = (size > vec_ints.size()) ? vec_ints.size() : size;
    for (int i = 0; i < n; i++)
        std::cout << vec_ints[i] << ", ";
    std::cout << std::endl;
}

int main() {
    int n = pow(2, 15);

    std::cout << "Building list of size: " << n << std::endl;
    std::vector<int> unsorted(n), bubble_unsorted(n);
    for (int i = n-1; i >= 0; i--) {
        unsorted[i] = n - i;
        bubble_unsorted[i] = n - i;
    }

    std::cout << "Unsorted: ";
    print_sample(unsorted, 10);


    // merge sort
    auto start = std::chrono::system_clock::now();
    std::vector<int> sorted = merge_sort(unsorted, 0, n);
    std::chrono::duration<double> elapsed_seconds = std::chrono::system_clock::now()-start;

    std::cout << "Merge Sorted (took=" << elapsed_seconds.count() << "s): ";
    print_sample(sorted, 10);


    // bubble sort
    auto start_bubble = std::chrono::system_clock::now();
    bubble_sort(bubble_unsorted);
    std::chrono::duration<double> elapsed_seconds_bubble = std::chrono::system_clock::now()-start;

    std::cout << "Bubble sorted (took=" << elapsed_seconds_bubble.count() << "s): ";
    print_sample(bubble_unsorted, 10);

    return 0;
}
