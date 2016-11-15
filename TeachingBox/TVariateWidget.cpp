#include "stdafx.h"
#include "TVariateWidget.h"
#include "TVariate.h"
#include "TreeWidgetItemWithVariate.h"
#include "QTreeWidget"


TVariateWidget::TVariateWidget(TVariate* variate)
	:m_variate(variate)
{

}

TVariateWidget::~TVariateWidget()
{

}

void TVariateWidget::WriteToTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget)
{
	m_itemVariateHeader = new TreeWidgetItemWithVariate(parentItem, m_variate);

	WriteContentIntoItem(m_itemVariateHeader, treeWidget);
}

void TVariateWidget::WriteContentIntoItem(TreeWidgetItemWithVariate* parentItem, QTreeWidget* treeWidget)
{
	m_itemVariateHeader = parentItem;
	parentItem->Variate(m_variate);

	auto childItem = parentItem->child(0);
	while (childItem != nullptr)
	{
		parentItem->removeChild(childItem);
		delete childItem;
		childItem = parentItem->child(0);
	}

	WriteContentToTreeWidgetItem(parentItem, treeWidget);
}

void TVariateWidget::SlotOnValueChanged()
{
	OnValueChanged();

	m_itemVariateHeader->IsSave(true);
}
