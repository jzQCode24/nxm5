#include "dynamicarray.h"

template <typename E, typename K, typename V>
DynamicArray<E, K, V>::DynamicArray(int initialCapacity)
    : size(0), capacity(initialCapacity) {
    // 为数组分配内存
    array = new DbLinkedList<E, K, V>*[capacity];

    // 初始化所有指针为 nullptr
    for (int i = 0; i < capacity; ++i) {
        array[i] = nullptr;
    }
}

template <typename E, typename K, typename V>
DynamicArray<E, K, V>::~DynamicArray() {
    // 删除每个链表
    for (int i = 0; i < capacity; ++i) {
        if (array[i]) {
            delete array[i];  // 删除链表
        }
    }
    delete[] array;  // 删除数组本身
}

template <typename E, typename K, typename V>
int DynamicArray<E, K, V>::getSize() const {
    return size;
}

template <typename E, typename K, typename V>
DbLinkedList<E, K, V>* DynamicArray<E, K, V>::operator[](int i) {
    if (i < 0 || i >= capacity) {
        throw std::out_of_range("Index out of range");
    }
    return array[i];
}

template <typename E, typename K, typename V>
void DynamicArray<E, K, V>::add(const E& data, const K& key, const V& value) {
    // 计算桶索引
    int index = key % capacity;  // 假设使用简单的取模哈希方法

    // 如果该位置没有链表，创建一个新的链表
    if (!array[index]) {
        array[index] = new DbLinkedList<E, K, V>();
    }

    // 将元素添加到对应的链表中
    array[index]->addNode(data, key, value);
    ++size;
}

template <typename E, typename K, typename V>
void DynamicArray<E, K, V>::clear() {
    for (int i = 0; i < capacity; ++i) {
        if (array[i]) {
            array[i]->clear();  // 清空链表
            delete array[i];  // 删除链表
            array[i] = nullptr;  // 置为空
        }
    }
    size = 0;
}
