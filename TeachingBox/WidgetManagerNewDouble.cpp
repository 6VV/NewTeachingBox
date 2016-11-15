#include "stdafx.h"
#include "WidgetManagerNewDouble.h"
#include "TDouble.h"
#include "LineEditWithRegExpAndKeyboard.h"


namespace VariateWidget
{

	WidgetManagerNewDouble::WidgetManagerNewDouble(QTableWidget* tableWidget, int startRowCount)
		:WidgetManagerNewVariate(tableWidget, startRowCount)
	{

	}

	WidgetManagerNewDouble::~WidgetManagerNewDouble()
	{

	}

	std::unique_ptr<TVariate> VariateWidget::WidgetManagerNewDouble::GetVariate(const QString& name, const QString& scope)
	{
		QString valueString = dynamic_cast<QLineEdit*>(m_tableWidget->cellWidget(m_startRowCount, 1))->text();

		bool ok;
		double value = valueString.toDouble(&ok);
		if (!ok)
		{
			return nullptr;
		}

		return std::unique_ptr<TVariate>(new TDouble(scope, name, value));
	}

	void VariateWidget::WidgetManagerNewDouble::InitParameter()
	{
		m_tableWidget->setRowCount(m_startRowCount + 1);
		QLabel* lbValue = new QLabel(QObject::tr("Value"));

		m_tableWidget->setCellWidget(m_startRowCount, 0, lbValue);
		m_tableWidget->setCellWidget(m_startRowCount, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
	}

}