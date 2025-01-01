#include "dynamicarray.h"

// 构造函数
template <typename E, typename K, typename V>
DynamicArray<E, K, V>::DynamicArray(int initialCapacity)
    : size(0), capacity(initialCapacity), head(nullptr), tail(nullptr) {
    // 为加速访问分配一个新的数组
    array = new Node<E, K, V>*[capacity];
    for (int i = 0; i < capacity; ++i) {
        array[i] = nullptr;
    }
}

// 析构函数
template <typename E, typename K, typename V>
DynamicArray<E, K, V>::~DynamicArray() {
    clear();
    delete[] array;
}

// 获取当前元素个数
template <typename E, typename K, typename V>
int DynamicArray<E, K, V>::getSize() const {
    return size;
}

// 向链表末尾添加一个元素
template <typename E, typename K, typename V>
void DynamicArray<E, K, V>::add(const E& data, const K& key, const V& value) {
    Node<E, K, V>* newNode = new Node<E, K, V>(data, key, value);

    if (tail) {
        tail->next = newNode;  // 如果链表非空，将新节点连接到尾节点
    } else {
        head = newNode;  // 如果链表为空，将新节点设置为头节点
    }

    tail = newNode;  // 更新尾节点为新节点
    ++size;

    // 如果链表大小超过当前容量，进行扩容
    if (size > capacity) {
        resizeList();
    }

    // 将新节点存储到加速访问的数组中
    array[size - 1] = newNode;
}

// 扩容（将容量翻倍）
template <typename E, typename K, typename V>
void DynamicArray<E, K, V>::resizeList() {
    capacity *= 2;  // 容量翻倍
    Node<E, K, V>** newArray = new Node<E, K, V>*[capacity];  // 创建一个新的数组

    // 将原来的链表节点复制到新的数组中
    for (int i = 0; i < size; ++i) {
        newArray[i] = array[i];
    }

    // 删除旧的数组
    delete[] array;
    array = newArray;
}

// 访问指定位置的元素（带越界检查）
template <typename E, typename K, typename V>
E& DynamicArray<E, K, V>::operator[](int i) {
    if (i < 0 || i >= size) {
        throw std::out_of_range("Index out of bounds");  // 越界检查
    }
    return array[i]->data;  // 通过数组直接访问链表节点
}

// 根据关键字获取对应的值
template <typename E, typename K, typename V>
V DynamicArray<E, K, V>::getValueByKey(const K& key) const {
    Node<E, K, V>* current = head;
    while (current) {
        if (current->key == key) {
            return current->value;  // 找到匹配的关键字，返回对应的值
        }
        current = current->next;
    }
    throw std::invalid_argument("Key not found");  // 如果没有找到对应的关键字
}

// 清空链表
template <typename E, typename K, typename V>
void DynamicArray<E, K, V>::clear() {
    Node<E, K, V>* current = head;
    while (current) {
        Node<E, K, V>* temp = current;
        current = current->next;
        delete temp;  // 删除节点
    }
    head = tail = nullptr;
    size = 0;
}
