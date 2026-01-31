#pragma once
#include <QString>
#include <QSvgGenerator>
#include <QPainter>
#include <QFileDialog>
#include <QGraphicsScene>


class MindMapExporter {
public:

#include <QSvgGenerator>
#include <QPainter>

    static void exportSceneToSvg(QGraphicsScene* scene, QWidget* parent)
    {
        QString file = QFileDialog::getSaveFileName(
            parent,
            "导出 SVG",
            "mindmap.svg",
            "SVG (*.svg)"
        );
        if (file.isEmpty())
            return;

        // 1️⃣ Scene 实际内容范围
        QRectF rect = scene->itemsBoundingRect();

        // 2️⃣ 预留边距（非常关键）
        constexpr qreal margin = 30;
        rect.adjust(-margin, -margin, margin, margin);

        // 3️⃣ SVG 生成器
        QSvgGenerator gen;
        gen.setFileName(file);
        gen.setTitle("klog mindmap");
        gen.setDescription("Exported by QtSvg");

        // ❗ 不要 toSize()
        gen.setSize(QSize(
            qCeil(rect.width()),
            qCeil(rect.height())
        ));

        // ❗ ViewBox 必须是 scene 的世界坐标
        gen.setViewBox(rect);

        QPainter painter(&gen);

        // 4️⃣ 平移坐标系（解决负坐标裁剪）
        painter.translate(-rect.left(), -rect.top());

        // 5️⃣ 背景
        painter.fillRect(QRectF(QPointF(0, 0), rect.size()), Qt::white);

        // 6️⃣ 渲染 Scene（QtSvg 正确方式）
        scene->render(&painter);

        painter.end();
    }

};
