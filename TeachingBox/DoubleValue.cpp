#include "stdafx.h"
#include "DoubleValue.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include <assert.h>



	DoubleValue::DoubleValue(double value)
		:m_value(value)
	{
	}

	DoubleValue::operator double() const
	{
		return m_value;
	}

	void DoubleValue::WriteToDataStream(QDataStream& dataStream) const
	{
		dataStream << m_value;
	}

	/*void DoubleValue::WriteToTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column) const
	{
		assert(row < parentItem->childCount());

		auto widget = new LineEditWithRegExpAndKeyboard(QString::number(m_value), RegExp::STR_REG_FLOAT, treeWidget);
		treeWidget->setItemWidget(parentItem->child(row), column, widget);

	}

	void DoubleValue::UpdateTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column) const
	{
		assert(row < parentItem->childCount());

		dynamic_cast<QLineEdit*>(treeWidget->itemWidget(parentItem->child(row), column))->setText(QString::number(m_value));

	}*/

	void DoubleValue::ReadFromDataStream(QDataStream& dataStream)
	{
		dataStream >> m_value;
	}

	/*void DoubleValue::ReadFromTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column)
	{
		assert(row < parentItem->childCount());

		auto widget = treeWidget->itemWidget(parentItem->child(row), column);

		assert(typeid(*widget) == typeid(QLineEdit));

		m_value = dynamic_cast<QLineEdit*>(widget)->text().toDouble();
	}*/


