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

	ReadContentTreeWidgetItem(m_itemVariateHeader, treeWidget);
}

void TVariateWidget::SlotOnValueChanged()
{
	OnValueChanged();

	m_itemVariateHeader->IsSave(true);
}
