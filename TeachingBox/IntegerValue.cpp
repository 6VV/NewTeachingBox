#include "stdafx.h"
#include "IntegerValue.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include <assert.h>


namespace NVariateValue
{
	IntegerValue::IntegerValue(int value)
		:m_value(value)
	{

	}

	IntegerValue::operator int() const
	{
		return m_value;
	}

	void NVariateValue::IntegerValue::WriteToDataStream(QDataStream& dataStream) const
	{
		dataStream << m_value;
	}

	void NVariateValue::IntegerValue::WriteToTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column) const
	{
		assert(row < parentItem->childCount());

		treeWidget->setItemWidget(parentItem->child(row), column, new LineEditWithRegExpAndKeyboard(QString::number(m_value), RegExp::STR_REG_INT, treeWidget));
	}

	void NVariateValue::IntegerValue::ReadFromDataStream(QDataStream& dataStream)
	{
		dataStream >> m_value;
	}

	void NVariateValue::IntegerValue::ReadFromTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column)
	{
		assert(row < parentItem->childCount());

		auto widget=treeWidget->itemWidget(parentItem->child(row), column);

		assert(typeid(*widget) == typeid(QLineEdit));

		m_value = dynamic_cast<QLineEdit*>(widget)->text().toInt();
	}

}