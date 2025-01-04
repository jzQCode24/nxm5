#include "DbListNode.h"

template <typename E>
DbListNode<E>::DbListNode(const E& data) : data(data), prev(nullptr), next(nullptr) {}

template <typename E>
E DbListNode<E>::getData() const {
    return data;
}

template <typename E>
void DbListNode<E>::setData(const E& data) {
    this->data = data;
}

template <typename E>
DbListNode<E>* DbListNode<E>::getPrev() const {
    return prev;
}

template <typename E>
void DbListNode<E>::setPrev(DbListNode* prev) {
    this->prev = prev;
}

template <typename E>
DbListNode<E>* DbListNode<E>::getNext() const {
    return next;
}

template <typename E>
void DbListNode<E>::setNext(DbListNode* next) {
    this->next = next;
}
