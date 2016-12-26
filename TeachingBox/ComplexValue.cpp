#include "stdafx.h"
#include "ComplexValue.h"


	void ComplexValue::WriteToDataStream(QDataStream& dataStream) const
	{
		for (auto value:m_value)
		{
			value->WriteToDataStream(dataStream);
		}
	}

	/*void ComplexValue::WriteToTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column) const
	{
		for (auto value:m_value)
		{
			value->WriteToTreeWidget(treeWidget, parentItem, row++,column);
		}
	}*/

	void ComplexValue::ReadFromDataStream(QDataStream& dataStream)
	{
		for (auto value : m_value)
		{
			value->ReadFromDataStream(dataStream);
		}
	}

	//void ComplexValue::ReadFromTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column)
	//{
	//	for (auto value : m_value)
	//	{
	//		value->ReadFromTreeWidget(treeWidget, parentItem,row++,column);
	//	}
	//}

	//void ComplexValue::UpdateTreeWidget(QTreeWidget* treeWidget, QTreeWidgetItem* parentItem, int row, int column) const
	//{
	//	for (auto value : m_value)
	//	{
	//		value->UpdateTreeWidget(treeWidget, parentItem, row++, column);
	//	}
	//}

	ComplexValue::ComplexValue(ValueType value)
		:m_value(value)
	{
	}

	ComplexValue::operator ValueType() const
	{
		return m_value;
	}

