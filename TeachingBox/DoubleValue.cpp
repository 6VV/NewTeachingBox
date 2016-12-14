#include "stdafx.h"
#include "DoubleValue.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include <assert.h>



namespace NVariateValue
{
	DoubleValue::DoubleValue(double value)
		:m_value(value)
	{
	}

	DoubleValue::operator double() const
	{
		return m_value;
	}

	void NVariateValue::DoubleValue::WriteToDataStream(QDataStream& dataStream) const
	{
		dataStream << m_value;
	}

	void NVariateValue::DoubleValue::WriteToTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column) const
	{
		assert(row < parentItem->childCount());

		treeWidget->setItemWidget(parentItem->child(row), column, new LineEditWithRegExpAndKeyboard(QString::number(m_value), RegExp::STR_REG_FLOAT, treeWidget));
	}

	void NVariateValue::DoubleValue::ReadFromDataStream(QDataStream& dataStream)
	{
		dataStream >> m_value;
	}

	void NVariateValue::DoubleValue::ReadFromTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column)
	{
		assert(row < parentItem->childCount());

		auto widget = treeWidget->itemWidget(parentItem->child(row), column);

		assert(typeid(*widget) == typeid(QLineEdit));

		m_value = dynamic_cast<QLineEdit*>(widget)->text().toDouble();
	}


}