// wusgraph.h
#ifndef WUSGRAPH_H
#define WUSGRAPH_H

#include "DbLinkedList.h"
#include "HashMap.h"
#include <utility> // 包含std::pair
#include <algorithm>

template <typename Object, typename Weight>
struct Edge {
    Object vertex;
    Weight weight;
    Edge* peer; // 伙伴指针，指向对应的边

    Edge(Object v, Weight w, Edge* p = nullptr) : vertex(v), weight(w), peer(p) {}
};

template <typename T,typename Object, typename Weight>
class WUSGraph {
private:
    HashMap<Object, int> vertexMap; // 顶点映射
    DynamicArray<T> adjacencyLists; // 邻接表
    DynamicArray<Object> vertices; // 顶点数组
    DynamicArray<Weight> edgeWeights; // 边的权重数组
    int numEdges; // 边的数量

public:
    WUSGraph(int v);
    ~WUSGraph();
    bool isVertex(const Object& v); // 检查是否为顶点
    void addVertex(const Object& v); // 添加顶点
    void removeVertex(const Object& v); // 删除顶点
    int Degree(const Object& v); // 获取顶点的度
    DbLinkedList<T>& getNeighbors(const Object& v); // 获取邻接顶点
    void addEdge(const Object& u, const Object& v, Weight w); // 添加边
    void removeEdge(const Object& u, const Object& v); // 删除边
    bool isEdge(const Object& u, const Object& v); // 检查是否为边
    Weight getWeight(const Object& u, const Object& v); // 获取边的权重
    int vertexCount(); // 获取顶点数
    int edgeCount(); // 获取边数
    DynamicArray<Object>* getVertices(); // 获取所有顶点
};

#endif // WUSGRAPH_H
