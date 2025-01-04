#include "ExpandableLinkedHashTable.h"
#include <functional>
#include <cmath> // 包含std::hash

template <typename K, typename V>
ExpandableLinkedHashTable<K, V>::ExpandableLinkedHashTable(int initialSize, double maxLoadFactor)
    : buckets(initialSize), size(0), maxLoadFactor(maxLoadFactor) {}

template <typename K, typename V>
ExpandableLinkedHashTable<K, V>::~ExpandableLinkedHashTable() {
    Clear();
}

template <typename K, typename V>
void ExpandableLinkedHashTable<K, V>::resize() {
    int newCapacity = std::ceil(buckets.getSize() * 2);
    DynamicArray<DbLinkedList<std::pair<K, V>>> newBuckets(newCapacity);

    for (int i = 0; i < buckets.getSize(); ++i) {
        DbLinkedList<std::pair<K, V>>& bucket = buckets[i];
        DbListNode<std::pair<K, V>>* node = bucket.getHead();
        while (node != nullptr) {
            int newIndex = std::hash<K>{}(node->getData().first) % newCapacity;
            newBuckets[newIndex].insertAtTail(node->getData());
            node = node->getNext();
        }
    }
    buckets = newBuckets;
}

template <typename K, typename V>
int ExpandableLinkedHashTable<K, V>::getBucketIndex(const K& key) const {
    return std::hash<K>{}(key) % buckets.getSize();
}

template <typename K, typename V>
DbListNode<std::pair<K, V>>* ExpandableLinkedHashTable<K, V>::findPos(const K& key, int &bucket) const {
    int index = getBucketIndex(key);
    bucket = index;
    DbListNode<std::pair<K, V>>* node = buckets[index].Search([&key](const std::pair<K, V>& pair) { return pair.first == key; });
    return node;
}

template <typename K, typename V>
bool ExpandableLinkedHashTable<K, V>::Search(const K& key) const {
    int bucket;
    return findPos(key, bucket) != nullptr;
}

template <typename K, typename V>
bool ExpandableLinkedHashTable<K, V>::Insert(const std::pair<K, V>& e) {
    if (containsKey(e.first)) {
        remove(e.first);
    }
    put(e.first, e.second);
    return true;
}

template <typename K, typename V>
int ExpandableLinkedHashTable<K, V>::Remove(const K& key, V& e) {
    int bucket;
    DbListNode<std::pair<K, V>>* node = findPos(key, bucket);
    if (node == nullptr) return 0;
    e = node->getData().second;
    buckets[bucket].Remove(node);
    size--;
    return 1;
}

template <typename K, typename V>
void ExpandableLinkedHashTable<K, V>::resizeTable() {
    int newCapacity = std::ceil(buckets.getSize() * 2);
    DynamicArray<DbLinkedList<std::pair<K, V>>> newBuckets(newCapacity);

    for (int i = 0; i < buckets.getSize(); ++i) {
        DbLinkedList<std::pair<K, V>>& bucket = buckets[i];
        DbListNode<std::pair<K, V>>* node = bucket.getHead();
        while (node != nullptr) {
            int newIndex = std::hash<K>{}(node->getData().first) % newCapacity;
            newBuckets[newIndex].insertAtTail(node->getData());
            node = node->getNext();
        }
    }
    buckets = newBuckets;
}

template <typename K, typename V>
void ExpandableLinkedHashTable<K, V>::Clear() {
    for (int i = 0; i < buckets.getSize(); ++i) {
        buckets[i].Clear();
    }
    buckets.clear();
    size = 0;
}

template <typename K, typename V>
int ExpandableLinkedHashTable<K, V>::getCapacity() const {
    return buckets.getSize();
}

template <typename K, typename V>
int ExpandableLinkedHashTable<K, V>::getSize() const {
    return size;
}

template <typename K, typename V>
int ExpandableLinkedHashTable<K, V>::getBucket(const K& k) const {
    return getBucketIndex(k);
}

template <typename K, typename V>
int ExpandableLinkedHashTable<K, V>::getBucketSize(int i) const {
    return buckets[i].getSize();
}
