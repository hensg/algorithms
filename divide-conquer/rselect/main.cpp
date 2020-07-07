#include <iostream>
#include <vector>

int COUNT = 0;

void swap(std::vector<int>& data_arr, int a, int b) {
    int tmp = data_arr[b];
    data_arr[b] = data_arr[a];
    data_arr[a] = tmp;
}

int choose_pivot(std::vector<int>& data_arr, int begin, int end) {
    int mid = begin + ((end - begin) / 2);
    if ((data_arr[begin] > data_arr[mid]) != (data_arr[begin] > data_arr[end]))
        return begin;
    if ((data_arr[mid] > data_arr[begin]) != (data_arr[mid] > data_arr[end]))
        return mid;
    return end;
}

int partition(std::vector<int>& data_arr, int begin, int end, int pivot_pos) {
    int pivot = data_arr[pivot_pos];
    swap(data_arr, pivot_pos, begin);

    int j = begin;
    for (int i = begin+1; i <= end; i++) {
        if (data_arr[i] < pivot) {
            swap(data_arr, i, ++j);
        }
    }
    swap(data_arr, begin, j);
    return j;
}

int rselect(std::vector<int>& data_arr, int begin, int end, int ith_element) {
    COUNT += end - begin;
    if (end - begin <= 1)
        return data_arr[begin];

    int pivot_pos = partition(data_arr, begin, end, choose_pivot(data_arr, begin, end));

    if (pivot_pos == ith_element)
        return data_arr[pivot_pos];

    if (ith_element < pivot_pos)
        return rselect(data_arr, begin, pivot_pos - 1, ith_element);
    else
        return rselect(data_arr, pivot_pos + 1, end, ith_element);
}

int main() {
    std::vector<int> data_arr {
        10, 15, 11, 12, 18, 19, 17, 13, 14
    };

    int third_greatest_element = 3;

    int d = rselect(data_arr, 0, data_arr.size() - 1, third_greatest_element);
    std::cout << "Third greatest element is: " << d << std::endl;
    std::cout << "Elements read: " << COUNT << std::endl;
    return 0;
}
