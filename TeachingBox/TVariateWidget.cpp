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

void TVariateWidget::ReadTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget)
{
	m_itemVariateHeader = new TreeWidgetItemWithVariate(parentItem, m_variate);

	ReadContentIntoItem(m_itemVariateHeader, treeWidget);
}

void TVariateWidget::ReadContentIntoItem(TreeWidgetItemWithVariate* parentItem, QTreeWidget* treeWidget)
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

	ReadContentTreeWidgetItem(parentItem, treeWidget);
}

void TVariateWidget::SlotOnValueChanged()
{
	OnValueChanged();

	m_itemVariateHeader->IsSave(true);
}
