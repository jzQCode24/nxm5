#include "DbLinkedList.h"

template <typename E, typename K, typename V>
DbLinkedList<E, K, V>::DbLinkedList() : head(nullptr), tail(nullptr), size(0) {}

template <typename E, typename K, typename V>
DbLinkedList<E, K, V>::~DbLinkedList() {
    clear();
}

template <typename E, typename K, typename V>
bool DbLinkedList<E, K, V>::isEmpty() const {
    return size == 0;
}

template <typename E, typename K, typename V>
int DbLinkedList<E, K, V>::getSize() const {
    return size;
}

template <typename E, typename K, typename V>
void DbLinkedList<E, K, V>::insertAtHead(const E& data, const K& key, const V& value) {
    DbListNode<E, K, V>* newNode = new DbListNode<E, K, V>(data, key, value);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->setNext(head);
        head->setPrev(newNode);
        head = newNode;
    }
    ++size;
}

template <typename E, typename K, typename V>
void DbLinkedList<E, K, V>::insertAtTail(const E& data, const K& key, const V& value) {
    DbListNode<E, K, V>* newNode = new DbListNode<E, K, V>(data, key, value);
    if (isEmpty()) {
        head = tail = newNode;
    } else {
        newNode->setPrev(tail);
        tail->setNext(newNode);
        tail = newNode;
    }
    ++size;
}


template <typename E, typename K, typename V>
void DbLinkedList<E, K, V>::Insert(const K& key, const E& data, const K& newKey, const V& newValue) {

    DbListNode<E, K, V>* current = head;
    while (current != nullptr) {
        if (current->getKey() == key) {

            DbListNode<E, K, V>* newNode = new DbListNode<E, K, V>(data, newKey, newValue);

            DbListNode<E, K, V>* nextNode = current->getNext();

            current->setNext(newNode);
            newNode->setPrev(current);

            if (nextNode != nullptr) {
                nextNode->setPrev(newNode);
                newNode->setNext(nextNode);
            } else {
                tail = newNode;
            }

            ++size;
            return;
        }
        current = current->getNext();
    }

}
template <typename E, typename K, typename V>
void DbLinkedList<E, K, V>::removeFromHead() {
    if (isEmpty()) {
        return;
    }
    DbListNode<E, K, V>* temp = head;
    head = head->getNext();
    if (head != nullptr) {
        head->setPrev(nullptr);
    } else {
        tail = nullptr;
    }
    delete temp;
    --size;
}

template <typename E, typename K, typename V>
void DbLinkedList<E, K, V>::removeFromTail() {
    if (isEmpty()) {
        return;
    }
    DbListNode<E, K, V>* temp = tail;
    tail = tail->getPrev();
    if (tail != nullptr) {
        tail->setNext(nullptr);
    } else {
        head = nullptr;
    }
    delete temp;
    --size;
}

template <typename E, typename K, typename V>
DbListNode<E, K, V>* DbLinkedList<E, K, V>::Search(const K& key) {
    DbListNode<E, K, V>* current = head;
    while (current != nullptr) {
        if (current->getKey() == key) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

template <typename E, typename K, typename V>
void DbLinkedList<E, K, V>::Remove(const K& key) {
    DbListNode<E, K, V>* nodeToRemove = findByKey(key);
    if (nodeToRemove != nullptr) {
        if (nodeToRemove == head) {
            removeFromHead();
        } else if (nodeToRemove == tail) {
            removeFromTail();
        } else {
            DbListNode<E, K, V>* prevNode = nodeToRemove->getPrev();
            DbListNode<E, K, V>* nextNode = nodeToRemove->getNext();
            prevNode->setNext(nextNode);
            if (nextNode != nullptr) {
                nextNode->setPrev(prevNode);
            }
            delete nodeToRemove;
            --size;
        }
    }
}

template <typename E, typename K, typename V>
void DbLinkedList<E, K, V>::clear() {
    while (!isEmpty()) {
        removeFromHead();
    }
}

template <typename E, typename K, typename V>
DbLinkedList<E, K, V>::iterator::iterator(DbListNode<E, K, V>* startNode)
    : current(startNode) {}

template <typename E, typename K, typename V>
E& DbLinkedList<E, K, V>::iterator::operator*() {
    return current->getData();
}

template <typename E, typename K, typename V>
typename DbLinkedList<E, K, V>::iterator& DbLinkedList<E, K, V>::iterator::operator++() {
    current = current->getNext();
    return *this;
}

template <typename E, typename K, typename V>
bool DbLinkedList<E, K, V>::iterator::operator!=(const iterator& other) {
    return current != other.current;
}

template <typename E, typename K, typename V>
typename DbLinkedList<E, K, V>::iterator DbLinkedList<E, K, V>::begin() {
    return iterator(head);
}

template <typename E, typename K, typename V>
typename DbLinkedList<E, K, V>::iterator DbLinkedList<E, K, V>::end() {
    return iterator(nullptr);
}
