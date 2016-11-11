#ifndef _TEACHING_BOX_COMBO_BOX_WITH_PARENT_TREE_ITEM_H_
#define _TEACHING_BOX_COMBO_BOX_WITH_PARENT_TREE_ITEM_H_

#include "QComboBox"

class TreeWidgetItemWithVariate;

class ComboBoxWithParentItem:public QComboBox
{
public:
	ComboBoxWithParentItem(QWidget* parent = nullptr);
	
	void ParentItem(TreeWidgetItemWithVariate* parentItem);
	TreeWidgetItemWithVariate* ParentItem() const;

private:
	TreeWidgetItemWithVariate* m_parentItem=nullptr;
};

#endif