#include "stdafx.h"
#include "ComboBoxWithParentTreeItem.h"



ComboBoxWithParentItem::ComboBoxWithParentItem(QWidget* parent/*=nullptr*/)
	:QComboBox(parent)
{

}

TreeWidgetItemWithVariate* ComboBoxWithParentItem::ParentItem() const
{
	return m_parentItem;
}

void ComboBoxWithParentItem::ParentItem(TreeWidgetItemWithVariate* parentItem)
{
	m_parentItem = parentItem;
}
