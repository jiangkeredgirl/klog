#pragma once

#include <QObject>
#include "qtstandard.h"
#include "cstandard.h"
#include "funcflow.h"
#include "mindmapscene.h"

class FuncMindMapui : public QObject
{
	Q_OBJECT

public:
	FuncMindMapui();
	~FuncMindMapui();

public:
	void setupUi(QDialog* hostDialog);

public:
	void FuncStacksAddInTrees(const string& process_name, const string& threadid, list<string>& func_stacks);
	void FuncStacksAddInTree(list<string>& func_stacks, QTreeWidget* thread_tree);
	void AddItem(QTreeWidget* thread_tree, QTreeWidgetItem* parentItem, list<string>& func_stacks);
    



    // ===================== 核心工具函数（适配多根节点） =====================
    // 1. 构建单个 FuncTreeNode 对应的界面节点（复用）
    void buildTreeWidgetItem(QTreeWidgetItem* parentWidgetItem, const std::shared_ptr<FuncTreeNode>& funcTreeNode)
    {
        if (!parentWidgetItem || !funcTreeNode) return;

        QTreeWidgetItem* item = new QTreeWidgetItem(parentWidgetItem);
        parentWidgetItem->setExpanded(true);
        // 显示函数名 + 调用状态样式
        item->setText(0, QString::fromStdString(funcTreeNode->func_trace->funcname));
        item->setForeground(0, funcTreeNode->is_calling ? Qt::red : Qt::black);

        // 存储 FuncTreeNode 指针（核心映射）
        item->setData(0, FuncTreeNodeRole, QVariant::fromValue(reinterpret_cast<void*>(funcTreeNode.get())));

        // 递归构建子分支
        for (const auto& branch : funcTreeNode->branchs)
        {
            buildTreeWidgetItem(item, branch);
        }
    }

    // 2. 批量添加多个 FuncTreeNode 根节点到 QTreeWidget
    void addRootFuncTreeNodes(std::shared_ptr<FuncTreeNode>& rootNode)
    {
        if (!treeWidget) return;

        // 获取 QTreeWidget 的隐形根节点（所有顶层节点的父节点）
        QTreeWidgetItem* invisibleRoot = treeWidget->invisibleRootItem();
        //for (const auto& rootNode : rootNodes)
        {
            // 每个根节点都挂载到隐形根节点下，成为界面的顶层节点
            buildTreeWidgetItem(invisibleRoot, rootNode);
        }
    }

    // 3. 从界面节点反向获取 FuncTreeNode 指针（复用）
    std::shared_ptr<FuncTreeNode> getFuncTreeNodeFromItem(QTreeWidgetItem* item)
    {
        if (!item) return nullptr;
        void* ptr = item->data(0, FuncTreeNodeRole).value<void*>();
        return ptr ? std::shared_ptr<FuncTreeNode>(reinterpret_cast<FuncTreeNode*>(ptr)) : nullptr;
    }

    // 4. 根据 FuncTreeNode 指针查找对应的 QTreeWidgetItem（天然支持多根节点）
    QTreeWidgetItem* findWidgetItemByFuncTreeNode(QTreeWidget* treeWidget, const FuncTreeNode* funcTreeNode)
    {
        if (!treeWidget || !funcTreeNode) return nullptr;

        // 从隐形根节点开始遍历所有节点（包括所有顶层根节点）
        QTreeWidgetItem* invisibleRoot = treeWidget->invisibleRootItem();
        for (int i = 0; i < invisibleRoot->childCount(); ++i)
        {
            QTreeWidgetItem* childItem = invisibleRoot->child(i);
            // 对比当前节点存储的指针
            void* storedPtr = childItem->data(0, FuncTreeNodeRole).value<void*>();
            if (storedPtr == funcTreeNode)
            {
                return childItem;
            }

            // 递归查找子节点
            QTreeWidgetItem* foundItem = findWidgetItemByFuncTreeNode(childItem, funcTreeNode);
            if (foundItem) return foundItem;
        }
        return nullptr;
    }

    // 优化 findWidgetItemByFuncTreeNode 重载（兼容子节点查找）
    QTreeWidgetItem* findWidgetItemByFuncTreeNode(QTreeWidgetItem* parentItem, const FuncTreeNode* funcTreeNode)
    {
        if (!parentItem || !funcTreeNode) return nullptr;

        for (int i = 0; i < parentItem->childCount(); ++i)
        {
            QTreeWidgetItem* childItem = parentItem->child(i);
            void* storedPtr = childItem->data(0, FuncTreeNodeRole).value<void*>();
            if (storedPtr == funcTreeNode)
            {
                return childItem;
            }

            QTreeWidgetItem* foundItem = findWidgetItemByFuncTreeNode(childItem, funcTreeNode);
            if (foundItem) return foundItem;
        }
        return nullptr;
    }

    // 5. 更新 FuncTreeNode 对应的界面节点（适配多根）
    void updateFuncTreeNodeWidgetItem(const std::shared_ptr<FuncTreeNode>& funcTreeNode)
    {
        if (!treeWidget || !funcTreeNode) return;

        // 从整个树（隐形根节点）查找节点
        QTreeWidgetItem* item = findWidgetItemByFuncTreeNode(treeWidget, funcTreeNode.get());
        if (!item) return;

        // 更新显示
        item->setText(0, QString::fromStdString(funcTreeNode->func_trace->funcname));
        item->setForeground(0, funcTreeNode->is_calling ? Qt::red : Qt::black);
    }

    // 6. 添加 FuncTreeNode 分支（复用）
    bool addFuncTreeNodeBranch(const std::shared_ptr<FuncTreeNode>& parentFunc, const std::shared_ptr<FuncTreeNode>& newBranch)
    {
        if (!treeWidget || !parentFunc || !newBranch) return false;

#if 0
        // 避免重复添加
        auto it = std::find(parentFunc->branchs.begin(), parentFunc->branchs.end(), newBranch);
        if (it != parentFunc->branchs.end()) return false;

        // 更新数据
        parentFunc->branchs.push_back(newBranch);
        newBranch->parent = parentFunc.get();
#endif

        // 找到父节点对应的界面节点
        QTreeWidgetItem* parentItem = findWidgetItemByFuncTreeNode(treeWidget, parentFunc.get());
        if (!parentItem) return false;

        // 更新界面
        buildTreeWidgetItem(parentItem, newBranch);
        return true;
    }

    // 7. 删除 FuncTreeNode 分支（复用）
    bool removeFuncTreeNodeBranch(QTreeWidget* treeWidget, const std::shared_ptr<FuncTreeNode>& delBranch)
    {
        if (!treeWidget || !delBranch || !delBranch->parent) return false;

        // 找到并删除界面节点
        QTreeWidgetItem* delItem = findWidgetItemByFuncTreeNode(treeWidget, delBranch.get());
        if (delItem)
        {
            QTreeWidgetItem* parentItem = delItem->parent();
            if (parentItem)
            {
                parentItem->removeChild(delItem);
                delete delItem; // 释放内存
            }
        }

        // 更新数据
        FuncTreeNode* parentFunc = delBranch->parent;
        parentFunc->branchs.remove(delBranch);
        delBranch->parent = nullptr;

        return true;
    }



public:
	QDialog*  m_hostDialog = nullptr;
	QListWidget* m_trees_list = nullptr;


    // 自定义角色：存储 FuncTreeNode 原始指针
    const int FuncTreeNodeRole = Qt::UserRole + 1;
    QTreeWidget* treeWidget;
};
