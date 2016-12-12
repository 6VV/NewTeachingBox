#include "stdafx.h"
#include "WidgetManagerNewBool.h"
#include "TVariateType.h"
#include "TBool.h"



namespace VariateWidget
{

	WidgetManagerNewBool::WidgetManagerNewBool(QTableWidget* tableWidget, int startRowCount)
		:WidgetManagerNewVariate(tableWidget,startRowCount)
	{

	}

	WidgetManagerNewBool::~WidgetManagerNewBool()
	{

	}

	std::shared_ptr<TVariate> WidgetManagerNewBool::GetVariate(const QString& name, const QString& scope)
	{
		QString valueString = dynamic_cast<QComboBox*>(m_tableWidget->cellWidget(m_startRowCount, 1))->currentText();

		bool value = false;
		if (valueString == TVariateType::STR_BOOL_TRUE)
		{
			value = true;
		}

		return std::shared_ptr<TVariate>(new TBool(TSymbol{ scope, name }, value));
	}

	void WidgetManagerNewBool::InitParameter()
	{
		m_tableWidget->setRowCount(m_startRowCount + 1);
		QLabel* lbValue = new QLabel(QObject::tr("Value"));
		QComboBox* cmbBool = new QComboBox;
		cmbBool->addItem(TVariateType::STR_BOOL_TRUE);
		cmbBool->addItem(TVariateType::STR_BOOL_FALSE);

		m_tableWidget->setCellWidget(m_startRowCount, 0, lbValue);
		m_tableWidget->setCellWidget(m_startRowCount, 1, cmbBool);
	}

}