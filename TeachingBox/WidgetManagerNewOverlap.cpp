#include "stdafx.h"
#include "WidgetManagerNewOverlap.h"
#include "DataStruct.h"
#include "TVariateType.h"
#include "TOverlap.h"
#include "LineEditWithRegExpAndKeyboard.h"



namespace VariateWidget
{

	WidgetManagerNewOverlap::WidgetManagerNewOverlap(QTableWidget* tableWidget, int startRowCount)
		:WidgetManagerNewVariate(tableWidget,startRowCount)
	{

	}

	WidgetManagerNewOverlap::~WidgetManagerNewOverlap()
	{

	}

	std::shared_ptr<TVariate> WidgetManagerNewOverlap::GetVariate(const QString& name, const QString& scope)
	{
		QString valueString = dynamic_cast<QLineEdit*>(m_tableWidget->cellWidget(m_startRowCount + 1, 1))->text();

		bool ok;
		double value = valueString.toDouble(&ok);
		if (!ok)
		{
			return nullptr;
		}

		tOverlapConstraint overlap;
		overlap.m_TransitionParameter = value;

		QString mode = dynamic_cast<QComboBox*>(m_tableWidget->cellWidget(m_startRowCount, 1))->currentText();
		if (mode == TVariateType::STR_TRANSITION_MODE_ABSOLUTE)
		{
			overlap.m_TransitionMode = static_cast<int>(tTransitionMode::kTransitionModeAbsolute);
		}
		else
		{
			overlap.m_TransitionMode = static_cast<int>(tTransitionMode::kTransitionModeRelative);
		}

		return std::shared_ptr<TVariate>(new TOverlap({ scope, name }, overlap));
	}

	void WidgetManagerNewOverlap::InitParameter()
	{
		m_tableWidget->setRowCount(m_startRowCount + 2);
		m_tableWidget->setCellWidget(m_startRowCount, 0, new QLabel(QObject::tr("Mode")));
		m_tableWidget->setCellWidget(m_startRowCount + 1, 0, new QLabel(QObject::tr("Value")));

		QComboBox* comboBoxMode = new QComboBox;
		comboBoxMode->addItem(TVariateType::STR_TRANSITION_MODE_RELATIVE);
		comboBoxMode->addItem(TVariateType::STR_TRANSITION_MODE_ABSOLUTE);
		QLineEdit* lineEdit = new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT);

		m_tableWidget->setCellWidget(m_startRowCount, 1, comboBoxMode);
		m_tableWidget->setCellWidget(m_startRowCount + 1, 1, lineEdit);
	}

}