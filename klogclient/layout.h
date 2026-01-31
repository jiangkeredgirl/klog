#pragma once
#include <QGraphicsScene>
#include <QLineF>
#include <QtMath>
#include "MindNode.h"
#include "MindNodeItem.h"

// 精确：直线与矩形求交点
inline QPointF intersectRect(const QPointF& p1,
                             const QPointF& p2,
                             const QRectF& rect)
{
    QLineF line(p1, p2);
    QVector<QLineF> edges = {
        {rect.topLeft(), rect.topRight()},
        {rect.topRight(), rect.bottomRight()},
        {rect.bottomRight(), rect.bottomLeft()},
        {rect.bottomLeft(), rect.topLeft()}
    };

    for (auto& e : edges)
    {
        QPointF pt;
        if (line.intersects(e, &pt) == QLineF::BoundedIntersection)
            return pt;
    }
    return p2;
}

// 计算子树高度（防重叠）
inline int subtreeHeight(MindNode* node)
{
    if (node->children.isEmpty()) return 1;
    int h = 0;
    for (auto* c : node->children)
        h += subtreeHeight(c);
    return h;
}

// 布局函数
inline qreal layoutTree(MindNode* node,
                        QGraphicsScene* scene,
                        qreal x,
                        qreal yStart,
                        MindNodeItem* parentItem = nullptr)
{   
    const qreal xStep = 180;
    const qreal yStep = 80;

    int h = subtreeHeight(node);
    qreal y = yStart + (h * yStep) / 2.0;

    MindNodeItem* item = new MindNodeItem(node);
    item->setPos(x, y);
    scene->addItem(item);

    if (parentItem)
    {
        QRectF pr = parentItem->mapRectToScene(parentItem->boundingRect());
        QRectF cr = item->mapRectToScene(item->boundingRect());

        QPointF start = intersectRect(pr.center(), cr.center(), pr);
        QPointF end   = intersectRect(pr.center(), cr.center(), cr);

        QLineF line(start, end);
        scene->addLine(line, QPen(QColor("#9CA3AF"), 1));

        // 箭头
        double angle = std::atan2(line.dy(), line.dx());
        double size = 10;

        QPointF p1 = end - QPointF(size * std::cos(angle - M_PI/6),
                                   size * std::sin(angle - M_PI/6));
        QPointF p2 = end - QPointF(size * std::cos(angle + M_PI/6),
                                   size * std::sin(angle + M_PI/6));

        scene->addPolygon(QPolygonF() << end << p1 << p2,
                          QPen(Qt::NoPen),
                          QBrush(QColor("#9CA3AF")));
    }

    qreal currentY = yStart;
    for (auto* c : node->children)
    {
        int ch = subtreeHeight(c);
        layoutTree(c, scene, x + xStep, currentY, item);
        currentY += ch * yStep;
    }

    return y;
}
