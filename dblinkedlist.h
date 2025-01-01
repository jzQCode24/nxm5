#ifndef DBLINKEDLIST_H
#define DBLINKEDLIST_H

#include "DbListNode.h"  // 引入 DbListNode

template <typename E, typename K, typename V>
class DbLinkedList {
private:
    DbListNode<E, K, V>* head;  // 头节点
    DbListNode<E, K, V>* tail;  // 尾节点
    int size;                   // 链表大小

public:
    DbLinkedList();
    ~DbLinkedList();

    bool isEmpty() const;
    int getSize() const;

    void insertAtHead(const E& data, const K& key, const V& value);
    void insertAtTail(const E& data, const K& key, const V& value);
    void removeFromHead();
    void removeFromTail();

    DbListNode<E, K, V>* Search(const K& key);
    void Remove(const K& key);
    void clear();

    class iterator {
    private:
        DbListNode<E, K, V>* current;

    public:
        iterator(DbListNode<E, K, V>* startNode);

        E& operator*();
        iterator& operator++();
        bool operator!=(const iterator& other);
    };

    iterator begin();
    iterator end();
};


#endif // DBLINKEDLIST_H
