// GraphClient.cpp
#include "GraphClient.h"
#include <QFile>
#include <QTextStream>
#include <stdexcept>
#include<QDebug>
template <typename T,typename Object, typename Weight>
void CreateGraphFromFile(const QString& filepath, WUSGraph<T,Object, Weight>& graph) {
    QFile file(filepath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("Failed to open file");
    }

    QTextStream in(&file);

    // 跳过第一行，因为它已经被main.cpp读取
    in.readLine();

    // 读取顶点信息
    for (int i = 0; i < graph.vertexCount(); ++i) {
        int index, x, y;
        in >> index >> x >> y;
        Object vertex = Object(index); // 假设Object类型可以直接由索引值构造
        graph.addVertex(vertex); // 添加顶点到图
        qDebug() << "Vertex" << index << "at" << "(" << x << "," << y << ")";
    }

    // 读取边信息
    for (int i = 0; i < graph.edgeCount(); ++i) {
        int u, v;
        in >> u >> v;
        Weight weight = static_cast<Weight>(1.0); // 假设权重为1.0，实际中可能需要计算
        graph.addEdge(Object(u), Object(v), weight); // 添加边到图
        qDebug() << "Edge between vertex" << u << "and vertex" << v;
    }

    file.close();
}
