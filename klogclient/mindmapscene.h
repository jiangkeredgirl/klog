#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>   // ✅ 必须
#include <QMenu>
#include <QColorDialog>
#include <QMap>

#include "MindNodeItem.h"
#include "MindEdgeItem.h"
#include <qdialog.h>
#include "funcflow.h"


class MindMapScene : public QWidget {

    Q_OBJECT
public:
    MindMapScene();

private slots:
    void exportSvg();

public:
    MindNode* buildDemoTree();
    MindNode* addTree(const std::shared_ptr<FuncTreeNode>& parentFunc);
    MindNode* addTree(const std::shared_ptr<FuncTreeNode>& parentFunc, const std::shared_ptr<FuncTreeNode>& newBranch);
    MindNode* updateTree( const std::shared_ptr<FuncTreeNode>& funcnode);
    MindNode* getMindNode(const std::shared_ptr<FuncTreeNode>& funcnode, MindNode* mindnode)
    {
        MindNode* getnode = nullptr;
        if (funcnode && mindnode)
        {
            if (funcnode.get() == mindnode->funcTreeNode)
            {
                getnode = mindnode;
            }
            else
            {
                if (!mindnode->children.empty())
                {
                    for (auto child : mindnode->children)
                    {
                        getnode = getMindNode(funcnode, child);
                        if (getnode)
                        {
                            break;
                        }
                    }
                }
            }
        }
        return getnode;
    }

    MindNode* m_root;

    QGraphicsView* m_view;
    QGraphicsScene* m_scene;
};

#include "layout.h"
#include <QSvgGenerator>
#include <QToolBar>
#include <QFileDialog>
#include <QSvgGenerator>
#include <QPainter>
#include <QGraphicsView>
#include <QVBoxLayout>

inline MindMapScene::MindMapScene()
{
    resize(1000, 600);

    m_scene = new QGraphicsScene(this);
    m_view = new QGraphicsView(m_scene, this);
    m_view->setRenderHint(QPainter::Antialiasing);
    //setCentralWidget(m_view);
    QVBoxLayout* layout = new QVBoxLayout;
    this->setLayout(layout);
    QWidget* widget_panel = new QWidget();
    layout->addWidget(widget_panel);
    QVBoxLayout* widget_panel_layout = new QVBoxLayout;
    widget_panel->setLayout(widget_panel_layout);
    widget_panel_layout->addWidget(m_view);
    

    //MindNode* root = buildDemoTree();
    //layoutTree(root, m_scene, 0, 0);

    // Toolbar
    //auto* tb = addToolBar("Export");
    //QAction* actExport = tb->addAction("Export SVG");
    //connect(actExport, &QAction::triggered,
    //    this, &MindMapScene::exportSvg);
}

inline MindNode* MindMapScene::buildDemoTree()
{
    auto* root = new MindNode{ "Root", QColor("#2563EB") };

    //auto* a = new MindNode{ "Module A", QColor("#059669") };
    //auto* b = new MindNode{ "Module B", QColor("#D97706") };

    //root->children = { a, b };

    //a->children.append(new MindNode{ "File A1", QColor("#DC2626") });
    //a->children.append(new MindNode{ "File A2", QColor("#7C3AED") });

    //b->children.append(new MindNode{ "File B1", QColor("#CA8A04") });
    //b->children.append(new MindNode{ "File B2", QColor("#0284C7") });
    m_root = root;

    layoutTree(m_root, m_scene, 0, 0);
    return root;
}

inline  MindNode* MindMapScene::addTree(const std::shared_ptr<FuncTreeNode>& parentFunc)
{
    buildDemoTree();
    m_root->funcTreeNode = parentFunc.get();
    m_root->text = parentFunc->func_trace->funcname.c_str();
    m_root->parent = nullptr;
    layoutTree(m_root, m_scene, 0, 0);
    return m_root;
}

inline MindNode* MindMapScene::addTree(const std::shared_ptr<FuncTreeNode>& parentFunc, const std::shared_ptr<FuncTreeNode>& newBranch)
{
    m_scene->clear();
    auto* parent = getMindNode(parentFunc, m_root);
    //if (parent == nullptr)
    //{
    //    parent = m_root;
    //}
	if (parent)
	{
		MindNode* node = new MindNode{ newBranch->func_trace->funcname.c_str(), QColor("#DC2626") };
		node->funcTreeNode = newBranch.get();
        node->parent = parent;
		parent->children.append(node);
		layoutTree(m_root, m_scene, 0, 0);
	}
    return parent;
}

inline MindNode* MindMapScene::updateTree(const std::shared_ptr<FuncTreeNode>& funcnode)
{
    m_scene->clear();
    auto* parent = getMindNode(funcnode, m_root);
    if (parent)
    {
        parent->textColor = QColor("#7C3AED");
        layoutTree(m_root, m_scene, 0, 0);
    }    
    return parent;
}

#if 0
void MindMapScene::exportSvg()
{
    QString file = QFileDialog::getSaveFileName(
        this,
        "Export SVG",
        "mindmap.svg",
        "SVG Files (*.svg)");

    if (file.isEmpty())
        return;

    // 获取完整内容区域（关键点！）
    QRectF sceneRect = m_scene->itemsBoundingRect();
    sceneRect.adjust(-20, -20, 20, 20); // 留边距

    QSvgGenerator generator;
    generator.setFileName(file);
    generator.setSize(sceneRect.size().toSize());
    generator.setViewBox(sceneRect);
    generator.setTitle("MindMap");
    generator.setDescription("Graphviz-style mind map exported from Qt");

    QPainter painter;
    painter.begin(&generator);

    // ⚠️ 关键：平移 scene 到 (0,0)，否则 SVG 会偏移
    painter.translate(-sceneRect.topLeft());

    m_scene->render(&painter);
    painter.end();
}
#endif

#if 1
inline void MindMapScene::exportSvg()
{
    QString file = QFileDialog::getSaveFileName(
        this,
        "Export SVG",
        "mindmap.svg",
        "SVG Files (*.svg)");

    if (file.isEmpty())
        return;

    // 1️⃣ 精确获取所有 item 的包围盒（scene 坐标）
    QRectF contentRect = m_scene->itemsBoundingRect();

    // 必须留边距（箭头 / 线宽 / 圆角都会超出）
    const qreal margin = 40;
    contentRect.adjust(-margin, -margin, margin, margin);

    // 2️⃣ 创建 SVG
    QSvgGenerator generator;
    generator.setFileName(file);

    // ⚠️ 关键点 1：size 和 viewBox 必须对应
    QSize svgSize(
        std::ceil(contentRect.width() * 2),
        std::ceil(contentRect.height())
    );
    generator.setSize(svgSize);

    // ⚠️ 关键点 2：viewBox 从 (0,0) 开始
    generator.setViewBox(QRectF(0, 0,
        contentRect.width(),
        contentRect.height()));

    generator.setTitle("MindMap");
    generator.setDescription("Graphviz-style mind map (Qt)");

    // 3️⃣ 开始绘制
    QPainter painter(&generator);
    painter.setRenderHint(QPainter::Antialiasing);

    // ⚠️ 关键点 3：把 scene 平移到 (0,0)
    painter.translate(-contentRect.topLeft());

    // ⚠️ 关键点 4：显式指定 sourceRect
    m_scene->render(
        &painter,
        QRectF(0, 0,
            contentRect.width(),
            contentRect.height()),
        contentRect,
        Qt::KeepAspectRatio
    );

    painter.end();
}
#endif

#if 0
void MindMapScene::exportSvg()
{
    QString file = QFileDialog::getSaveFileName(
        this,
        "Export SVG",
        "mindmap.svg",
        "SVG Files (*.svg)");

    if (file.isEmpty())
        return;

    // 1️⃣ Scene 包围盒
    QRectF contentRect = m_scene->itemsBoundingRect();

    // =========================
    // 2️⃣ 层级感知的安全外扩
    // =========================
    constexpr qreal ARROW_LENGTH = 14.0;
    constexpr int   MAX_ARROW_DEPTH = 8;   // ★ 核心
    constexpr qreal PEN_MAX_WIDTH = 6.0;
    constexpr qreal AA_MARGIN = 2.0;

    const qreal safeMargin =
        ARROW_LENGTH * MAX_ARROW_DEPTH +
        PEN_MAX_WIDTH * 0.5 +
        AA_MARGIN;

    contentRect.adjust(
        -safeMargin,
        -safeMargin,
        safeMargin,
        safeMargin
    );

    // =========================
    // 3️⃣ SVG Generator
    // =========================
    QSvgGenerator generator;
    generator.setFileName(file);

    generator.setSize(QSize(
        std::ceil(contentRect.width() * 2),
        std::ceil(contentRect.height())
    ));

    generator.setViewBox(QRectF(
        0, 0,
        contentRect.width(),
        contentRect.height()
    ));

    generator.setTitle("MindMap");
    generator.setDescription("Graphviz-style mind map (QtSvg)");

    // =========================
    // 4️⃣ Render
    // =========================
    QPainter painter(&generator);
    painter.setRenderHint(QPainter::Antialiasing);

    painter.translate(-contentRect.topLeft());

    m_scene->render(
        &painter,
        QRectF(0, 0,
            contentRect.width(),
            contentRect.height()),
        contentRect,
        Qt::IgnoreAspectRatio
    );

    painter.end();
}
#endif