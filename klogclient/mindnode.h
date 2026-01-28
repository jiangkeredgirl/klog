#pragma once
#include <QString>
#include <QColor>
#include <QVector>

struct MindNode {
    QString text;
    QColor  color = Qt::black;

    MindNode* parent = nullptr;
    QVector<MindNode*> children;
};
