#include "binary_search_tree.h"
#include <cassert>

void test_ordered_data_insertion_rebalance() {
    BST<int> bst;
    for (int i = 1; i < 16; i++)
        bst.insert(i);
    bst.print();

    assert(bst.get_height() == 4);
    assert(bst.get_root().data == 8);
};

void test_inverted_order_data_insertion_rebalance() {
    BST<int> bst;
    for (int i = 15; i > 0; i--)
        bst.insert(i);
    bst.print();

    assert(bst.get_height() == 4);
    assert(bst.get_root().data == 8);
};

int main(int argc, char* argv[]) {
    test_ordered_data_insertion_rebalance();
    test_inverted_order_data_insertion_rebalance();
    return 0;
}