#include "hash_set.h"
#include <iostream>
#include <cassert>

void test_hash_set() {
    HashSet<long> hash_set(1000);
    hash_set.insert(0L);
    hash_set.insert(0L);
    hash_set.insert(10L);
    hash_set.insert(10L);
    hash_set.insert(-333L);
    hash_set.insert(-333L);
    hash_set.insert(-333L);
    hash_set.insert(11L);
    hash_set.insert(12L);
    hash_set.insert(-333L);
    hash_set.insert(-333L);
    hash_set.insert(-333L);
    hash_set.insert(-333L);
    hash_set.insert(-333L);
    hash_set.insert(-999L);
    
    std::cout << "Size is: " << hash_set.get_size() << std::endl;
    assert(hash_set.get_size() == 6);
    assert(hash_set.lookup(10L) == true);
    assert(hash_set.lookup(11L) == true);
    assert(hash_set.lookup(98L) == false);
    assert(hash_set.lookup(0L) == true);
    assert(hash_set.lookup(-333L) == true);
    assert(hash_set.lookup(999L) == false);

    hash_set.remove(-333L);
    assert(hash_set.lookup(-333L) == false);
};

void test_2_sum() {
    const int target_sum = 56;

    HashSet<long> hash_set(8);
    const int size = 9;
    const int arr[]{ 99L, 23L, 23L, 38L, 44L, 88L, 48L, 75L, 33L};
    for (int i = 0; i < size; i++)//O(n)
        hash_set.insert(arr[i]);//O(1)

    long sum = 0;
    for (int i = 1; i < size; i++) {//O(n)
        sum = target_sum - arr[i];
        if (hash_set.lookup(sum)) {//O(1)
            std::cout << arr[i] << "+" << sum << "=" << target_sum << std::endl;
            return;
        }
    }
    assert(true == false);//shouldn't execute
};

int main(int argc, char* argv[]) {
    test_hash_set();
    test_2_sum();
    return 0;
}