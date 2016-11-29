#include "stdafx.h"
#include "WidgetManagerNewDynamic.h"
#include "DataStruct.h"
#include "TDynamic.h"
#include "TVariateType.h"
#include "LineEditWithRegExpAndKeyboard.h"



namespace VariateWidget
{

	WidgetManagerNewDynamic::WidgetManagerNewDynamic(QTableWidget* tableWidget, int startRowCount)
		:WidgetManagerNewVariate(tableWidget,startRowCount)
	{

	}

	WidgetManagerNewDynamic::~WidgetManagerNewDynamic()
	{

	}

	std::unique_ptr<TVariate> WidgetManagerNewDynamic::GetVariate(const QString& name, const QString& scope)
	{
		double values[6]{};

		for (int i = m_startRowCount; i < m_startRowCount + AXIS_SIZE; ++i)
		{
			QString valueString = dynamic_cast<QLineEdit*>(m_tableWidget->cellWidget(i, 1))->text();

			bool ok;
			int value = valueString.toInt(&ok);
			if (!ok)
			{
				return nullptr;
			}
			values[i - m_startRowCount] = value;
		}
		tDynamicConstraint dynamic;
		dynamic.m_Velocity = values[0];
		dynamic.m_Acceleration = values[1];
		dynamic.m_Deceleration = values[2];
		dynamic.m_PostureVelocity = values[3];
		dynamic.m_PostureAcceleration = values[4];
		dynamic.m_PostureDeceleration = values[5];

		return std::unique_ptr<TVariate>(new TDynamic({scope, name}, dynamic));
	}

	void WidgetManagerNewDynamic::InitParameter()
	{
		m_tableWidget->setRowCount(m_startRowCount + 6);
		m_tableWidget->setCellWidget(m_startRowCount, 0, new QLabel(QObject::tr("Velocity")));
		m_tableWidget->setCellWidget(m_startRowCount + 1, 0, new QLabel(QObject::tr("Acceleration")));
		m_tableWidget->setCellWidget(m_startRowCount + 2, 0, new QLabel(QObject::tr("Deceleration")));
		m_tableWidget->setCellWidget(m_startRowCount + 3, 0, new QLabel(QObject::tr("PostureVelocity")));
		m_tableWidget->setCellWidget(m_startRowCount + 4, 0, new QLabel(QObject::tr("PostureAcceleration")));
		m_tableWidget->setCellWidget(m_startRowCount + 5, 0, new QLabel(QObject::tr("PostureDeceleration")));

		m_tableWidget->setCellWidget(m_startRowCount, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(m_startRowCount + 1, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(m_startRowCount + 2, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(m_startRowCount + 3, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(m_startRowCount + 4, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(m_startRowCount + 5, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
	}

}