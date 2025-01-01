#ifndef DBLISTNODE_H
#define DBLISTNODE_H

template <typename E, typename K, typename V>
class DbListNode {
private:
    E data;            // 数据元素
    K key;             // 关键字
    V value;           // 关键字对应的值
    DbListNode* prev;  // 前驱节点
    DbListNode* next;  // 后继节点

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
