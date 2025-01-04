#ifndef DBLISTNODE_H
#define DBLISTNODE_H

template <typename E>
class DbListNode {
public:
    E data;
    DbListNode* prev;
    DbListNode* next;

    DbListNode(const E& data); // 构造函数
    E getData() const;         // 获取数据
    void setData(const E& data); // 设置数据
    DbListNode* getPrev() const; // 获取前驱节点
    void setPrev(DbListNode* prev); // 设置前驱节点
    DbListNode* getNext() const; // 获取后继节点
    void setNext(DbListNode* next); // 设置后继节点
};

#endif // DBLISTNODE_H
