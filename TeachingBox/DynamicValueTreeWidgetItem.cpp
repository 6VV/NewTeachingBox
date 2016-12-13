#include "stdafx.h"
#include "DynamicValueTreeWidgetItem.h"
#include "TDynamic.h"
#include <assert.h>



VariateValueTreeWidgetBuilder<DynamicValueTreeWidgetItem> DynamicValueTreeWidgetItem::buidler(TDynamic::TypeName());

std::shared_ptr<TVariate> DynamicValueTreeWidgetItem::GetVariate(const TSymbol& symbol, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem,int index)
{
	tDynamicConstraint value{};

	value.m_Velocity = dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(0+index), 1))->text().toDouble();
	value.m_Acceleration = dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(1 + index), 1))->text().toDouble();
	value.m_Deceleration = dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(2 + index), 1))->text().toDouble();
	value.m_PostureVelocity = dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(3 + index), 1))->text().toDouble();
	value.m_PostureAcceleration = dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(4 + index), 1))->text().toDouble();
	value.m_PostureDeceleration = dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(5 + index), 1))->text().toDouble();

	return std::shared_ptr<TDynamic>(new TDynamic(symbol, value));
}

void DynamicValueTreeWidgetItem::InsertVariateValue(const std::shared_ptr<TVariate> variate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*variate) == typeid(TDynamic));

	auto value = dynamic_cast<TDynamic*>(variate.get())->GetValue();

	InsertDouble("Velocity", value.m_Velocity, treeWidget, variateItem);
	InsertDouble("Accelerate", value.m_Acceleration, treeWidget, variateItem);
	InsertDouble("Deceleration", value.m_Deceleration, treeWidget, variateItem);
	InsertDouble("PostureVelocity", value.m_PostureVelocity, treeWidget, variateItem);
	InsertDouble("PostureAcceleration", value.m_PostureAcceleration, treeWidget, variateItem);
	InsertDouble("PostureDeceleration", value.m_PostureDeceleration, treeWidget, variateItem);
}

void DynamicValueTreeWidgetItem::UpdateWidgetValue(const std::shared_ptr<TVariate> newVariate, QTreeWidget* treeWidget, QTreeWidgetItem* variateItem)
{
	assert(typeid(*newVariate) == typeid(TDynamic));

	auto value = dynamic_cast<TDynamic*>(newVariate.get())->GetValue();

	dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(0), 1))->setText(QString::number(value.m_Velocity));
	dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(1), 1))->setText(QString::number(value.m_Acceleration));
	dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(2), 1))->setText(QString::number(value.m_Deceleration));
	dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(3), 1))->setText(QString::number(value.m_PostureVelocity));
	dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(4), 1))->setText(QString::number(value.m_PostureAcceleration));
	dynamic_cast<QLineEdit*>(treeWidget->itemWidget(variateItem->child(5), 1))->setText(QString::number(value.m_PostureDeceleration));
}
