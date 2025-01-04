#ifndef DBLINKEDLIST_H
#define DBLINKEDLIST_H

#include "DbListNode.h"

template <typename E>
class DbLinkedList {
private:
    DbListNode<E>* head;
    DbListNode<E>* tail;
    int size;

public:
    DbLinkedList(); // 构造函数
    ~DbLinkedList(); // 析构函数
    bool isEmpty() const; // 判断是否为空
    int getSize() const; // 获取大小
    void insertAtHead(const E& data); // 在头部插入
    void insertAtTail(const E& data); // 在尾部插入
    void removeFromHead(); // 从头部移除
    void removeFromTail(); // 从尾部移除
    DbListNode<E>* Search(const E& data); // 搜索节点
    void Remove(const E& data); // 移除节点
    void Clear(); // 清空链表
};

#endif // DBLINKEDLIST_H
