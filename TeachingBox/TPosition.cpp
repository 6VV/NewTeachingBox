#include "stdafx.h"
#include "TPosition.h"
#include "TreeWidgetItemWithVariate.h"
#include "RegExp.h"
#include "LineEditInTree.h"
#include "TPositionWidget.h"


TPosition::TPosition(QDataStream& dataStream) : TVariate(dataStream)
{
	double value;

	for (int i = 0; i < AXIS_SIZE;++i)
	{
		dataStream >> value;
		m_value.m_AxisPosition[i] = value;
		//m_value.push_back(value);
	}

	Init();
}

TPosition::TPosition(const QString& scope, const QString& name, const tAxesAllPositions& value)
	:TVariate(scope, name, TSymbol::TYPE_POSITION)
{
	m_value = value;

	Init();
}

TPosition::TPosition(const TPosition& variate)
	: TVariate(variate)
{
	m_value = variate.m_value;

	Init();
}

const tAxesAllPositions TPosition::GetValue() const
{
	return m_value;
}

void TPosition::SetValue(const tAxesAllPositions& value)
{
	m_value = value;
}

void TPosition::ReadValueStream(QDataStream& dataStream)const
{
	for (int i = 0; i < AXIS_SIZE;++i)
	{
		dataStream << m_value.m_AxisPosition[i];
	}
}

void TPosition::UpdateFromValue(const TVariate& variate)
{
	m_value = static_cast<const TPosition&>(variate).m_value;
}

//void TPosition::SlotOnTextChanged()
//{
//	LineEditInTree* currentWidget = static_cast<LineEditInTree*>(sender());
//	QTreeWidgetItem* parentItem = currentWidget->GetParentItem();
//	QTreeWidget* treeWidget = currentWidget->GetTreeWidget();
//
//	tAxesAllPositions position{};
//	for (int i = 0; i < parentItem->childCount();++i)
//	{
//		QLineEdit* lineEdit=static_cast<QLineEdit*>(treeWidget->itemWidget(parentItem->child(i), 1));
//		position.m_AxisPosition[i] = lineEdit->text().toDouble();
//	}
//
//	m_value = position;
//
//	m_itemVariate->IsSave(true);
//	//UpdateRamAndDatabaseFrom(*this);
//}

void TPosition::Init()
{
	m_variateWidget = new TPositionWidget(this);
}

TVariate* TPosition::Clone() const
{
	return new TPosition(*this);
}
