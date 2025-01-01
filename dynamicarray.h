#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <QDebug>

// 模板类：动态数组
template <typename E>
class DynamicArray {
private:
    E *array;
    int capacity;
    int size;

    // 内部方法：扩容
    void resizeList();

public:
    // 构造函数
    DynamicArray(int initialCapacity = 10);
    // 析构函数
    ~DynamicArray();

    // 获取元素数量
    int getSize() const;

    // 查找元素
    int search(const E &key) const;

    // 访问元素
    bool getElement(int i, E &outElement) const;

    // 访问元素（无越界检查）
    E& operator[](int i);

    // 添加元素
    bool add(const E &element);

    // 清空数组
    void clear();

    // 输出元素
    void print() const;
};

#endif // DYNAMICARRAY_H
