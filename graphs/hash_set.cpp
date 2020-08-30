#include "hash_set.h"

template<>
const int HashSet<long>::hash(long key) {
    long tmp = key < 0 ? key * -1 : key;
    return (33 * tmp - 7) % capacity;
};

template <typename K>
void HashSet<K>::insert(K key) {
    const int hash_value = hash(key);
    LinkedElement<K>* elem = &hash_table[hash_value];
    if (!elem->used) {
        elem->key = key;
        elem->used = true;
        elem->next = nullptr;
        this->size++;
        this->bucket_size[hash_value]++;
    } else if (elem->key != key) {
        while (elem->next != nullptr && elem->next->key != key) {
            elem = elem->next;
        }
        if (elem->next == nullptr) {
            elem->next = new LinkedElement<K>();
            elem->next->key = key;
            elem->next->used = true;
            elem->next->next = nullptr;
            this->size++;
            this->bucket_size[hash_value]++;
        }
    }
}

template <typename K>
bool HashSet<K>::lookup(K key) {
    LinkedElement<K>* elem = &hash_table[hash(key)];
    while (elem && elem->key != key)
        elem = elem->next;
    return elem != nullptr && elem->used;
};

template <typename K>
void HashSet<K>::remove(K key) {
    const int hash_value = hash(key);
    LinkedElement<K>* elem = &hash_table[hash_value];
    if (elem->key == key) {
        elem->key = 0;
        elem->used = false;
        this->size--;
        this->bucket_size[hash_value]--;
    } else {
        while (elem->next && elem->next->key != key)
            elem = elem->next;

        if (elem->next != nullptr) {
            LinkedElement<K>* tmp = elem->next;
            tmp->key = 0;
            tmp->used = false;
            elem->next = elem->next->next;
            tmp->next = nullptr;
            delete tmp;
            this->size--;
            this->bucket_size[hash_value]--;
        }
    }
};

template class HashSet<long>;