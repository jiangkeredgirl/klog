#pragma once

#include <QGraphicsScene>
#include <QGraphicsSceneContextMenuEvent>   // ✅ 必须
#include <QMenu>
#include <QColorDialog>
#include <QMap>

#include "MindNodeItem.h"
#include "MindEdgeItem.h"


class MindMapScene : public QGraphicsScene {
    Q_OBJECT
public:
    MindMapScene() {
        setSceneRect(-2000, -2000, 4000, 4000);
    }

    void buildDemoTree() {
        root = new MindNode{"Root"};

        addChild(root, "Left-1");
        addChild(root, "Left-2");
        addChild(root, "Right-1");
        addChild(root, "Right-2");

        rebuild();
    }

protected:
    void contextMenuEvent(QGraphicsSceneContextMenuEvent* event) override {
        auto item = dynamic_cast<MindNodeItem*>(itemAt(event->scenePos(), QTransform()));
        if (!item) return;

        QMenu menu;
        auto addAct = menu.addAction("➕ 添加子节点");
        auto delAct = menu.addAction("❌ 删除节点");
        auto colAct = menu.addAction("🎨 修改颜色");

        auto sel = menu.exec(event->screenPos());

        if (sel == addAct) {
            addChild(item->node(), "New Node");
            rebuild();
        }
        else if (sel == delAct) {
            deleteNode(item->node());
            rebuild();
        }
        else if (sel == colAct) {
            QColor c = QColorDialog::getColor(item->node()->color);
            if (c.isValid()) {
                item->node()->color = c;
                update();
            }
        }
    }

private:
    MindNode* root = nullptr;
    QMap<MindNode*, MindNodeItem*> nodeMap;

    void addChild(MindNode* parent, const QString& text) {
        auto n = new MindNode{text};
        n->parent = parent;
        parent->children.push_back(n);
    }

    void deleteNode(MindNode* node) {
        if (!node || node == root) return;

        node->parent->children.removeOne(node);
        delete node;
    }

    // ========= 自动布局（左右脑） =========
    void rebuild() {
        clear();
        nodeMap.clear();

        layout(root, 0, 0, true);
        drawEdges();
    }

    void layout(MindNode* node, int depth, int y, bool center) {
        auto item = new MindNodeItem(node);
        addItem(item);
        nodeMap[node] = item;

        int x = depth * 200;
        if (!center)
            x *= (node->parent->children.indexOf(node) % 2 == 0 ? -1 : 1);

        item->setPos(x, y);

        int childY = y - (node->children.size() - 1) * 60 / 2;
        for (auto c : node->children) {
            layout(c, depth + 1, childY, false);
            childY += 60;
        }
    }

    void drawEdges() {
        for (auto it = nodeMap.begin(); it != nodeMap.end(); ++it) {
            auto node = it.key();
            if (!node->parent) continue;

            addItem(new MindEdgeItem(
                nodeMap[node->parent],
                nodeMap[node]
            ));
        }
    }
};
