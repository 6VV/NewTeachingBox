#include "stdafx.h"
#include "WidgetManagerNewPosition.h"
#include "DataStruct.h"
#include "TPosition.h"
#include "LineEditWithRegExpAndKeyboard.h"


namespace VariateWidget
{

	WidgetManagerNewPosition::WidgetManagerNewPosition(QTableWidget* tableWidget, int startRowCount)
		:WidgetManagerNewVariate(tableWidget,startRowCount)
	{

	}

	WidgetManagerNewPosition::~WidgetManagerNewPosition()
	{

	}

	std::unique_ptr<TVariate> WidgetManagerNewPosition::GetVariate(const QString& name, const QString& scope)
	{
		tAxesAllPositions position;

		for (int i = m_startRowCount; i < m_startRowCount + AXIS_SIZE; ++i)
		{
			QString valueString = dynamic_cast<QLineEdit*>(m_tableWidget->cellWidget(i, 1))->text();

			bool ok;
			double value = valueString.toDouble(&ok);
			if (!ok)
			{
				return nullptr;
			}
			position.m_AxisPosition[i - m_startRowCount] = value;
		}


		return std::unique_ptr<TVariate>(new TPosition(scope, name, position));
	}

	void WidgetManagerNewPosition::InitParameter()
	{
		m_tableWidget->setRowCount(m_startRowCount + 6);
		QLabel* lbValue1 = new QLabel("Axis1");
		QLabel* lbValue2 = new QLabel("Axis2");
		QLabel* lbValue3 = new QLabel("Axis3");
		QLabel* lbValue4 = new QLabel("Axis4");
		QLabel* lbValue5 = new QLabel("Axis5");
		QLabel* lbValue6 = new QLabel("Axis6");


		m_tableWidget->setCellWidget(m_startRowCount, 0, lbValue1);
		m_tableWidget->setCellWidget(m_startRowCount + 1, 0, lbValue2);
		m_tableWidget->setCellWidget(m_startRowCount + 2, 0, lbValue3);
		m_tableWidget->setCellWidget(m_startRowCount + 3, 0, lbValue4);
		m_tableWidget->setCellWidget(m_startRowCount + 4, 0, lbValue5);
		m_tableWidget->setCellWidget(m_startRowCount + 5, 0, lbValue6);

		m_tableWidget->setCellWidget(m_startRowCount, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(m_startRowCount + 1, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(m_startRowCount + 2, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(m_startRowCount + 3, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(m_startRowCount + 4, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(m_startRowCount + 5, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
	}

}
