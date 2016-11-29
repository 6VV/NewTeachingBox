#include "stdafx.h"
#include "WidgetManagerNewInteger.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include "QTableWidget"
#include "TInteger.h"


namespace VariateWidget
{

	WidgetManagerNewInteger::WidgetManagerNewInteger(QTableWidget* tableWidget, int startRowCount)
		:WidgetManagerNewVariate(tableWidget, startRowCount)
	{

	}

	WidgetManagerNewInteger::~WidgetManagerNewInteger()
	{

	}

	std::unique_ptr<TVariate> WidgetManagerNewInteger::GetVariate(const QString& name, const QString& scope)
	{
		QString valueString = dynamic_cast<QLineEdit*>(m_tableWidget->cellWidget(m_startRowCount, 1))->text();

		bool ok;
		int value = valueString.toInt(&ok);
		if (!ok)
		{
			return nullptr;
		}

		return std::unique_ptr<TVariate>(new TInteger({scope, name}, value));
	}

	void WidgetManagerNewInteger::InitParameter()
	{
		m_tableWidget->setRowCount(m_startRowCount + 1);
		QLabel* lbValue = new QLabel(QObject::tr("Value"));

		m_tableWidget->setCellWidget(m_startRowCount, 0, lbValue);
		m_tableWidget->setCellWidget(m_startRowCount, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_INT));
	}

}

