#ifndef _TEACHING_BOX_WIDGET_ITEM_IN_TREE_H_
#define _TEACHING_BOX_WIDGET_ITEM_IN_TREE_H_

class QTreeWidget;
class QTreeWidgetItem;

class WidgetItemInTree
{
public:
	WidgetItemInTree(QTreeWidgetItem* parentItem,QTreeWidget* treeWidget);
	~WidgetItemInTree();

	QTreeWidget* const GetTreeWidget() const;
	QTreeWidgetItem* const GetParentItem() const;

protected:
	QTreeWidgetItem* m_parentItem=nullptr;
	QTreeWidget* m_treeWidget=nullptr;
};

#endif