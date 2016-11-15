#include "stdafx.h"
#include "VariateTableManager.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include "Context.h"
#include "TVariateType.h"
#include "WarningManager.h"
#include "WidgetManagerNewVariateFactory.h"
#include "WidgetManagerNewVariate.h"

namespace VariateWidget{

	VariateTableManager::VariateTableManager(QWidget* parent)
	{
		m_tableWidget = new QTableWidget(parent);
		m_tableWidget->setColumnCount(COLUMN_NUM);
		m_tableWidget->setRowCount(INIT_ROW_NUM);
		m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
		//m_tableWidget->verticalHeader()->setVisible(false);

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

		return m_currentWidgetManager->GetVariate(name, scope);

	}

	void VariateTableManager::ChangeToType(const QString& type)
	{
		m_comboBoxType->setCurrentText(type);

		m_currentWidgetManager = GetWidgetManager(type);
		m_currentWidgetManager->InitParameter();

		m_currentWidgetManager->OnScopeChanged(m_comboBoxScope->currentText());
		connect(m_comboBoxScope, &QComboBox::currentTextChanged, m_currentWidgetManager.get(), &WidgetManagerNewVariate::OnScopeChanged);
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

	inline
	std::unique_ptr<WidgetManagerNewVariate> VariateTableManager::GetWidgetManager(const QString& type) const
	{
		return std::unique_ptr<WidgetManagerNewVariate>(WidgetManagerNewVariateFactory::CreateWidgetManagerNewVariate(type, m_tableWidget, INIT_ROW_NUM));
	}

}