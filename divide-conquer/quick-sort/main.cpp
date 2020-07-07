#include <iostream>
#include <vector>
#include <fstream>

int COMPARISONS = 0;

void swap(std::vector<int> &arr, int begin, int end) {
    int tmp = arr[end];
    arr[end] = arr[begin];
    arr[begin] = tmp;
}

/**
 * Using randomization to have an avg(n logn) time complexity
 * @return randomized pivot (the median of three)
 */
int chose_pivot(std::vector<int> &arr, int begin, int end) {
    //return begin;
    //return end;
    int mid = begin + ((end-begin)/2);
    if (arr[begin] > arr[mid] != arr[begin] > arr[end])
        return begin;
    if (arr[mid] > arr[begin] != arr[mid] > arr[end])
        return mid;
    return end;
}

/**
 * partition the array, lower than pivot to the left
 * and bigger than pivot to the right
 * @return the pivot position
 */
int partition(std::vector<int> &arr, int begin, int end) {
    int pivot_pos = chose_pivot(arr, begin, end);
    swap(arr, pivot_pos, begin); //move pivot to the beginning
    //std::cout << "pivot: " << arr[begin] << std::endl;

    int i = begin;
    for (int j = begin; j <= end; j++) {
        if (arr[j] < arr[begin]) {
            i++;
            swap(arr, i, j);
        }
    }
    swap(arr, begin, i);
    return i;
}

void quick_sort(std::vector<int> &arr, int begin, int end) {
    //std::cout << "begin: " << begin << ", end: " << end << std::endl;
    if (end - begin <= 0)
        return;
    COMPARISONS += end - begin;
    int pivot_pos = partition(arr, begin, end);
    quick_sort(arr, begin, pivot_pos-1);
    quick_sort(arr, pivot_pos+1, end);
}

int main() {
    std::cout << "Quick sort" << std::endl;

    std::vector<int> arr;
    std::string str;
    std::ifstream file;

    file.open("../data.txt");
    while (std::getline(file, str) && !str.empty()) {
        arr.push_back(stoi(str));
    }
    file.close();

    std::cout << "Array size: " << arr.size() << std::endl;
    //std::vector<int> arr{ 3, 8, 2, 5, 1, 4, 7, 6 };
    //std::vector<int> arr{ 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1 };
    quick_sort(arr, 0, arr.size()-1);

    std::cout << "\nSorted items:\n";
    for (int i : arr)
        std::cout << i << ',';

    std::cout << "\nComparisons: " << COMPARISONS;
    return 0;
}
