#include "stdafx.h"
#include "ComplexValue.h"


namespace NVariateValue
{
	void NVariateValue::ComplexValue::WriteToDataStream(QDataStream& dataStream) const
	{
		for (auto value:m_value)
		{
			value->WriteToDataStream(dataStream);
		}
	}

	void NVariateValue::ComplexValue::WriteToTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column) const
	{
		for (auto value:m_value)
		{
			value->WriteToTreeWidget(treeWidget, parentItem, row++,column);
		}
	}

	void NVariateValue::ComplexValue::ReadFromDataStream(QDataStream& dataStream)
	{
		for (auto value : m_value)
		{
			value->ReadFromDataStream(dataStream);
		}
	}

	void NVariateValue::ComplexValue::ReadFromTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column)
	{
		for (auto value : m_value)
		{
			value->ReadFromTreeWidget(treeWidget, parentItem,row++,column);
		}
	}

	ComplexValue::ComplexValue(ValueType value)
		:m_value(value)
	{
	}

	ComplexValue::operator ValueType() const
	{
		return m_value;
	}

}