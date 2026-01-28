#pragma once
#include <QGraphicsRectItem>
#include <QPainter>
#include "MindNode.h"

class MindNodeItem : public QGraphicsRectItem {
public:
    explicit MindNodeItem(MindNode* node)
        : data(node)
    {
        setRect(0, 0, 140, 40);
        setFlags(ItemIsMovable | ItemIsSelectable);
    }

    MindNode* node() const { return data; }

protected:
    void paint(QPainter* painter,
               const QStyleOptionGraphicsItem*,
               QWidget*) override
    {
        painter->setBrush(isSelected() ? QColor("#E3F2FD") : Qt::white);
        painter->setPen(Qt::black);
        painter->drawRoundedRect(rect(), 6, 6);

        painter->setPen(data->color);
        painter->drawText(rect(), Qt::AlignCenter, data->text);
    }

private:
    MindNode* data;
};
