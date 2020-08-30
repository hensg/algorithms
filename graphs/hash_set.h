#if !defined(HASH_SET_H)
#define HASH_SET_H

template <typename K>
struct LinkedElement {
    K key;
    bool used = false;
    LinkedElement* next = nullptr;
};

template <typename K>
class HashSet {
private:
    unsigned int capacity = 0;
    unsigned int size = 0;
    LinkedElement<K>* hash_table = nullptr;
    int* bucket_size = nullptr;
    const int hash(K key);
public:
    HashSet(unsigned int capacity) {
        this->hash_table = new LinkedElement<K>[capacity];
        this->bucket_size = new int[capacity];
        this->capacity = capacity; 
        this->size = 0;
    }
    ~HashSet() {
        LinkedElement<K>* tmp = nullptr;
        LinkedElement<K>* previous = nullptr;
        for (int i = 0; i < this->capacity; i++) {
            tmp = &hash_table[i];
            while (tmp && tmp->used) {
                previous = tmp;
                tmp = tmp->next;
                if (previous != &hash_table[i])
                    delete previous;
            };
        }
        delete[] hash_table;
    }
    const float get_load() { return (float)size / capacity; }
    const int get_size() { return size; }
    const int get_bucket_size(K key) { return bucket_size[hash(key)]; }
    void insert(K key);
    bool lookup(K key);
    void remove(K key);
};


#endif