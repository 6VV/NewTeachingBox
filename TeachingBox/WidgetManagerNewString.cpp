#include "stdafx.h"
#include "WidgetManagerNewString.h"
#include "TString.h"
#include "LineEditWithRegExpAndKeyboard.h"


namespace VariateWidget
{
	VariateWidget::WidgetManagerNewString::WidgetManagerNewString(QTableWidget* tableWidget, int startRowCount)
		:WidgetManagerNewVariate(tableWidget,startRowCount)
	{

	}

	VariateWidget::WidgetManagerNewString::~WidgetManagerNewString()
	{

	}

	std::unique_ptr<TVariate> VariateWidget::WidgetManagerNewString::GetVariate(const QString& name, const QString& scope)
	{
		QString valueString = dynamic_cast<QLineEdit*>(m_tableWidget->cellWidget(m_startRowCount, 1))->text();

		return std::unique_ptr<TVariate>(new TString(scope, name, valueString));
	}

	void VariateWidget::WidgetManagerNewString::InitParameter()
	{
		m_tableWidget->setRowCount(m_startRowCount + 1);
		QLabel* lbValue = new QLabel(QObject::tr("Value"));

		m_tableWidget->setCellWidget(m_startRowCount, 0, lbValue);
		m_tableWidget->setCellWidget(m_startRowCount, 1, new LineEditWithRegExpAndKeyboard());
	}
}