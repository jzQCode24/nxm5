// wusgraph.cpp
#include "WUSGraph.h"
#include <stdexcept>

template <typename T,typename Object, typename Weight>
WUSGraph<T,Object, Weight>::WUSGraph(int v) : numEdges(0) {
    vertexMap = HashMap<Object, int>(v, 0.7);
    adjacencyLists = DynamicArray<DbLinkedList<T>>(v);
    vertices = DynamicArray<Object>(v);
}

template <typename T,typename Object, typename Weight>
WUSGraph<T,Object, Weight>::~WUSGraph() {
    // 析构函数不需要手动释放资源，因为会自动调用clear
}

template <typename T,typename Object, typename Weight>
bool WUSGraph<T,Object, Weight>::isVertex(const Object& v) {
    return vertexMap.containsKey(v);
}

template <typename T,typename Object, typename Weight>
void WUSGraph<T,Object, Weight>::addVertex(const Object& v) {
    if (!isVertex(v)) {
        int index = vertices.getSize();
        vertices[index] = v;
        vertexMap.put(v, index);
        adjacencyLists.resizeList();
        adjacencyLists[index] = DbLinkedList<T>();
    }
}

template <typename T,typename Object, typename Weight>
void WUSGraph<T,Object, Weight>::removeVertex(const Object& v) {
    if (!isVertex(v)) {
        throw std::invalid_argument("Vertex not found");
    }

    int index = vertexMap.get(v); // 获取顶点v的索引
    DbLinkedList<T>& adjacencyList = adjacencyLists[index]; // 获取顶点v的邻接表

    // 遍历邻接表，对于每个邻接顶点，删除与v相关的边
    for (auto& edge : adjacencyList) {
        if (edge.peer) {
            int uIndex = vertexMap.get(edge.vertex);
            DbLinkedList<T>& uAdjacencyList = adjacencyLists[uIndex];
            auto it = std::find_if(uAdjacencyList.begin(), uAdjacencyList.end(), [v](const T& e) { return e.vertex == v; });
            if (it != uAdjacencyList.end()) {
                uAdjacencyList.Remove(*it);
            }
            edge.peer = nullptr; // 断开伙伴指针
        }
    }

    // 删除顶点v的所有边
    adjacencyList.Clear();

    // 从顶点数组和映射中删除顶点v
    vertices.remove(index);
    for (int i = index; i < vertices.getSize(); ++i) {
        int mappedIndex = vertexMap.get(vertices[i]);
        if (mappedIndex > index) {
            vertexMap.put(vertices[i], mappedIndex - 1);
        }
    }
    vertexMap.remove(v);

    // 删除顶点v的邻接表
    adjacencyLists.remove(index);

    // 更新边的数量
    numEdges -= adjacencyList.getSize();
}

template <typename T,typename Object, typename Weight>
int WUSGraph<T,Object, Weight>::Degree(const Object& v) {
    if (!isVertex(v)) {
        throw std::invalid_argument("Vertex not found");
    }
    return adjacencyLists[vertexMap.get(v)].getSize();
}

template <typename T,typename Object, typename Weight>
DbLinkedList<T>& WUSGraph<T,Object, Weight>::getNeighbors(const Object& v) {
    if (!isVertex(v)) {
        throw std::invalid_argument("Vertex not found");
    }
    return adjacencyLists[vertexMap.get(v)];
}

template <typename T,typename Object, typename Weight>
void WUSGraph<T,Object, Weight>::addEdge(const Object& u, const Object& v, Weight w) {
    if (!isVertex(u) || !isVertex(v)) {
        throw std::invalid_argument("Both vertices must be in the graph");
    }
    int uIndex = vertexMap.get(u);
    int vIndex = vertexMap.get(v);
    T edgeU(v, w);
    T edgeV(u, w, &edgeU); // 设置伙伴指针
    edgeU.peer = &edgeV;
    adjacencyLists[uIndex].insertAtTail(edgeU);
    adjacencyLists[vIndex].insertAtTail(edgeV);
    edgeWeights.insertAtTail(w);
    numEdges++;
}

template <typename T,typename Object, typename Weight>
void WUSGraph<T,Object, Weight>::removeEdge(const Object& u, const Object& v) {
    if (!isEdge(u, v)) {
        return;
    }
    Object temp = u;
    int uIndex = vertexMap.get(u);
    int vIndex = vertexMap.get(v);
    T toRemove(u, Weight()); // 初始化一个临时Edge对象，用于查找

    // 修改此处的lambda表达式捕获列表，按值捕获temp和v
    auto it = std::find_if(adjacencyLists[vIndex].begin(), adjacencyLists[vIndex].end(),
                           [&toRemove, temp, v](const T& e) { return e.vertex == temp; });
    if (it!= adjacencyLists[vIndex].end()) {
        adjacencyLists[vIndex].Remove(*it);
        if (it->peer) {
            it->peer->peer = nullptr; // 清除伙伴指针
        }
    }
    toRemove.vertex = v; // 交换u和v

    // 修改此处的lambda表达式捕获列表，按值捕获toRemove和v
    auto uit = std::find_if(adjacencyLists[uIndex].begin(), adjacencyLists[uIndex].end(),
                            [&toRemove, v](const T& e) { return e.vertex == v; });
    if (uit!= adjacencyLists[uIndex].end()) {
        adjacencyLists[uIndex].Remove(*uit);
        if (uit->peer) {
            uit->peer->peer = nullptr; // 清除伙伴指针
        }
    }
    edgeWeights.removeFromTail();
    numEdges--;
}

template <typename T,typename Object, typename Weight>
bool WUSGraph<T,Object, Weight>::isEdge(const Object& u, const Object& v) {
    int uIndex = vertexMap.get(u);
    DbLinkedList<T>& list = adjacencyLists[uIndex];
    for (auto& edge : list) {
        if (edge.vertex == v) {
            return true;
        }
    }
    return false;
}

template <typename T,typename Object, typename Weight>
Weight WUSGraph<T,Object, Weight>::getWeight(const Object& u, const Object& v) {
    if (!isEdge(u, v)) {
        throw std::invalid_argument("Edge not found");
    }
    int uIndex = vertexMap.get(u);
    DbLinkedList<T>& list = adjacencyLists[uIndex];
    for (auto& edge : list) {
        if (edge.vertex == v) {
            return edge.weight;
        }
    }
    return Weight(); // 返回Weight类型的默认值
}

template <typename T,typename Object, typename Weight>
int WUSGraph<T,Object, Weight>::vertexCount() {
    return vertices.getSize();
}

template <typename T,typename Object, typename Weight>
int WUSGraph<T,Object, Weight>::edgeCount() {
    return numEdges;
}

template <typename T,typename Object, typename Weight>
DynamicArray<Object>* WUSGraph<T,Object, Weight>::getVertices() {
    return &vertices;
}
