#ifndef _TEACHING_BOX_COMBOBOX_IN_TREE_H_
#define _TEACHING_BOX_COMBOBOX_IN_TREE_H_

#include "QComboBox"
#include "WidgetItemInTree.h"

class ComboBoxInTree:public QComboBox,public WidgetItemInTree
{
	Q_OBJECT

public:
	ComboBoxInTree(QTreeWidgetItem* const parentItem, QTreeWidget* const treeWidget);
};

#endif