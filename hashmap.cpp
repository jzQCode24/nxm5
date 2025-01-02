// HashMap.cpp
#include "HashMap.h"

template <typename K, typename V>
HashMap<K, V>::HashMap(int initialSize, double maxLoadFactor)
    : hashTable(initialSize, maxLoadFactor) {}

template <typename K, typename V>
V& HashMap<K, V>::getValue(const K& key) {
    std::pair<K, V> keyValuePair(key, V());
    int bucket;
    auto* node = hashTable.findPos(key, bucket);
    if (node != nullptr) {
        return node->getValue().second;
    } else {
        throw std::out_of_range("Key not found");
    }
}

template <typename K, typename V>
void HashMap<K, V>::insert(const std::pair<K, V>& keyValuePair) {
    hashTable.Insert(keyValuePair);
}

template <typename K, typename V>
bool HashMap<K, V>::containsKey(const K& key) const {
    return hashTable.Search(key);
}

template <typename K, typename V>
V& HashMap<K, V>::Remove(const K& key) {
    std::pair<K, V> keyValuePair(key, V());
    int bucket;
    auto* node = hashTable.findPos(key, bucket);
    if (node != nullptr) {
        std::pair<K, V> removed = node->getValue();
        hashTable.Remove(key, removed);
        return removed.second;
    } else {
        throw std::out_of_range("Key not found");
    }
}

template <typename K, typename V>
V& HashMap<K, V>::Remove(const K& key, const V& val) {
    std::pair<K, V> keyValuePair(key, val);
    int bucket;
    auto* node = hashTable.findPos(key, bucket);
    if (node != nullptr && node->getValue() == keyValuePair) {
        hashTable.Remove(key, keyValuePair);
        return keyValuePair.second;
    } else {
        throw std::out_of_range("Key-value pair not found");
    }
}

template <typename K, typename V>
void HashMap<K, V>::Clear() {
    hashTable.Clear();
}

template <typename K, typename V>
int HashMap<K, V>::getSize() const {
    return hashTable.GetSize();
}

template <typename K, typename V>
std::set<K> HashMap<K, V>::keySet() const {
    std::set<K> keys;
    for (int i = 0; i < hashTable.GetCapacity(); ++i) {
        if (auto* list = hashTable.table[i]) { // Assuming table is accessible
            for (auto& node : *list) {
                keys.insert(node.getKey());
            }
        }
    }
    return keys;
}
