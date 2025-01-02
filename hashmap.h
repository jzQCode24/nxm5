// HashMap.h
#ifndef HASHMAP_H
#define HASHMAP_H

#include "ExpandableLinkedHashTable.h"
#include <utility>
#include <stdexcept>
#include <set>

template <typename K, typename V>
class HashMap {
public:
    HashMap(int initialSize = 16, double maxLoadFactor = 0.7);
    V& getValue(const K& key);
    void insert(const std::pair<K, V>& keyValuePair);
    bool containsKey(const K& key) const;
    V& Remove(const K& key);
    V& Remove(const K& key, const V& val);
    void Clear();
    int getSize() const;
    std::set<K> keySet() const;

private:
    ExpandableLinkedHashTable<std::pair<K, V>, K, V> hashTable;
};

#endif // HASHMAP_H
