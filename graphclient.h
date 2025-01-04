// GraphClient.h
#ifndef GRAPHCLIENT_H
#define GRAPHCLIENT_H

#include "WUSGraph.h"
#include <QString>

// 声明创建图的函数
template <typename T,typename Object, typename Weight>
void CreateGraphFromFile(const QString& filepath, WUSGraph<T,Object, Weight>& graph);

#endif // GRAPHCLIENT_H
