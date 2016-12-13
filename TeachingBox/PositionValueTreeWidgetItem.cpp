#include "stdafx.h"
#include "PositionValueTreeWidgetItem.h"
#include "TPosition.h"
#include <assert.h>



VariateValueTreeWidgetBuilder<PositionValueTreeWidgetItem> PositionValueTreeWidgetItem::builder(TPosition::TypeName());

std::shared_ptr<TVariate> PositionValueTreeWidgetItem::GetVariate(const TSymbol& symbol, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem,int index)
{
	TPosition::ValueType value{};
	for (int i =index; i < 6 + index; ++i)
	{
		value.m_AxisPosition[i-index] = dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(i),1))->text().toDouble();
	}

	return std::shared_ptr<TPosition>(new TPosition(symbol, value));
}

void PositionValueTreeWidgetItem::InsertVariateValue(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*variate) == typeid(TPosition));
	auto value = dynamic_cast<TPosition*>(variate.get())->GetValue();

	QStringList nameList{ "Axis1", "Axis2", "Axis3", "Axis4","Axis5", "Axis6" };

	for (int i = 0; i < 6;++i)
	{
		InsertDouble(nameList[i], value.m_AxisPosition[i], treeWidget, variateItem);
	}
}

void PositionValueTreeWidgetItem::UpdateWidgetValue(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*newVariate) == typeid(TPosition));
	auto value = dynamic_cast<TPosition*>(newVariate.get())->GetValue();

	for (int i = 0; i < 6; ++i)
	{
		dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(i), 1))->setText(QString::number(value.m_AxisPosition[i]));
	}
}
