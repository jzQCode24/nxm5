#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "singlenode.h"
#include <stdexcept>  // 异常处理

template <typename E, typename K, typename V>
class DynamicArray {
private:
    Node<E, K, V>* head;  // 链表的头指针
    Node<E, K, V>* tail;  // 链表的尾指针
    Node<E, K, V>** array;  // 用于加速随机访问的数组
    int size;  // 当前元素个数
    int capacity;  // 当前链表的容量

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
    E& operator[](int i);

    // 根据关键字获取值
    V getValueByKey(const K& key) const;

    // 清空链表
    void clear();
};

#endif // DYNAMICARRAY_H
