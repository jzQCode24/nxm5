#ifndef NODE_H
#define NODE_H

template <typename E, typename K, typename V>
class Node {
public:
    E data;  // 存储数据元素
    K key;   // 存储关键字
    V value; // 存储关键字对应的值
    Node* next;  // 指向下一个节点

    // 构造函数
    Node(const E& data, const K& key, const V& value)
        : data(data), key(key), value(value), next(nullptr) {}
};

#endif // NODE_H
