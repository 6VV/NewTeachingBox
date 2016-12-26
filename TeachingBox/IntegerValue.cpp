#include "stdafx.h"
#include "IntegerValue.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include <assert.h>


IntegerValue::IntegerValue(int value)
	:m_value(value)
{

}

IntegerValue::operator int() const
{
	return m_value;
}

void IntegerValue::WriteToDataStream(QDataStream& dataStream) const
{
	dataStream << m_value;
}
//
//void IntegerValue::WriteToTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column) const
//{
//	assert(row < parentItem->childCount());
//
//	auto widget = new LineEditWithRegExpAndKeyboard(QString::number(m_value), RegExp::STR_REG_INT, treeWidget);
//	treeWidget->setItemWidget(parentItem->child(row), column, widget);
//
//}

void IntegerValue::ReadFromDataStream(QDataStream& dataStream)
{
	dataStream >> m_value;
}

//void IntegerValue::ReadFromTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column)
//{
//	assert(row < parentItem->childCount());
//
//	auto widget = treeWidget->itemWidget(parentItem->child(row), column);
//
//	assert(typeid(*widget) == typeid(QLineEdit));
//
//	m_value = dynamic_cast<QLineEdit*>(widget)->text().toInt();
//}
//
//void IntegerValue::UpdateTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column) const
//{
//	assert(row < parentItem->childCount());
//
//	dynamic_cast<QLineEdit*>(treeWidget->itemWidget(parentItem->child(row), column))->setText(QString::number(m_value));
//}

