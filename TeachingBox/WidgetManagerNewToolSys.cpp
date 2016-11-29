#include "stdafx.h"
#include "WidgetManagerNewToolSys.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include "TToolSys.h"
#include <assert.h>



namespace VariateWidget
{

	WidgetManagerNewToolSys::WidgetManagerNewToolSys(QTableWidget* tableWidget, int startRowCount)
		:WidgetManagerNewVariate(tableWidget,startRowCount)
	{

	}

	WidgetManagerNewToolSys::~WidgetManagerNewToolSys()
	{

	}

	std::unique_ptr<TVariate> WidgetManagerNewToolSys::GetVariate(const QString& name, const QString& scope)
	{
		TToolSys::ValueType resultValue{};

		assert(m_tableWidget->rowCount() == m_startRowCount + 6);
		for (int i = m_startRowCount; i < m_startRowCount + 6; ++i)
		{
			QString valueString = dynamic_cast<QLineEdit*>(m_tableWidget->cellWidget(i, 1))->text();

			bool ok;
			double value = valueString.toDouble(&ok);
			assert(ok);

			resultValue[i - m_startRowCount] = value;
		}


		return std::unique_ptr<TVariate>(new TToolSys({scope, name}, resultValue));
	}

	void WidgetManagerNewToolSys::InitParameter()
	{
		m_tableWidget->setRowCount(m_startRowCount + 6);

		QStringList offsets{ "x", "y", "z", "a", "b", "c" };
		for (int i = 0; i < 6; ++i)
		{
			m_tableWidget->setCellWidget(m_startRowCount + i, 0, new QLabel(offsets[i]));
			m_tableWidget->setCellWidget(m_startRowCount + i, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		}
	}

}