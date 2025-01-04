#ifndef EXPANDABLELINKEDHASHTABLE_H
#define EXPANDABLELINKEDHASHTABLE_H


#include "DynamicArray.h"
#include <utility> // 包含std::pair
#include "DbLinkedList.h"

template <typename K, typename V>
class ExpandableLinkedHashTable {
private:
    DynamicArray<DbLinkedList<std::pair<K, V>>> buckets; // 使用DynamicArray存储链表
    int size;
    double maxLoadFactor;

    void resize(); // 调整散列表大小的函数
    int getBucketIndex(const K& key) const; // 获取键对应的桶索引

public:
    ExpandableLinkedHashTable(int initialSize = 16, double maxLoadFactor = 0.7); // 默认构造函数
    ~ExpandableLinkedHashTable();
    DbListNode<std::pair<K, V>>* findPos(const K& key, int &bucket) const; // 获取散列表中指定键 key 映射到的双向链表结点
    bool Search(const K& key) const; // 在散列表中查找
    bool Insert(const std::pair<K, V>& e); // 将元素 e 插入到散列表中
    int Remove(const K& key, V& e); // 将给定值从散列表中删除
    void resizeTable(); // 散列表会自动增加桶的数量以保持负载因子低于 maxLoadFactor
    void Clear(); // 移除所有元素（已销毁），并保留大小为 0 的散列表
    int getCapacity() const; // 获取散列表的容量
    int getSize() const; // 获取散列表中键值对的数量
    int getBucket(const K& k) const; // 返回 k 对应的桶序号
    int getBucketSize(int i) const; // 返回第 i 个桶的元素数
};

#endif // EXPANDABLELINKEDHASHTABLE_H
