#include "stdafx.h"
#include "ScreenReferenceSystem.h"
#include "Button.h"
#include "VariateWidgetProducer.h"
#include "TVariateManager.h"
#include "Context.h"
#include "TRefSys.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include "DialogTeachReferenceSystem.h"
#include <chrono>
#include "QMessageBox"
#include <assert.h>


ScreenReferenceSystem::ScreenReferenceSystem(QWidget* parent/*=nullptr*/)
	:InternationalWidget(parent)
	, m_variateWidgetProducer(new VariateWidgetProducer)
{
	Init();
}

/*************************************************
//  Method:        ScreenReferenceSystem::showEvent(QShowEvent *)
//  Description:   显示界面时更新当前坐标系信息
//  Author:        刘巍 
//  Date:          2016/11/15
//  Returns:       
//  Parameter:     
//  History:
*************************************************/
void ScreenReferenceSystem::showEvent(QShowEvent *)
{

	disconnect(m_comboBoxRefSys, &QComboBox::currentTextChanged, this, &ScreenReferenceSystem::OnRefSysChanged);	/*断开信号连接，以便更新数据*/

	auto variatesMap = std::move(TVariateManager::GetInstance()->GetVariatesMapScollUp(Context::projectContext.CurrentScope()));

	//auto startTime = std::chrono::steady_clock::now();

	/*考虑到不同作用域内可能存在同名坐标系，故在组合框中显示坐标系名时，同时显示作用域名*/
	m_variateWidgetProducer->UpdateComboBoxWithWholeName(TSymbol::SymbolType::TYPE_REF_SYS, variatesMap, m_comboBoxRefSys);
	m_variateWidgetProducer->UpdateComboBoxWithWholeName(TSymbol::SymbolType::TYPE_REF_SYS, variatesMap, m_comboBoxBaseSys);

	//auto endTime = std::chrono::steady_clock::now();
	//qDebug() << "use time" << std::chrono::duration_cast<std::chrono::milliseconds>(endTime - startTime).count();

	OnRefSysChanged();	/*更新参考坐标系的基坐标系*/

	connect(m_comboBoxRefSys, &QComboBox::currentTextChanged, this, &ScreenReferenceSystem::OnRefSysChanged);	/*重新建立连接*/


}

void ScreenReferenceSystem::UpdateText()
{
	m_offsetBox->setTitle(tr("Offset"));
	m_systemBox->setTitle(tr("Coordinate System"));
	m_tcpValueBox->setTitle(tr("Tcp Values"));

	m_btnSave->setText(tr("Save"));
	m_btnAdd->setText(tr("Add"));
	m_btnDelete->setText(tr("Delete"));
	m_btnEdit->setText(tr("Edit"));

	m_lbRefSys->setText(tr("Reference Coordinate System"));
	m_lbBaseSys->setText(tr("Base Coordinate System"));

	m_lbTcpValuesIllustrate->setText(tr("Actual Tcp values of robot in this reference system"));
	m_lbOffsetValuesIllustrate->setText(tr("Position and orientation offset relative to base"));
}

QWidget* ScreenReferenceSystem::GetOffsetDataWidget()
{
	m_offsetBox = new QGroupBox(this);

	QVBoxLayout* layout = new QVBoxLayout(m_offsetBox);

	m_lbOffsetValuesIllustrate = GetValuesIllustrateWidget();
	layout->addWidget(m_lbOffsetValuesIllustrate);

	for (auto& lineEdit:m_ltOffsetValues)
	{
		lineEdit = new LineEditWithRegExpAndKeyboard("",RegExp::STR_REG_FLOAT,this);
		//connect(lineEdit, &QLineEdit::textChanged, this, &ScreenReferenceSystem::OnDataChanged);
	}

	layout->addLayout(GetValuesWidget(m_ltOffsetValues,true));
	layout->setStretch(1, 1);

	return m_offsetBox;
}

QWidget* ScreenReferenceSystem::GetSystemWidget()
{
	m_systemBox = new QGroupBox(this);

	QGridLayout* layout = new QGridLayout(m_systemBox);

	m_lbRefSys = new QLabel(this);
	m_lbRefSys->setAlignment(Qt::AlignCenter);
	m_comboBoxRefSys = new QComboBox(this);

	m_lbBaseSys = new QLabel(this);
	m_lbBaseSys->setAlignment(Qt::AlignCenter);
	m_comboBoxBaseSys = new QComboBox(this);
	m_comboBoxBaseSys->addItem("");	/*添加空的基坐标系，部分坐标系无基坐标系*/
	m_comboBoxBaseSys->setEnabled(false);	/*禁止修改基坐标系*/

	layout->addWidget(m_lbRefSys, 0, 0);
	layout->addWidget(m_comboBoxRefSys, 0, 1);
	layout->addWidget(m_lbBaseSys, 1, 0);
	layout->addWidget(m_comboBoxBaseSys, 1, 1);

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

inline
TRefSys* ScreenReferenceSystem::GetVariate()
{
	return static_cast<TRefSys*>(TVariateManager::GetInstance()->GetVariateSrollUp(GetVariateScope(), GetVariateName()));	/*获取当前参考坐标系变量*/
}

inline
QString ScreenReferenceSystem::GetVariateName()
{
	auto wholeName = m_comboBoxRefSys->currentText();
	auto nameList = wholeName.split(".");

	assert(nameList.size() > 1);
	return nameList.at(nameList.size() - 1);
}

inline
QString ScreenReferenceSystem::GetVariateScope()
{
	auto wholeName = m_comboBoxRefSys->currentText();
	return wholeName.left(wholeName.size() - GetVariateName().size() - 1);
}

QWidget* ScreenReferenceSystem::GetButtonWidget()
{
	QWidget* widget = new QWidget(this);
	QHBoxLayout* layout = new QHBoxLayout(widget);

	m_btnSave = new Button(this);
	m_btnAdd = new Button(this);
	m_btnDelete = new Button(this);
	m_btnEdit = new Button(this);

	layout->addWidget(m_btnAdd);
	layout->addWidget(m_btnEdit);
	layout->addWidget(m_btnDelete);
	layout->addWidget(m_btnSave);

	connect(m_btnSave, &QPushButton::clicked, this, &ScreenReferenceSystem::OnSaveButtonClicked);
	connect(m_btnAdd, &QPushButton::clicked, this, &ScreenReferenceSystem::OnAddButtonClicked);
	connect(m_btnDelete, &QPushButton::clicked, this, &ScreenReferenceSystem::OnDeleteButtonClicked);
	connect(m_btnEdit, &QPushButton::clicked, this, &ScreenReferenceSystem::OnEditButtonClicked);

	return widget;
}

void ScreenReferenceSystem::Init()
{
	QGridLayout* layout = new QGridLayout(this);

	layout->addWidget(GetSystemWidget(), 0, 0, 1, 2);
	layout->addWidget(GetOffsetDataWidget(), 1, 0);
	layout->addWidget(GetTcpValueWidget(), 1, 1);
	layout->addWidget(GetButtonWidget(), 2, 0, 1, 2);
	layout->setColumnStretch(0, 1);
	layout->setColumnStretch(1, 1);

	layout->setRowStretch(1, 1);

	UpdateText();

}

void ScreenReferenceSystem::OnAddButtonClicked()
{
	QMessageBox::warning(this, "",tr("not implement"));
}

void ScreenReferenceSystem::OnEditButtonClicked()
{
	(new DialogTeachReferenceSystem(GetVariate(),this))->show();
}

void ScreenReferenceSystem::OnDeleteButtonClicked()
{
	QMessageBox::warning(this, "", tr("not implement"));
}

void ScreenReferenceSystem::OnSaveButtonClicked()
{
	TRefSys::ValueType value;
	value.baseSys = m_comboBoxBaseSys->currentText();

	for (size_t i = 0; i < value.offset.size(); ++i)
	{
		value.offset[i] = m_ltOffsetValues[i]->text().toDouble();
	}

	auto variate = TVariateManager::GetInstance()->GetVariateSrollUp(GetVariateScope(), GetVariateName());
	TVariateManager::GetInstance()->UpdateVariate(variate->GetScope(), variate->GetName(), TRefSys{ variate->GetScope(), variate->GetName(), value });
}

void ScreenReferenceSystem::OnRefSysChanged()
{
	auto variate = GetVariate();
	assert(variate != nullptr);
	m_comboBoxBaseSys->setCurrentText(variate->GetValue().baseSys);	/*设置基坐标系*/

	auto variateValue = variate->GetValue();
	for (size_t i = 0; i <variateValue.offset.size(); ++i)
	{
		auto value = QString::number(variateValue.offset[i]);
		m_ltOffsetValues[i]->setText(value);
	}
}
