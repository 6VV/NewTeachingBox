#include "stdafx.h"
#include "ScreenReferenceSystem.h"
#include "Button.h"
#include "VariateWidgetProducer.h"
#include "ComboBoxWithParentTreeItem.h"
#include "TVariateManager.h"
#include "Context.h"
#include "TRefSys.h"
#include "LineEditWithRegExpAndKeyboard.h"


ScreenReferenceSystem::ScreenReferenceSystem(QWidget* parent/*=nullptr*/)
	:InternationalWidget(parent)
	, m_variateWidgetProducer(new VariateWidgetProducer)
	, m_btnAdd(new Button(this))
	, m_btnDelete(new Button(this))
	, m_btnEdit(new Button(this))
{
	Init();
}

void ScreenReferenceSystem::UpdateText()
{
	m_offsetBox->setTitle(tr("Offset"));
	m_systemBox->setTitle(tr("Coordinate System"));
	m_tcpValueBox->setTitle(tr("Tcp Values"));

	m_btnAdd->setText(tr("Add"));
	m_btnDelete->setText(tr("Delete"));
	m_btnEdit->setText(tr("Edit"));

	m_lbRefSys->setText(tr("Reference Coordinate System"));
	m_lbBaseSys->setText(tr("Base Coordinate System"));

	m_lbTcpValuesIllustrate->setText(tr("Actual Tcp values of robot in this reference system"));
	m_lbOffsetValuesIllustrate->setText(tr("Position and orientation offset relative to base"));
}

QWidget* ScreenReferenceSystem::GetDataWidget()
{
	m_offsetBox = new QGroupBox(this);

	QVBoxLayout* layout = new QVBoxLayout(m_offsetBox);

	m_lbOffsetValuesIllustrate = GetValuesIllustrateWidget();
	layout->addWidget(m_lbOffsetValuesIllustrate);

	for (auto& lineEdit:m_ltOffsetValues)
	{
		lineEdit = new LineEditWithRegExpAndKeyboard("",RegExp::STR_REG_FLOAT,this);
	}

	layout->addLayout(GetValuesWidget(m_ltOffsetValues,true));
	layout->setStretch(1, 1);

	return m_offsetBox;
}

QWidget* ScreenReferenceSystem::GetSystemWidget()
{
	m_systemBox = new QGroupBox(this);

	QGridLayout* layout = new QGridLayout(m_systemBox);

	auto variatesMap = std::move(TVariateManager::GetInstance()->GetVariatesMapFromScope(GetCurrentScope()));

	m_lbRefSys = new QLabel(this);
	m_lbRefSys->setAlignment(Qt::AlignCenter);
	m_comboBoxRefSys = m_variateWidgetProducer->GetComboBox(TSymbol::SymbolType::TYPE_REF_SYS, variatesMap);	/*获取参考坐标系ComboBox*/

	m_lbBaseSys = new QLabel(this);
	m_lbBaseSys->setAlignment(Qt::AlignCenter);
	m_comboBoxBaseSys = m_variateWidgetProducer->GetComboBox(TSymbol::SymbolType::TYPE_REF_SYS, variatesMap);
	m_comboBoxBaseSys->addItem("");	/*添加空的基坐标系，部分坐标系无基坐标系*/
	m_comboBoxBaseSys->setEnabled(false);	/*禁止修改基坐标系*/

	layout->addWidget(m_lbRefSys, 0, 0);
	layout->addWidget(m_comboBoxRefSys, 0, 1);
	layout->addWidget(m_lbBaseSys, 1, 0);
	layout->addWidget(m_comboBoxBaseSys, 1, 1);

	OnRefSysChanged();	/*更新参考坐标系的基坐标系*/
	connect(m_comboBoxRefSys, &QComboBox::currentTextChanged, this, &ScreenReferenceSystem::OnRefSysChanged);

	return m_systemBox;
}

QWidget* ScreenReferenceSystem::GetTcpValueWidget()
{
	m_tcpValueBox = new QGroupBox(this);

	QVBoxLayout* layout = new QVBoxLayout(m_tcpValueBox);

	m_lbTcpValuesIllustrate = GetValuesIllustrateWidget();
	layout->addWidget(m_lbTcpValuesIllustrate);

	for (auto& lineEdit: m_ltTcpValues)
	{
		lineEdit = new QLineEdit(this);
	}
	layout->addLayout(GetValuesWidget(m_ltTcpValues, false));
	layout->setStretch(1, 1);

	return m_tcpValueBox;
}

QLayout* ScreenReferenceSystem::GetValuesWidget(std::array<QLineEdit*, 6> widgets, bool enabled)
{
	for (auto lineEdit : widgets)
	{
		lineEdit->setText("0.00");
		lineEdit->setEnabled(enabled);
	}

	QGridLayout* layout = new QGridLayout(this);

	layout->addWidget(new QLabel("X"), 0, 0);
	layout->addWidget(widgets[0], 0, 1);
	layout->addWidget(new QLabel("mm"), 0, 2);

	layout->addWidget(new QLabel("Y"), 1, 0);
	layout->addWidget(widgets[1], 1, 1);
	layout->addWidget(new QLabel("mm"), 1, 2);

	layout->addWidget(new QLabel("Z"), 2, 0);
	layout->addWidget(widgets[2], 2, 1);
	layout->addWidget(new QLabel("mm"), 2, 2);

	layout->addWidget(new QLabel("A"), 3, 0);
	layout->addWidget(widgets[3], 3, 1);
	layout->addWidget(new QLabel(QStringLiteral("°")), 3, 2);

	layout->addWidget(new QLabel("B"), 4, 0);
	layout->addWidget(widgets[4], 4, 1);
	layout->addWidget(new QLabel(QStringLiteral("°")), 4, 2);

	layout->addWidget(new QLabel("C"), 5, 0);
	layout->addWidget(widgets[5], 5, 1);
	layout->addWidget(new QLabel(QStringLiteral("°")), 5, 2);

	return layout;
}

QLabel* ScreenReferenceSystem::GetValuesIllustrateWidget()
{
	QLabel* textEdit = new QLabel(this);
	textEdit->setEnabled(false);
	textEdit->setStyleSheet("QLabel{border:0px}");
	textEdit->setAlignment(Qt::AlignCenter);

	return textEdit;
}

QString ScreenReferenceSystem::GetCurrentScope()
{
	auto scope = Context::projectContext.ProgramOpened();
	if (scope.isEmpty())
	{
		scope = Context::projectContext.GetProjectLoaded();
		if (scope.isEmpty())
		{
			scope = Context::projectContext.ScopeGlobal();
		}
	}

	return scope;
}

QLayout* ScreenReferenceSystem::GetButtonLayout()
{
	QHBoxLayout* layout = new QHBoxLayout(this);

	layout->addWidget(m_btnAdd);
	layout->addWidget(m_btnEdit);
	layout->addWidget(m_btnDelete);

	connect(m_btnAdd, &QPushButton::clicked, this, &ScreenReferenceSystem::OnAddButtonClicked);
	connect(m_btnDelete, &QPushButton::clicked, this, &ScreenReferenceSystem::OnDeleteButtonClicked);
	connect(m_btnEdit, &QPushButton::clicked, this, &ScreenReferenceSystem::OnEditButtonClicked);

	return layout;
}

void ScreenReferenceSystem::Init()
{
	QGridLayout* layout = new QGridLayout(this);

	layout->addWidget(GetSystemWidget(), 0, 0, 1, 2);
	layout->addWidget(GetDataWidget(), 1, 0);
	layout->addWidget(GetTcpValueWidget(), 1, 1);
	layout->addLayout(GetButtonLayout(), 2, 0, 1, 2);
	layout->setColumnStretch(0, 1);
	layout->setColumnStretch(1, 1);

	layout->setRowStretch(1, 1);

	UpdateText();
}

void ScreenReferenceSystem::OnAddButtonClicked()
{

}

void ScreenReferenceSystem::OnEditButtonClicked()
{

}

void ScreenReferenceSystem::OnDeleteButtonClicked()
{

}


void ScreenReferenceSystem::OnRefSysChanged()
{
	auto variate = static_cast<TRefSys*>(TVariateManager::GetInstance()->GetVariateSrollUp(GetCurrentScope(), 
		m_comboBoxRefSys->currentText()));	/*获取当前参考坐标系变量*/

	m_comboBoxBaseSys->setCurrentText(variate->GetValue().baseSys);	/*设置基坐标系*/
}
