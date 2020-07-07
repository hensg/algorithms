#include <iostream>
#include <vector>
#include "nested_loop_inversion_counter.h"
#include "merge_sort_inversion_count.h"
#include <fstream>

int main(int argc, char * argv[]) {
    if (argc != 2) {
        std::cout << "Missing argument! ./runnable <input_file_path>\n";
        return 1;
    }
    std::ifstream in(argv[1]);
    if (!in) {
        std::cout << "Cannot open input file.\n";
        return 1;
    }

    std::vector<int> array;
    std::string str;
//    for (int i = 10; i > 0; i--) {
//        array.push_back(i);
//    }
    while (in) {
        std::getline(in, str);
        if (!str.empty())
            array.push_back(std::stoi(str));
    }


    //std::cout << "Num inversions O(n^2): " << count_inversions(array) << std::endl;
    auto merge_sorted = merge_sort_and_count_inversions(array, 0, array.size()-1);
    std::cout << "Num inversions O(nlogn): " << merge_sorted.inversions_count << std::endl;

    std::cout << "Sorted: ";
    for (auto &elem : merge_sorted.sorted_array) {
        std::cout << elem << ", ";
    }
    std::cout << std::endl;

    return 0;
}
