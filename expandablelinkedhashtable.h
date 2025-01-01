#ifndef EXPANDABLELINKEDHASHTABLE_H
#define EXPANDABLELINKEDHASHTABLE_H

#include "dynamicarray.h"  // 使用你提供的动态数组实现
#include "dblinkedlist.h"  // 使用你提供的双链表实现

template <typename E, typename K, typename V>
class ExpandableLinkedHashTable {
private:
    DynamicArray table;  // 使用动态数组代替双链表的桶数组
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

    // 获取桶数
    int GetCapacity() const;


    // 获取第 i 个桶的元素数量
    int getBucketSize(int i) const;

    // 获取指定键的桶序号
    int getBucket(const K& k) const;

    // 查找指定键的节点，并返回桶序号
    DbListNode<E, K, V>* findPos(const K& key, int& bucket) const;
};

#endif // EXPANDABLELINKEDHASHTABLE_H

