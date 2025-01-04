#include "HashMap.h"
#include <functional>
#include <cmath> // 包含std::hash
#include <set>

template <typename K, typename V>
HashMap<K, V>::HashMap(int initialSize, double maxLoadFactor)
    : hashTable(initialSize, maxLoadFactor) {}

template <typename K, typename V>
V& HashMap<K, V>::getValue(const K& key) {
    int bucket;
    DbListNode<std::pair<K, V>>* node = hashTable.findPos(key, bucket);
    if (node) {
        return node->getData().second;
    } else {
        static V defaultVal;
        return defaultVal;
    }
}

template <typename K, typename V>
std::set<K> HashMap<K, V>::keySet() {
    std::set<K> keys;
    for (int i = 0; i < hashTable.getCapacity(); ++i) {
        DbLinkedList<std::pair<K, V>>& bucket = hashTable.buckets[i];
        DbListNode<std::pair<K, V>>* node = bucket.getHead();
        while (node != nullptr) {
            keys.insert(node->getData().first);
            node = node->getNext();
        }
    }
    return keys;
}

template <typename K, typename V>
bool HashMap<K, V>::containsKey(const K& key) const {
    return hashTable.containsKey(key);
}

template <typename K, typename V>
void HashMap<K, V>::Insert(const std::pair<K, V>& k_v) {
    hashTable.put(k_v.first, k_v.second);
}

template <typename K, typename V>
V& HashMap<K, V>::Remove(const K& key) {
    V temp;
    int bucket;
    DbListNode<std::pair<K, V>>* node = hashTable.findPos(key, bucket);
    if (node) {
        temp = node->getData().second;
        hashTable.Remove(key, temp);
    }
    static V defaultVal;
    return temp;
}

template <typename K, typename V>
V& HashMap<K, V>::Remove(const K& key, const V& val) {
    V temp;
    int bucket;
    DbListNode<std::pair<K, V>>* node = hashTable.findPos(key, bucket);
    if (node && node->getData().second == val) {
        temp = node->getData().second;
        hashTable.Remove(key, temp);
    }
    static V defaultVal;
    return temp;
}

template <typename K, typename V>
void HashMap<K, V>::Clear() {
    hashTable.clear();
}

template <typename K, typename V>
int HashMap<K, V>::getSize() const {
    return hashTable.getSize();
}

template <typename K, typename V>
HashMap<K, V>::~HashMap() {
    hashTable.~ExpandableLinkedHashTable();
}

template <typename K, typename V>
void HashMap<K, V>::resizeTable() {
    hashTable.resizeTable();
}
