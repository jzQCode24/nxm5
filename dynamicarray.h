#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <stdexcept>

template <typename E>
class DynamicArray {
public:
    DynamicArray(int initialCapacity = 10);
    ~DynamicArray();
    E& operator[](int index);
    void add(E element);
    void resizeList();
    void clear();
    int getSize() const;

private:
    struct Node {
        E data;
        Node* next;

        Node(E data, Node* next = nullptr) : data(data), next(next) {}
    };

    Node* head;
    int size;
    int capacity;

    void resize();
};

#endif // DYNAMICARRAY_H
