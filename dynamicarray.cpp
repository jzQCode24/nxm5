#include "dynamicarray.h"

template <typename E>
DynamicArray<E>::DynamicArray(int initialCapacity) : head(new Node(E())), size(0), capacity(initialCapacity) {}

template <typename E>
DynamicArray<E>::~DynamicArray() {
    clear();
    delete head;
}

template <typename E>
E& DynamicArray<E>::operator[](int index) {
    if (index < 0 || index >= size) {
        throw std::out_of_range("Index out of range");
    }
    Node* current = head->next; // Skip dummy head
    for (int i = 0; i < index; ++i) {
        current = current->next;
    }
    return current->data;
}

template <typename E>
void DynamicArray<E>::add(E element) {
    if (size >= capacity) {
        resizeList();
    }
    Node* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = new Node(element);
    size++;
}

template <typename E>
void DynamicArray<E>::resizeList() {
    if (size >= capacity) {
        resize();
    }
}

template <typename E>
void DynamicArray<E>::clear() {
    Node* current = head;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
    head = new Node(E()); // Reset with a dummy head
    size = 0;
}

template <typename E>
int DynamicArray<E>::getSize() const {
    return size;
}

template <typename E>
void DynamicArray<E>::resize() {
    int newCapacity = capacity * 2;
    Node* newHead = new Node(E());
    Node* current = head->next; // Skip dummy head
    Node* iterator = newHead;

    while (current != nullptr) {
        iterator->next = new Node(current->data);
        iterator = iterator->next;
        current = current->next;
    }

    Node* oldHead = head;
    head = newHead;
    capacity = newCapacity;

    // Delete old nodes
    current = oldHead;
    while (current != nullptr) {
        Node* next = current->next;
        delete current;
        current = next;
    }
}
