#ifndef DBLINKEDLIST_H
#define DBLINKEDLIST_H

#include "DbListNode.h"

template <typename E, typename K, typename V>
class DbLinkedList {
private:
    DbListNode<E, K, V>* head;
    DbListNode<E, K, V>* tail;
    int size;

public:
    DbLinkedList();
    ~DbLinkedList();

    bool isEmpty() const;
    int getSize() const;

    void insertAtHead(const E& data, const K& key, const V& value);
    void insertAtTail(const E& data, const K& key, const V& value);
    void Insert(const K& key, const E& data, const K& newKey, const V& newValue);
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
