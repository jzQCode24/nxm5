#ifndef NODE_H
#define NODE_H

template <typename E>
class Node {
public:
    E data;  // 存储数据
    Node* next;  // 指向下一个节点

    // 构造函数
    Node(const E& data) : data(data), next(nullptr) {}
};

#endif // NODE_H
