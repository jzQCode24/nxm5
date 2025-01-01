#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include "singlenode.h"

template <typename E>
class DynamicArray {
private:
    Node<E>* head;  // 链表的头指针
    Node<E>* tail;  // 链表的尾指针
    Node<E>** array;  // 用于加速随机访问的数组
    int size;  // 当前数组的大小（链表长度）
    int capacity;  // 当前链表的容量（链表节点的数量）

public:
    // 构造函数
    DynamicArray(int initialCapacity = 10);

    // 析构函数
    ~DynamicArray();

    // 获取当前链表大小
    int getSize() const;

    // 向链表末尾添加一个元素
    void add(const E& element);

    // 访问指定位置的元素（带越界检查）
    E& operator[](int i);

    // 扩容（将容量翻倍）
    void resizeList();

    // 清空链表
    void clear();
};

#endif // DYNAMICARRAY_H
