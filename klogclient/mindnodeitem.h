
#pragma once
#include <QGraphicsItem>
#include "MindNode.h"

class MindNodeItem : public QGraphicsItem
{
public:
    explicit MindNodeItem(MindNode* model);

    QRectF boundingRect() const override;
    void paint(QPainter* painter,
        const QStyleOptionGraphicsItem*,
        QWidget*) override;

private:
    MindNode* m_model;
};

#include <QPainter>

inline MindNodeItem::MindNodeItem(MindNode* model)
    : m_model(model)
{
    setZValue(1); // 保证节点在连线之上
}

inline QRectF MindNodeItem::boundingRect() const
{
    return QRectF(-60, -25, 120, 50);
}

inline void MindNodeItem::paint(QPainter* p,
    const QStyleOptionGraphicsItem*,
    QWidget*)
{
    p->setRenderHint(QPainter::Antialiasing);

    QRectF r = boundingRect();

    p->setPen(QPen(QColor("#9CA3AF"), 1));
    p->setBrush(QColor("#F9FAFB"));
    p->drawRoundedRect(r, 8, 8);

    p->setPen(m_model->textColor);
    p->setFont(QFont("Segoe UI", 9));
    p->drawText(r, Qt::AlignCenter, m_model->text);
}
