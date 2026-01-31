#pragma once
#include <QString>
#include <QColor>
#include <QVector>

class FuncTreeNode;
struct MindNode {
    QString text;
    QColor textColor = Qt::black;
    QColor  color = Qt::black;
    MindNode* parent = nullptr;
    QVector<MindNode*> children;
    FuncTreeNode* funcTreeNode;
};
