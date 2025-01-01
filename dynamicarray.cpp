#include "DynamicArray.h"
#include <QDebug>

// 构造函数
template <typename E>
DynamicArray<E>::DynamicArray(int initialCapacity) {
    capacity = initialCapacity;
    size = 0;
    array = new E[capacity];
}

// 析构函数
template <typename E>
DynamicArray<E>::~DynamicArray() {
    delete[] array;
}

// 获取数组大小
template <typename E>
int DynamicArray<E>::getSize() const {
    return size;
}

// 查找元素（线性查找）
template <typename E>
int DynamicArray<E>::search(const E &key) const {
    for (int i = 0; i < size; ++i) {
        if (array[i] == key)
            return i;
    }
    return -1;  // 找不到返回-1
}

// 扩容方法
template <typename E>
void DynamicArray<E>::resizeList() {
    capacity *= 2;
    E *newArray = new E[capacity];
    for (int i = 0; i < size; ++i) {
        newArray[i] = array[i];
    }
    delete[] array;
    array = newArray;
}

// 获取元素（带越界检查）
template <typename E>
bool DynamicArray<E>::getElement(int i, E &outElement) const {
    if (i < 0 || i >= size) {
        return false;  // 越界
    }
    outElement = array[i];
    return true;  // 成功
}

// 访问元素（无越界检查）
template <typename E>
E& DynamicArray<E>::operator[](int i) {
    return array[i];
}

// 添加元素
template <typename E>
bool DynamicArray<E>::add(const E &element) {
    if (size == capacity) {
        resizeList();
    }
    array[size++] = element;
    return true;
}

// 清空数组
template <typename E>
void DynamicArray<E>::clear() {
    size = 0;
}

// 输出数组内容
template <typename E>
void DynamicArray<E>::print() const {
    for (int i = 0; i < size; ++i) {
        qDebug() << array[i];
    }
}

// 显式实例化模板类
// template class DynamicArray<int>;
// template class DynamicArray<double>;
// template class DynamicArray<QString>;
