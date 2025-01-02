#ifndef EXPANDABLELINKEDHASHTABLE_H
#define EXPANDABLELINKEDHASHTABLE_H

#include "dynamicarray.h"  // 使用你提供的动态数组实现
#include "dblinkedlist.h"  // 使用你提供的双链表实现

template <typename E, typename K, typename V>
class ExpandableLinkedHashTable {
private:
    DynamicArray<DbLinkedList<E, K, V>*,K,V> table;  // 使用动态数组代替双链表的桶数组
    int size;  // 当前元素的数量
    int capacity;  // 当前桶的数量
    double maxLoadFactor;  // 最大负载因子

    // 内部函数：扩展散列表容量
    void resizeTable();

    // 内部哈希函数
    int hash(const K& key) const;

public:
    // 构造函数
    ExpandableLinkedHashTable(int initialSize = 16, double maxLoadFactor = 0.7);

    // 析构函数
    ~ExpandableLinkedHashTable();

    // 插入一个元素
    bool Insert(const E& e);

    // 查找元素
    bool Search(const K& key) const;

    // 删除一个元素
    int Remove(const K& key, E& e);

    // 清空散列表
    void Clear();

    // 获取当前散列表的大小
    int GetSize() const;

    // 获取当前散列表的容量
    int GetCapacity() const;

    // 获取桶数
    int getBucketCount() const;

    // 获取第 i 个桶的元素数量
    int getBucketSize(int i) const;

    // 获取指定键的桶序号
    int getBucket(const K& k) const;

    // 查找指定键的节点，并返回桶序号
    DbListNode<E, K, V>* findPos(const K& key, int& bucket) const;
};

#endif // EXPANDABLELINKEDHASHTABLE_H

#include "ExpandableLinkedHashTable.h"
#include <iostream>
#include <cmath>

template <typename E, typename K, typename V>
ExpandableLinkedHashTable<E, K, V>::ExpandableLinkedHashTable(int initialSize, double maxLoadFactor)
    : size(0), capacity(initialSize), maxLoadFactor(maxLoadFactor) {
    // 初始化桶数组
    table = DynamicArray<DbLinkedList<E, K, V>*,K,V>(capacity);
    for (int i = 0; i < capacity; ++i) {
        table[i] = nullptr;
    }
}

template <typename E, typename K, typename V>
ExpandableLinkedHashTable<E, K, V>::~ExpandableLinkedHashTable() {
    // 销毁所有桶中的元素
    for (int i = 0; i < capacity; ++i) {
        if (table[i]) {
            delete table[i];  // 删除桶中的双链表
        }
    }
}

template <typename E, typename K, typename V>
int ExpandableLinkedHashTable<E, K, V>::hash(const K& key) const {
    // 简单的哈希函数
    return std::hash<K>{}(key) % capacity;
}

template <typename E, typename K, typename V>
bool ExpandableLinkedHashTable<E, K, V>::Insert(const E& e) {
    int index = hash(e.getKey());  // 获取桶的位置

    // 检查该桶是否为空
    if (!table[index]) {
        table[index] = new DbLinkedList<E, K, V>();
    }

    // 插入元素
    bool inserted = table[index]->insertAtTail(e);
    if (inserted) {
        ++size;
        if (static_cast<double>(size) / capacity > maxLoadFactor) {
            resizeTable();  // 需要扩容
        }
    }

    return inserted;
}

template <typename E, typename K, typename V>
bool ExpandableLinkedHashTable<E, K, V>::Search(const K& key) const {
    int index = hash(key);  // 获取桶的位置
    if (table[index]) {
        return table[index]->Search(key) != nullptr;
    }
    return false;
}

template <typename E, typename K, typename V>
int ExpandableLinkedHashTable<E, K, V>::Remove(const K& key, E& e) {
    int index = hash(key);  // 获取桶的位置
    if (table[index]) {
        int count = table[index]->Remove(key, e);  // 删除元素
        if (count > 0) {
            --size;
        }
        return count;  // 返回删除的元素个数
    }
    return 0;  // 没有找到元素
}
template <typename E, typename K, typename V>
void ExpandableLinkedHashTable<E, K, V>::resizeTable() {
    int newCapacity = capacity * 2;
    DynamicArray<DbLinkedList<E, K, V>*,K,V> newTable(newCapacity);

    // 初始化新的桶数组
    for (int i = 0; i < newCapacity; ++i) {
        newTable[i] = nullptr;
    }

    // 重新哈希所有元素并迁移到新的桶数组
    for (int i = 0; i < capacity; ++i) {
        if (table[i]) {
            auto it = table[i]->begin();
            while (it != table[i]->end()) {
                DbListNode<E, K, V>* node = &(*it);
                int newIndex = std::hash<K>{}(node->getKey()) % newCapacity;

                if (!newTable[newIndex]) {
                    newTable[newIndex] = new DbLinkedList<E, K, V>();
                }
                newTable[newIndex]->insertAtTail(node->getData(), node->getKey(), node->getValue());
                ++it;
            }
        }
    }

    // 删除旧的桶数组并替换为新的
    table = std::move(newTable);
    capacity = newCapacity;
}

template <typename E, typename K, typename V>
void ExpandableLinkedHashTable<E, K, V>::Clear() {
    // 清空每个桶中的元素
    for (int i = 0; i < capacity; ++i) {
        if (table[i]) {
            table[i]->clear();  // 调用每个桶的清空方法
        }
    }
    size = 0;  // 重置大小为0
}

template <typename E, typename K, typename V>
int ExpandableLinkedHashTable<E, K, V>::GetSize() const {
    return size;
}

template <typename E, typename K, typename V>
int ExpandableLinkedHashTable<E, K, V>::GetCapacity() const {
    return capacity;
}//获取桶数

template <typename E, typename K, typename V>
int ExpandableLinkedHashTable<E, K, V>::getBucketSize(int i) const {
    if (i < 0 || i >= capacity) {
        return -1;  // 处理无效的桶序号
    }
    return (table[i] ? table[i]->getSize() : 0);  // 返回第 i 个桶中的元素数量
}

template <typename E, typename K, typename V>
int ExpandableLinkedHashTable<E, K, V>::getBucket(const K& k) const {
    return hash(k) % capacity;  // 返回给定键所在的桶序号
}

template <typename E, typename K, typename V>
DbListNode<E, K, V>* ExpandableLinkedHashTable<E, K, V>::findPos(const K& key, int& bucket) const {
    // 计算键对应的桶序号
    bucket = hash(key);

    if (table[bucket]) {
        // 在桶中查找键
        DbListNode<E, K, V>* node = table[bucket]->Search(key);
        if (node) {
            // 如果找到了该键，返回该节点
            return node;
        }
    }

    // 如果没有找到，返回 nullptr
    return nullptr;
}
