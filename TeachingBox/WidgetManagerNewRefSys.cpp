#include "stdafx.h"
#include "WidgetManagerNewRefSys.h"
#include "TRefSys.h"
#include <assert.h>
#include "LineEditWithRegExpAndKeyboard.h"
#include "VariateWidgetProducer.h"
#include "TVariateManager.h"


namespace VariateWidget
{

	WidgetManagerNewRefSys::WidgetManagerNewRefSys(QTableWidget* tableWidget, int startRowCount)
		:WidgetManagerNewVariate(tableWidget,startRowCount)
	{

	}

	WidgetManagerNewRefSys::~WidgetManagerNewRefSys()
	{

	}

	std::shared_ptr<TVariate> WidgetManagerNewRefSys::GetVariate(const QString& name, const QString& scope)
	{
		TRefSys::ValueType resultValue;

		resultValue.baseSys = static_cast<QComboBox*>(m_tableWidget->cellWidget(m_startRowCount, 1))->currentText();

		for (int i = m_startRowCount + 1; i < m_startRowCount + 7; ++i)
		{
			QString valueString = dynamic_cast<QLineEdit*>(m_tableWidget->cellWidget(i, 1))->text();

			bool ok;
			double value = valueString.toDouble(&ok);
			assert(ok);

			resultValue.offset[i - m_startRowCount - 1] = value;
		}

		return std::shared_ptr<TVariate>(new TRefSys({ scope, name }, resultValue));
	}

	void WidgetManagerNewRefSys::InitParameter()
	{
		m_tableWidget->setRowCount(m_startRowCount + 7);
		m_tableWidget->setCellWidget(m_startRowCount, 0, new QLabel(QObject::tr("Base Sys")));

		m_tableWidget->setCellWidget(m_startRowCount, 1, new QComboBox);

		QStringList offsets{ "x", "y", "z", "a", "b", "c" };

		for (int i = 1; i < 7; ++i)
		{
			m_tableWidget->setCellWidget(m_startRowCount + i, 0, new QLabel(offsets[i - 1]));
			m_tableWidget->setCellWidget(m_startRowCount + i, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		}
	}

	void WidgetManagerNewRefSys::OnScopeChanged(const QString& scope)
	{
		VariateWidgetProducer producer;
		auto box = static_cast<QComboBox*>(m_tableWidget->cellWidget(m_startRowCount, 1));
		producer.UpdateComboBoxWithWholeName(TSymbol::TYPE_REF_SYS,
			std::move(TVariateManager::GetInstance()->GetVariatesMapScollUp(scope)), box);
		box->setCurrentText("WORLD");

	}

}