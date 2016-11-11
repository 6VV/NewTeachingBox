#include "stdafx.h"
#include "VariateTableManager.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include "TVariateType.h"
#include "TVariate.h"
#include "WarningManager.h"
#include "QRegExp"
#include "TInteger.h"
#include "TDouble.h"
#include "TBool.h"
#include "TString.h"
#include "DataStruct.h"
#include "TPosition.h"
#include "TDynamic.h"
#include "TOverlap.h"
#include "TScope.h"
#include "Context.h"

namespace VariateWidget{

	VariateTableManager::VariateTableManager(QWidget* parent)
	{
		m_tableWidget = new QTableWidget(parent);
		m_tableWidget->setColumnCount(COLUMN_NUM);
		m_tableWidget->setRowCount(INIT_ROW_NUM);
		m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

		QLabel* lbName = new QLabel(QObject::tr("Name"));
		QLabel* lbScope = new QLabel(QObject::tr("Scope"));
		QLabel* lbType = new QLabel(QObject::tr("Type"));

		m_lineEidtName = new LineEditWithRegExpAndKeyboard("", RegExp::STR_REG_STRING_NAME);

		m_comboBoxScope = new QComboBox;
		m_comboBoxScope->addItems(Context::projectContext.AllCurrentScopes());

		m_comboBoxType = new QComboBox;
		m_comboBoxType->addItems(TVariateType::TYPE_COLLECTION);

		m_tableWidget->setCellWidget(0, 0, lbName);
		m_tableWidget->setCellWidget(0, 1, m_lineEidtName);

		m_tableWidget->setCellWidget(1, 0, lbScope);
		m_tableWidget->setCellWidget(1, 1, m_comboBoxScope);

		m_tableWidget->setCellWidget(2, 0, lbType);
		m_tableWidget->setCellWidget(2, 1, m_comboBoxType);

		connect(m_comboBoxType, SIGNAL(currentIndexChanged(const QString&)), this, SLOT(ChangeToType(const QString&)));

		ChangeToType(m_comboBoxType->currentText());
	}

	QTableWidget* VariateTableManager::GetTableWidget(const QString& scope)
	{
		m_comboBoxScope->setCurrentText(scope);

		return m_tableWidget;
	}

	std::unique_ptr<TVariate> VariateTableManager::GetVariate()
	{
		/*若为无效名，则返回nullptr*/
		if (!IsValidName())
		{
			WarningManager::Warning(m_tableWidget, WarningManager::WrongName);

			return nullptr;
		}

		QString name = m_lineEidtName->text();
		QString scope = m_comboBoxScope->currentText();
		QString type = m_comboBoxType->currentText();

		/*若为Int类*/
		if (type == TVariateType::STR_TYPE_INT)
		{
			return GetInterger(name,scope);
		}
		/*若为Double类*/
		else if (type == TVariateType::STR_TYPE_DOUBLE)
		{
			return GetDouble(name, scope);
		}
		/*若为Bool类*/
		else if (type == TVariateType::STR_TYPE_BOOL)
		{
			return GetBool(name, scope);
		}
		/*若为String类*/
		else if (type == TVariateType::STR_TYPE_STRING)
		{
			return GetString(name, scope);
		}
		/*若为Position类*/
		else if (type == TVariateType::STR_TYPE_POSITION)
		{
			return GetPosition(name, scope);
		}
		/*若为Dynamic类*/
		else if (type == TVariateType::STR_TYPE_DYNAMIC)
		{
			return GetDynamic(name, scope);
		}
		/*若为Overlap类*/
		else if (type == TVariateType::STR_TYPE_OVERLAP)
		{
			return GetOverlap(name, scope);
		}
		else
		{
			return nullptr;
		}
	}

	void VariateTableManager::ChangeToType(const QString& type)
	{
		m_comboBoxType->setCurrentText(type);

		/*若为Int类*/
		if (type == TVariateType::STR_TYPE_INT)
		{
			InitIntParameter();
		}
		/*若为Double类*/
		else if (type == TVariateType::STR_TYPE_DOUBLE)
		{
			InitDoubleParameter();
		}
		/*若为Bool类*/
		else if (type == TVariateType::STR_TYPE_BOOL)
		{
			InitBoolParameter();
		}
		/*若为String类*/
		else if (type == TVariateType::STR_TYPE_STRING)
		{
			InitStringParameter();
		}
		/*若为Position类*/
		else if (type == TVariateType::STR_TYPE_POSITION)
		{
			InitPositionParameter();
		}
		/*若为Dynamic类*/
		else if (type == TVariateType::STR_TYPE_DYNAMIC)
		{
			InitDynamicParameter();
		}
		/*若为Overlap类*/
		else if (type == TVariateType::STR_TYPE_OVERLAP)
		{
			InitOverlapParameter();
		}
	}

	void VariateTableManager::UpdateText()
	{
		m_tableWidget->setHorizontalHeaderLabels(QStringList{ QObject::tr("Name"), QObject::tr("Value") });
	}

	bool VariateTableManager::IsValidVariate()
	{
		if (m_tableWidget->rowCount() <= INIT_ROW_NUM)
		{
			return false;
		}

		return true;
	}

	void VariateTableManager::InitIntParameter()
	{
		m_tableWidget->setRowCount(INIT_ROW_NUM + 1);
		QLabel* lbValue = new QLabel(QObject::tr("Value"));

		m_tableWidget->setCellWidget(INIT_ROW_NUM, 0, lbValue);
		m_tableWidget->setCellWidget(INIT_ROW_NUM, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_INT));
	}

	void VariateTableManager::InitDoubleParameter()
	{
		m_tableWidget->setRowCount(INIT_ROW_NUM + 1);
		QLabel* lbValue = new QLabel(QObject::tr("Value"));

		m_tableWidget->setCellWidget(INIT_ROW_NUM, 0, lbValue);
		m_tableWidget->setCellWidget(INIT_ROW_NUM, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
	}

	void VariateTableManager::InitBoolParameter()
	{
		m_tableWidget->setRowCount(INIT_ROW_NUM + 1);
		QLabel* lbValue = new QLabel(QObject::tr("Value"));
		QComboBox* cmbBool = new QComboBox;
		cmbBool->addItem(TVariateType::STR_BOOL_TRUE);
		cmbBool->addItem(TVariateType::STR_BOOL_FALSE);

		m_tableWidget->setCellWidget(INIT_ROW_NUM, 0, lbValue);
		m_tableWidget->setCellWidget(INIT_ROW_NUM, 1, cmbBool);
	}

	void VariateTableManager::InitStringParameter()
	{
		m_tableWidget->setRowCount(INIT_ROW_NUM + 1);
		QLabel* lbValue = new QLabel(QObject::tr("Value"));

		m_tableWidget->setCellWidget(INIT_ROW_NUM, 0, lbValue);
		m_tableWidget->setCellWidget(INIT_ROW_NUM, 1, new LineEditWithRegExpAndKeyboard());
	}

	void VariateTableManager::InitPositionParameter()
	{
		m_tableWidget->setRowCount(INIT_ROW_NUM + 6);
		QLabel* lbValue1 = new QLabel("Axis1");
		QLabel* lbValue2 = new QLabel("Axis2");
		QLabel* lbValue3 = new QLabel("Axis3");
		QLabel* lbValue4 = new QLabel("Axis4");
		QLabel* lbValue5 = new QLabel("Axis5");
		QLabel* lbValue6 = new QLabel("Axis6");


		m_tableWidget->setCellWidget(INIT_ROW_NUM, 0, lbValue1);
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 1, 0, lbValue2);
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 2, 0, lbValue3);
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 3, 0, lbValue4);
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 4, 0, lbValue5);
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 5, 0, lbValue6);

		m_tableWidget->setCellWidget(INIT_ROW_NUM, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 1, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 2, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 3, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 4, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 5, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
	}

	void VariateTableManager::InitDynamicParameter()
	{
		m_tableWidget->setRowCount(INIT_ROW_NUM + 6);
		m_tableWidget->setCellWidget(INIT_ROW_NUM, 0, new QLabel(QObject::tr("Velocity")));
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 1, 0, new QLabel(QObject::tr("Acceleration")));
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 2, 0, new QLabel(QObject::tr("Deceleration")));
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 3, 0, new QLabel(QObject::tr("PostureVelocity")));
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 4, 0, new QLabel(QObject::tr("PostureAcceleration")));
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 5, 0, new QLabel(QObject::tr("PostureDeceleration")));

		m_tableWidget->setCellWidget(INIT_ROW_NUM, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 1, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 2, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 3, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 4, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 5, 1, new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT));
	}

	void VariateTableManager::InitOverlapParameter()
	{
		m_tableWidget->setRowCount(INIT_ROW_NUM + 2);
		m_tableWidget->setCellWidget(INIT_ROW_NUM, 0, new QLabel(QObject::tr("Mode")));
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 1, 0, new QLabel(QObject::tr("Value")));

		QComboBox* comboBoxMode = new QComboBox;
		comboBoxMode->addItem(TVariateType::STR_TRANSITION_MODE_RELATIVE);
		comboBoxMode->addItem(TVariateType::STR_TRANSITION_MODE_ABSOLUTE);
		QLineEdit* lineEdit = new LineEditWithRegExpAndKeyboard("0", RegExp::STR_REG_FLOAT);

		m_tableWidget->setCellWidget(INIT_ROW_NUM, 1, comboBoxMode);
		m_tableWidget->setCellWidget(INIT_ROW_NUM + 1, 1, lineEdit);
	}

	bool VariateTableManager::IsValidName()
	{
		QString name = m_lineEidtName->text();
		QRegExp regExp(RegExp::STR_REG_STRING_NAME);

		if (name.isEmpty() || !regExp.exactMatch(name))
		{
			return false;
		}

		return true;
	}

	std::unique_ptr<TVariate> VariateTableManager::GetDouble(const QString& name, const QString& scope)
	{
		QString valueString = dynamic_cast<QLineEdit*>(m_tableWidget->cellWidget(INIT_ROW_NUM, 1))->text();

		bool ok;
		double value = valueString.toDouble(&ok);
		if (!ok)
		{
			return nullptr;
		}

		return std::unique_ptr<TVariate>(new TDouble(scope, name, value));
	}

	std::unique_ptr<TVariate> VariateTableManager::GetInterger(const QString& name, const QString& scope)
	{
		QString valueString = dynamic_cast<QLineEdit*>(m_tableWidget->cellWidget(INIT_ROW_NUM, 1))->text();
		
		bool ok;
		int value = valueString.toInt(&ok);
		if (!ok)
		{
			return nullptr;
		}

		return std::unique_ptr<TVariate>(new TInteger(scope, name, value));
	}

	std::unique_ptr<TVariate> VariateTableManager::GetBool(const QString& name, const QString& scope)
	{
		QString valueString = dynamic_cast<QComboBox*>(m_tableWidget->cellWidget(INIT_ROW_NUM, 1))->currentText();

		bool value = false;
		if (valueString==TVariateType::STR_BOOL_TRUE)
		{
			value = true;
		}

		return std::unique_ptr<TVariate>(new TBool(scope, name, value));
	}

	std::unique_ptr<TVariate> VariateTableManager::GetString(const QString& name, const QString& scope)
	{
		QString valueString = dynamic_cast<QLineEdit*>(m_tableWidget->cellWidget(INIT_ROW_NUM, 1))->text();

		return std::unique_ptr<TVariate>(new TString(scope, name, valueString));
	}

	std::unique_ptr<TVariate> VariateTableManager::GetPosition(const QString& name, const QString& scope)
	{
		tAxesAllPositions position;

		for (int i = INIT_ROW_NUM; i < INIT_ROW_NUM + AXIS_SIZE;++i)
		{
			QString valueString = dynamic_cast<QLineEdit*>(m_tableWidget->cellWidget(i, 1))->text();

			bool ok;
			double value = valueString.toDouble(&ok);
			if (!ok)
			{
				return nullptr;
			}
			position.m_AxisPosition[i - INIT_ROW_NUM] = value;
		}
		

		return std::unique_ptr<TVariate>(new TPosition(scope, name, position));
	}

	std::unique_ptr<TVariate> VariateTableManager::GetDynamic(const QString& name, const QString& scope)
	{
		double values[6]{};

		for (int i = INIT_ROW_NUM; i < INIT_ROW_NUM + AXIS_SIZE; ++i)
		{
			QString valueString = dynamic_cast<QLineEdit*>(m_tableWidget->cellWidget(i, 1))->text();

			bool ok;
			int value = valueString.toInt(&ok);
			if (!ok)
			{
				return nullptr;
			}
			values[i - INIT_ROW_NUM] = value;
		}
		tDynamicConstraint dynamic;
		dynamic.m_Velocity = values[0];
		dynamic.m_Acceleration = values[1];
		dynamic.m_Deceleration = values[2];
		dynamic.m_PostureVelocity = values[3];
		dynamic.m_PostureAcceleration = values[4];
		dynamic.m_PostureDeceleration = values[5];

		return std::unique_ptr<TVariate>(new TDynamic(scope, name, dynamic));
	}

	std::unique_ptr<TVariate> VariateTableManager::GetOverlap(const QString& name, const QString& scope)
	{
		QString valueString = dynamic_cast<QLineEdit*>(m_tableWidget->cellWidget(INIT_ROW_NUM+1, 1))->text();

		bool ok;
		double value = valueString.toDouble(&ok);
		if (!ok)
		{
			return nullptr;
		}

		tOverlapConstraint overlap;
		overlap.m_TransitionParameter = value;

		QString mode = dynamic_cast<QComboBox*>(m_tableWidget->cellWidget(INIT_ROW_NUM, 1))->currentText();
		if (mode==TVariateType::STR_TRANSITION_MODE_ABSOLUTE)
		{
			overlap.m_TransitionMode = static_cast<int>(tTransitionMode::kTransitionModeAbsolute);
		}
		else
		{
			overlap.m_TransitionMode = static_cast<int>(tTransitionMode::kTransitionModeRelative);
		}

		return std::unique_ptr<TVariate>(new TOverlap(scope, name, overlap));
	}

}