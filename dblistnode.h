#ifndef DBLISTNODE_H
#define DBLISTNODE_H

template <typename E, typename K, typename V>
class DbListNode {
private:
    E data;
    K key;
    V value;
    DbListNode* prev;
    DbListNode* next;

public:
    DbListNode(const E& data, const K& key, const V& value);

    // Getter 和 Setter
    E getData() const;
    void setData(const E& data);

    K getKey() const;
    void setKey(const K& key);

    V getValue() const;
    void setValue(const V& value);

    DbListNode* getPrev() const;
    void setPrev(DbListNode* prev);

    DbListNode* getNext() const;
    void setNext(DbListNode* next);
};


#endif // DBLISTNODE_H
