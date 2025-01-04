#include <QCoreApplication>
#include "GraphClient.h"
#include <QFile>
#include <QTextStream>
#include <stdexcept>

int main(int argc, char *argv[]) {
    QCoreApplication app(argc, argv);

    QFile file("D:\\qqtt\\nxm5\\test.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Failed to open file";
        return -1;
    }

    QTextStream in(&file);
    int numVertices, numEdges;
    in >> numVertices >> numEdges;

    // 创建图对象，假设 Edge 结构已经定义好
    WUSGraph<Edge<int, double>, int, double> graph(numVertices); // 使用正确的三个模板参数

    try {
        CreateGraphFromFile("D:\\qqtt\\nxm5\\test.txt", graph); // 假设文件位于指定路径
        qDebug() << "Graph created successfully.";
    } catch (const std::exception& e) {
        qCritical() << "Error:" << e.what();
    }

    file.close();
    return app.exec();
}
