#include <vector>
#include <cassert>
#include "heap.h"
#include "median_maintainer.cpp"

void test_heap_properties() {
    Heap<int, bool> heap(10); 
    const std::vector<int> seq{13, 9, 11, 4, 4, 8, 9, 12};
    for (auto& k: seq) {
        heap.insert(k, false);
    }
    heap.print();
    assert(heap.extract_min().first == 4);
    assert(heap.extract_min().first == 4);
    assert(heap.extract_min().first == 8);
    assert(heap.extract_min().first == 9);
    assert(heap.extract_min().first == 9);
    assert(heap.extract_min().first == 11);
    assert(heap.extract_min().first == 12);
    assert(heap.extract_min().first == 13);
}

//heap can be used for keep max updated
void test_heap_properties_inversed() {
    Heap<int, bool> heap(10); 
    const std::vector<int> seq{13, 9, 11, 4, 4, 8, 9, 12};
    for (auto& k: seq) {
        heap.insert(k * -1, false);
    }
    heap.print();
    assert(heap.extract_min().first * -1 == 13);
    assert(heap.extract_min().first * -1 == 12);
    assert(heap.extract_min().first * -1 == 11);
    assert(heap.extract_min().first * -1 == 9);
    assert(heap.extract_min().first * -1 == 9);
    assert(heap.extract_min().first * -1 == 8);
    assert(heap.extract_min().first * -1 == 4);
    assert(heap.extract_min().first * -1 == 4);
}

void median_maintenance() {
    MedianMaintainer mm(10);
    mm.insert(2);
    mm.insert(1);
    mm.insert(5);
    mm.insert(4);
    mm.insert(3);
    
    std::cout << "median is: " << mm.median() << std::endl;
    assert(mm.median() == 3);
}

void test_sum_of_medians() {
    MedianMaintainer mm(10);
    std::vector<int> values{1,666,10,667,100,2,3};
    int median_sum = 0;
    for (auto& i: values) {
        mm.insert(i);
        median_sum += mm.median();
    }
    median_sum = median_sum % 10000;
    std::cout << "Median sum mod :" << median_sum << std::endl;
    assert(median_sum == 142);

    std::vector<int> values2{6331,2793,1640,9290,225,625,6195,2303,5685,1354};
    MedianMaintainer mm2(10);
    median_sum = 0;
    for (auto& i: values2) {
        mm2.insert(i);
        median_sum += mm2.median();
    }
    median_sum = median_sum % 10000;
    std::cout << "Median sum mod :" << median_sum << std::endl;
    assert(median_sum == 9335);
}

int main(int argc, char const *argv[]) {
    //test_heap_properties();
    //test_heap_properties_inversed();
    //median_maintenance();
    test_sum_of_medians();
    return 0;
}
