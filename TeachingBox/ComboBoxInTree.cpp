#include "stdafx.h"
#include "ComboBoxInTree.h"

ComboBoxInTree::ComboBoxInTree(QTreeWidgetItem* const parentItem, QTreeWidget* const treeWidget)
	:QComboBox(treeWidget)
	,WidgetItemInTree(parentItem,treeWidget)
{
}
