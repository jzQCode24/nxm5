#include "DbLinkedList.h"

template <typename E>
DbLinkedList<E>::DbLinkedList() : head(nullptr), tail(nullptr), size(0) {}

template <typename E>
DbLinkedList<E>::~DbLinkedList() {
    Clear();
}

template <typename E>
bool DbLinkedList<E>::isEmpty() const {
    return size == 0;
}

template <typename E>
int DbLinkedList<E>::getSize() const {
    return size;
}

template <typename E>
void DbLinkedList<E>::insertAtHead(const E& data) {
    DbListNode<E>* newNode = new DbListNode<E>(data);
    if (head == nullptr) {
        head = tail = newNode;
    } else {
        newNode->setNext(head);
        head->setPrev(newNode);
        head = newNode;
    }
    size++;
}

template <typename E>
void DbLinkedList<E>::insertAtTail(const E& data) {
    DbListNode<E>* newNode = new DbListNode<E>(data);
    if (tail == nullptr) {
        head = tail = newNode;
    } else {
        tail->setNext(newNode);
        newNode->setPrev(tail);
        tail = newNode;
    }
    size++;
}

template <typename E>
void DbLinkedList<E>::removeFromHead() {
    if (head != nullptr) {
        DbListNode<E>* temp = head;
        head = head->getNext();
        if (head != nullptr) {
            head->setPrev(nullptr);
        } else {
            tail = nullptr;
        }
        delete temp;
        size--;
    }
}

template <typename E>
void DbLinkedList<E>::removeFromTail() {
    if (tail != nullptr) {
        DbListNode<E>* temp = tail;
        tail = tail->getPrev();
        if (tail != nullptr) {
            tail->setNext(nullptr);
        } else {
            head = nullptr;
        }
        delete temp;
        size--;
    }
}

template <typename E>
DbListNode<E>* DbLinkedList<E>::Search(const E& data) {
    DbListNode<E>* current = head;
    while (current != nullptr) {
        if (current->getData() == data) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

template <typename E>
void DbLinkedList<E>::Remove(const E& data) {
    DbListNode<E>* nodeToRemove = Search(data);
    if (nodeToRemove != nullptr) {
        DbListNode<E>* prevNode = nodeToRemove->getPrev();
        DbListNode<E>* nextNode = nodeToRemove->getNext();
        if (prevNode != nullptr) {
            prevNode->setNext(nextNode);
        } else {
            head = nextNode;
        }
        if (nextNode != nullptr) {
            nextNode->setPrev(prevNode);
        } else {
            tail = prevNode;
        }
        delete nodeToRemove;
        size--;
    }
}

template <typename E>
void DbLinkedList<E>::Clear() {
    while (head != nullptr) {
        DbListNode<E>* temp = head;
        head = head->getNext();
        delete temp;
    }
    tail = nullptr;
    size = 0;
}
