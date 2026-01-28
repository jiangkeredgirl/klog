#pragma once
#include <QGraphicsLineItem>

class MindEdgeItem : public QGraphicsLineItem {
public:
    MindEdgeItem(QGraphicsItem* from, QGraphicsItem* to)
        : src(from), dst(to)
    {
        setPen(QPen(Qt::darkGray, 2));
        updateLine();
    }

    void updateLine() {
        setLine(QLineF(src->sceneBoundingRect().center(),
                       dst->sceneBoundingRect().center()));
    }

private:
    QGraphicsItem* src;
    QGraphicsItem* dst;
};
