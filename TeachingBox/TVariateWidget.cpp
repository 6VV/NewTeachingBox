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
	delete m_variate;
	m_variate = nullptr;
}

void TVariateWidget::ReadTreeWidgetItem(QTreeWidgetItem* parentItem, QTreeWidget* treeWidget)
{
	m_itemVariateHeader = new TreeWidgetItemWithVariate(parentItem, m_variate);

	ReadContentIntoItem(m_itemVariateHeader, treeWidget);
}

void TVariateWidget::ReadContentIntoItem(TreeWidgetItemWithVariate* parentItem, QTreeWidget* treeWidget)
{
	parentItem->Variate(m_variate);

	ReadContentTreeWidgetItem(parentItem, treeWidget);
}

void TVariateWidget::SlotOnValueChanged()
{
	OnValueChanged();

	m_itemVariateHeader->IsSave(true);
}
