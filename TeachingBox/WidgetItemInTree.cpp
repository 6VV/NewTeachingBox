#include "stdafx.h"
#include "WidgetItemInTree.h"


WidgetItemInTree::WidgetItemInTree(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget)
{
	m_parentItem = parentItem;
	m_treeWidget = treeWidget;
}

WidgetItemInTree::~WidgetItemInTree()
{

}

QTreeWidget* const WidgetItemInTree::GetTreeWidget() const
{
	return m_treeWidget;
}

QTreeWidgetItem* const WidgetItemInTree::GetParentItem() const
{
	return m_parentItem;
}
