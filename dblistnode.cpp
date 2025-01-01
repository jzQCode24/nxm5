#include "DbListNode.h"

// DbListNode 类的实现

template <typename E, typename K, typename V>
DbListNode<E, K, V>::DbListNode(const E& data, const K& key, const V& value)
    : data(data), key(key), value(value), prev(nullptr), next(nullptr) {}

template <typename E, typename K, typename V>
E DbListNode<E, K, V>::getData() const {
    return data;
}

template <typename E, typename K, typename V>
void DbListNode<E, K, V>::setData(const E& data) {
    this->data = data;
}

template <typename E, typename K, typename V>
K DbListNode<E, K, V>::getKey() const {
    return key;
}

template <typename E, typename K, typename V>
void DbListNode<E, K, V>::setKey(const K& key) {
    this->key = key;
}

template <typename E, typename K, typename V>
V DbListNode<E, K, V>::getValue() const {
    return value;
}

template <typename E, typename K, typename V>
void DbListNode<E, K, V>::setValue(const V& value) {
    this->value = value;
}

template <typename E, typename K, typename V>
DbListNode<E, K, V>* DbListNode<E, K, V>::getPrev() const {
    return prev;
}

template <typename E, typename K, typename V>
void DbListNode<E, K, V>::setPrev(DbListNode* prev) {
    this->prev = prev;
}

template <typename E, typename K, typename V>
DbListNode<E, K, V>* DbListNode<E, K, V>::getNext() const {
    return next;
}

template <typename E, typename K, typename V>
void DbListNode<E, K, V>::setNext(DbListNode* next) {
    this->next = next;
}
