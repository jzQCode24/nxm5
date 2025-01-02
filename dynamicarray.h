#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "dblinkedlist.h"  // 引入双链表的头文件
#include <stdexcept>  // 异常处理

template <typename E, typename K, typename V>
class DynamicArray {
private:
    DbLinkedList<E, K, V>** array;  // 用于存储双链表指针的数组
    int size=0;  // 当前元素个数
    int capacity=10;  // 当前数组的容量

    // 扩容
    void resizeList();

public:
    // 构造函数
    DynamicArray(int initialCapacity = 10);

    // 析构函数
    ~DynamicArray();

    // 获取当前元素个数
    int getSize() const;

    // 向链表末尾添加一个元素
    void add(const E& data, const K& key, const V& value);

    // 访问指定位置的元素（带越界检查）
    DbLinkedList<E, K, V>* operator[](int i);  // 访问的是链表对象指针

    // 清空链表
    void clear();
};

#endif // DYNAMICARRAY_H
