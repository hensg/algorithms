#if !defined(BINARY_SEARCH_TREE)
#define BINARY_SEARCH_TREE

template <typename T>
struct Node {
    T data;
    Node<T>* parent;
    Node<T>* left;
    Node<T>* right;
    unsigned int size;
    unsigned int height;
};

template <typename T>
class BST {
private:
    Node<T>* root;
    void recalculate_sizes(Node<T>* node);
    void recalculate_height(Node<T>* node);
    void rebalance(Node<T>* node);
    void rotate_left(Node<T>* subtree_root);
    void rotate_right(Node<T>* subtree_root);
public:
    BST() {};
    ~BST() {
        Node<T>* tmp = root;
        while (tmp->parent != nullptr) {
            while (tmp->left != nullptr) {
                tmp = tmp->left; 
            }
            if (tmp->right != nullptr)
                tmp = tmp->right;
            if (tmp->size == 1 && tmp->parent != nullptr) {
                tmp = tmp->parent;
                if (tmp->right != nullptr && tmp->right->size == 1) {
                    delete tmp->right;
                    tmp->right = nullptr;
                }
                if (tmp->left != nullptr && tmp->left->size == 1) {
                    delete tmp->left;
                    tmp->left = nullptr;
                }
                recalculate_sizes(tmp);
            }
        }
        delete root;
        root = nullptr;
    };
    void insert(T data);
    void print();
    Node<T>& get_root() { return *root; }
    unsigned int get_height() { return root->height; };
    unsigned int get_size() { return root->size; };
};

#endif