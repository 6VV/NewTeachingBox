﻿#include "stdafx.h"
#include "ScreenReferenceSystem.h"
#include "Button.h"
#include "VariateWidgetProducer.h"
#include "TVariateManager.h"
#include "Context.h"
#include "TRefSys.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include <chrono>
#include "QMessageBox"
#include <assert.h>
#include "CoordinateContext.h"
#include "RefSysDialog.h"
#include "TeachingBoxInitialization.h"


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
	UpdateWidgetState();
}

void ScreenReferenceSystem::UpdateText()
{
	m_offsetBox->setTitle(tr("Offset"));
	m_systemBox->setTitle(tr("Coordinate System"));
	m_tcpValueBox->setTitle(tr("Tcp Values"));

	m_btnSave->setText(tr("Save"));
	m_btnDelete->setText(tr("Delete"));
	m_btnEdit->setText(tr("Edit"));

	m_lbRefSys->setText(tr("Reference Coordinate System"));
	m_lbBaseSys->setText(tr("Base Coordinate System"));

	m_lbTcpValuesIllustrate->setText(tr("Actual Tcp values of robot in this reference system"));
	m_lbOffsetValuesIllustrate->setText(tr("Position and orientation offset relative to base"));
}

QWidget* ScreenReferenceSystem::InitOffsetDataWidget()
{
	m_offsetBox = new QGroupBox(this);

	QVBoxLayout* layout = new QVBoxLayout(m_offsetBox);

	m_lbOffsetValuesIllustrate = InitValuesIllustrateWidget();
	layout->addWidget(m_lbOffsetValuesIllustrate);

	for (auto& lineEdit:m_ltOffsetValues)
	{
		lineEdit = new LineEditWithRegExpAndKeyboard("",RegExp::STR_REG_FLOAT,this);
		//connect(lineEdit, &QLineEdit::textChanged, this, &ScreenReferenceSystem::OnDataChanged);
	}

	layout->addLayout(InitValuesWidget(m_ltOffsetValues,true));
	layout->setStretch(1, 1);

	return m_offsetBox;
}

QWidget* ScreenReferenceSystem::InitSystemWidget()
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

QWidget* ScreenReferenceSystem::InitTcpValueWidget()
{
	m_tcpValueBox = new QGroupBox(this);

	QVBoxLayout* layout = new QVBoxLayout(m_tcpValueBox);

	m_lbTcpValuesIllustrate = InitValuesIllustrateWidget();
	layout->addWidget(m_lbTcpValuesIllustrate);

	for (auto& lineEdit: m_ltTcpValues)
	{
		lineEdit = new QLineEdit(this);
	}
	layout->addLayout(InitValuesWidget(m_ltTcpValues, false));
	layout->setStretch(1, 1);

	return m_tcpValueBox;
}

QLayout* ScreenReferenceSystem::InitValuesWidget(std::array<QLineEdit*, 6> widgets, bool enabled)
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

QLabel* ScreenReferenceSystem::InitValuesIllustrateWidget()
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
	return std::static_pointer_cast<TRefSys>(TVariateManager::GetInstance()->GetVariateSrollUp(GetVariateScope(), GetVariateName())).get();	/*获取当前参考坐标系变量*/
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

QWidget* ScreenReferenceSystem::InitButtonWidget()
{
	QWidget* widget = new QWidget(this);
	QHBoxLayout* layout = new QHBoxLayout(widget);

	m_btnSave = new Button(this);
	m_btnDelete = new Button(this);
	m_btnEdit = new Button(this);

	layout->addWidget(m_btnEdit);
	layout->addWidget(m_btnDelete);
	layout->addWidget(m_btnSave);

	connect(m_btnSave, &QPushButton::clicked, this, &ScreenReferenceSystem::OnSaveButtonClicked);
	connect(m_btnDelete, &QPushButton::clicked, this, &ScreenReferenceSystem::OnDeleteButtonClicked);
	connect(m_btnEdit, &QPushButton::clicked, this, &ScreenReferenceSystem::OnEditButtonClicked);

	return widget;
}

void ScreenReferenceSystem::Init()
{
	QGridLayout* layout = new QGridLayout(this);

	layout->addWidget(InitSystemWidget(), 0, 0, 1, 2);
	layout->addWidget(InitOffsetDataWidget(), 1, 0);
	layout->addWidget(InitTcpValueWidget(), 1, 1);
	layout->addWidget(InitButtonWidget(), 2, 0, 1, 2);
	layout->setColumnStretch(0, 1);
	layout->setColumnStretch(1, 1);

	layout->setRowStretch(1, 1);

	UpdateText();
}


void ScreenReferenceSystem::OnEditButtonClicked()
{
	auto variate = GetVariate();
	if (variate==nullptr)
	{
	}
	(new RefSysDialog(variate, this, this))->show();
}

void ScreenReferenceSystem::OnDeleteButtonClicked()
{
	auto variate = GetVariate();

	if (variate==nullptr)
	{
		return;
	}

	/*若为世界坐标系*/
	if (variate->GetScope()==TeachingBoxInitialization::WorldRefSys()->GetScope()
		|| variate->GetName()==TeachingBoxInitialization::WorldRefSys()->GetName())
	{
		QMessageBox::warning(this, tr("Operator failed"), tr("Cann't delete variate: ") + variate->GetScope()+"."+variate->GetName());
		return;
	}

	switch (QMessageBox::information(this, tr("Delete variate"), tr("Delete variate: ")+variate->GetName(), QMessageBox::Ok | QMessageBox::Cancel))
	{
	case QMessageBox::Ok:{
		TVariateManager::GetInstance()->DeleteVariate(variate->GetScope(), variate->GetName());
		UpdateWidgetState();
	}break;
	default:
		break;
	}
}

void ScreenReferenceSystem::OnSaveButtonClicked()
{
	auto variate = GetVariate();
	if (variate==nullptr)
	{
		return;
	}

	TRefSys::ValueType value{};
	//value.baseSys = m_comboBoxBaseSys->currentText();

	for (size_t i = 0; i < value.size(); ++i)
	{
		value[i] = m_ltOffsetValues[i]->text().toDouble();
	}

	TVariateManager::GetInstance()->UpdateVariate(std::shared_ptr<TVariate>(new TRefSys{ {variate->GetScope(), variate->GetName()}, value }));
}

void ScreenReferenceSystem::OnRefSysChanged()
{
	auto variate = GetVariate();
	assert(variate != nullptr);

	auto variateValue = variate->GetValue();
	for (size_t i = 0; i <variateValue.size(); ++i)
	{
		auto value = QString::number(variateValue[i]);
		m_ltOffsetValues[i]->setText(value);
	}
}

void ScreenReferenceSystem::UpdateWidgetState()
{
	disconnect(m_comboBoxRefSys, &QComboBox::currentTextChanged, this, &ScreenReferenceSystem::OnRefSysChanged);	/*断开连接*/

	auto variatesMap = std::move(TVariateManager::GetInstance()->GetAllVariatesMapScollUp(Context::projectContext.CurrentScope()));

	/*考虑到不同作用域内可能存在同名坐标系，故在组合框中显示坐标系名时，同时显示作用域名*/
	m_variateWidgetProducer->UpdateComboBoxWithWholeName(TRefSys::TypeName(), variatesMap, m_comboBoxRefSys);
	m_variateWidgetProducer->UpdateComboBoxWithWholeName(TRefSys::TypeName(), variatesMap, m_comboBoxBaseSys);
	m_comboBoxBaseSys->setCurrentText(ProjectContext::ScopeSystem() + "." + CoordinateContext::WorldRefSysName());

	OnRefSysChanged();	/*更新参考坐标系的基坐标系*/

	connect(m_comboBoxRefSys, &QComboBox::currentTextChanged, this, &ScreenReferenceSystem::OnRefSysChanged);	/*重新建立连接*/
}

void ScreenReferenceSystem::OnReceive(const tPoseEuler& poseEuler)
{
	m_ltOffsetValues[0]->setText(QString::number(poseEuler.m_PositionCartesian.m_X));
	m_ltOffsetValues[1]->setText(QString::number(poseEuler.m_PositionCartesian.m_Y));
	m_ltOffsetValues[2]->setText(QString::number(poseEuler.m_PositionCartesian.m_Z));
	m_ltOffsetValues[3]->setText(QString::number(poseEuler.m_PostureEuler.m_A));
	m_ltOffsetValues[4]->setText(QString::number(poseEuler.m_PostureEuler.m_B));
	m_ltOffsetValues[5]->setText(QString::number(poseEuler.m_PostureEuler.m_C));

	TRefSys::ValueType value{};
	value[0] = poseEuler.m_PositionCartesian.m_X;
	value[1] = poseEuler.m_PositionCartesian.m_Y;
	value[2] = poseEuler.m_PositionCartesian.m_Z;
	value[3] = poseEuler.m_PostureEuler.m_A;
	value[4] = poseEuler.m_PostureEuler.m_B;
	value[5] = poseEuler.m_PostureEuler.m_C;

	GetVariate()->SetValue(value);
}
