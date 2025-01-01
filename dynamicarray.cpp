#include "dynamicarray.h"
#include <iostream>

// 构造函数
template <typename E>
DynamicArray<E>::DynamicArray(int initialCapacity)
    : head(nullptr), tail(nullptr), size(0), capacity(initialCapacity) {
    array = new Node<E>*[capacity];  // 分配加速访问的数组
    for (int i = 0; i < capacity; ++i) {
        array[i] = nullptr;  // 初始化为空
    }
}

// 析构函数
template <typename E>
DynamicArray<E>::~DynamicArray() {
    clear();
    delete[] array;
}

// 获取当前链表大小
template <typename E>
int DynamicArray<E>::getSize() const {
    return size;
}

// 向链表末尾添加一个元素
template <typename E>
void DynamicArray<E>::add(const E& element) {
    Node<E>* newNode = new Node<E>(element);

    if (tail) {
        tail->next = newNode;  // 如果链表非空，将新节点连接到尾节点
    } else {
        head = newNode;  // 如果链表为空，将新节点设置为头节点
    }

    tail = newNode;  // 将尾节点更新为新节点
    ++size;

    // 如果链表的大小超过当前容量，进行扩容
    if (size > capacity) {
        resizeList();
    }

    // 将新节点存储到加速访问的数组中
    array[size - 1] = newNode;
}

// 扩容（将容量翻倍）
template <typename E>
void DynamicArray<E>::resizeList() {
    capacity *= 2;  // 容量翻倍
    Node<E>** newArray = new Node<E>*[capacity];  // 创建一个新的数组

    // 将原来的链表节点复制到新的数组中
    for (int i = 0; i < size; ++i) {
        newArray[i] = array[i];
    }

    // 删除旧的数组
    delete[] array;
    array = newArray;
}

// 访问指定位置的元素（带越界检查）
template <typename E>
E& DynamicArray<E>::operator[](int i) {
    if (i < 0 || i >= size) {
        throw std::out_of_range("Index out of bounds");  // 越界检查
    }
    return array[i]->data;  // 通过数组直接访问链表节点
}

// 清空链表
template <typename E>
void DynamicArray<E>::clear() {
    Node<E>* current = head;
    while (current) {
        Node<E>* temp = current;
        current = current->next;
        delete temp;  // 删除节点
    }
    head = tail = nullptr;
    size = 0;
}
