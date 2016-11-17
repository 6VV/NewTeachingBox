#include "stdafx.h"
#include "DialogTeachReferenceSystem.h"
#include "QBoxLayout"
#include "Button.h"
#include "TRefSys.h"
#include "QRadioButton"
#include "QLabel"
#include <assert.h>
#include "LineEditWithRegExpAndKeyboard.h"
#include "QMessageBox"
#include "VariateWidgetProducer.h"




DialogTeachReferenceSystem::DialogTeachReferenceSystem(TRefSys* oldVariate, QWidget* parent/*=nullptr*/)
	:DialogParent(parent)
	, m_controller(this,oldVariate)
{
	Init();
}

void DialogTeachReferenceSystem::UpdateText()
{
}

void DialogTeachReferenceSystem::Init()
{
	m_mainLayout = new QGridLayout(this);

	m_mainLayout->addWidget(GetReferenceSystemWidget(), 0, 0, 1, 2);
	m_currentWidget = OriginWidget();
	m_mainLayout->addWidget(m_currentWidget, 1, 0);
	m_mainLayout->addWidget(GetIllustrationWidget(), 1, 1);
	m_mainLayout->addLayout(GetButtonLayout(), 2, 0, 1, 2);

	m_mainLayout->setRowStretch(1, 1);
	m_mainLayout->setColumnStretch(0, 1);
	m_mainLayout->setColumnStretch(1, 1);

	UpdateText();

}

QWidget* DialogTeachReferenceSystem::OnePointKeepOrientationStep1()
{
	QWidget* widget = new QWidget(this);
	QHBoxLayout* layoutMain = new QHBoxLayout(widget);
	QGroupBox* groupBox = new QGroupBox(tr("Origin Point"), widget);
	layoutMain->addWidget(groupBox);

	QVBoxLayout* layout = new QVBoxLayout(groupBox);
	layout->addWidget(PointWidget());

	layout->setStretch(0, 1);

	return widget;
}

QWidget* DialogTeachReferenceSystem::OriginWidget()
{
	QWidget* widget = new QWidget(this);

	QVBoxLayout* layout = new QVBoxLayout(widget);

	layout->addWidget(GetTeachToolWidget());
	layout->addWidget(GetTeachMethodWidget());

	return widget;
}

QWidget* DialogTeachReferenceSystem::PointWidget()
{
	QWidget* widget = new QWidget(this);
	QGridLayout* layout = new QGridLayout(widget);

	auto ltX = new LineEditWithRegExpAndKeyboard("0.00",RegExp::STR_REG_FLOAT,widget);
	auto ltY = new LineEditWithRegExpAndKeyboard("0.00", RegExp::STR_REG_FLOAT, widget);
	auto ltZ = new LineEditWithRegExpAndKeyboard("0.00", RegExp::STR_REG_FLOAT, widget);

	ltX->setEnabled(false);
	ltY->setEnabled(false);
	ltZ->setEnabled(false);

	layout->addWidget(new QLabel("X"), 0, 0);
	layout->addWidget(ltX, 0, 1);
	layout->addWidget(new QLabel("mm"), 0, 2);

	layout->addWidget(new QLabel("Y"), 1, 0);
	layout->addWidget(ltY, 1, 1);
	layout->addWidget(new QLabel("mm"), 1, 2);

	layout->addWidget(new QLabel("Z"), 2, 0);
	layout->addWidget(ltZ, 2, 1);
	layout->addWidget(new QLabel("mm"), 2, 2);

	layout->addWidget(new QPushButton(tr("Teach")), 3, 0, 1, 3);

	return widget;
}

QWidget* DialogTeachReferenceSystem::ThreePointsWithOriginWidgetStep1()
{
	QWidget* widget = new QWidget(this);
	QHBoxLayout* layoutMain = new QHBoxLayout(widget);
	QGroupBox* groupBox = new QGroupBox(tr("Origin Point"), widget);
	layoutMain->addWidget(groupBox);

	QVBoxLayout* layout = new QVBoxLayout(groupBox);
	layout->addWidget(PointWidget());

	layout->setStretch(0, 1);

	return widget;
}

QWidget* DialogTeachReferenceSystem::ThreePointsWithOriginWidgetStep2()
{
	QWidget* widget = new QWidget(this);
	QHBoxLayout* layoutMain = new QHBoxLayout(widget);
	QGroupBox* groupBox = new QGroupBox(tr("Axis Point"), widget);

	layoutMain->addWidget(groupBox);

	QVBoxLayout* layout = new QVBoxLayout(groupBox);

	auto btnX = new QRadioButton("X", widget);
	auto btnY = new QRadioButton("Y", widget);
	auto btnZ = new QRadioButton("Z", widget);
	QHBoxLayout* radioLayout = new QHBoxLayout(widget);
	radioLayout->addWidget(btnX);
	radioLayout->addWidget(btnY);
	radioLayout->addWidget(btnZ);

	layout->addLayout(radioLayout);
	layout->addWidget(PointWidget());

	layout->setStretch(1, 1);

	return widget;
}

QWidget* DialogTeachReferenceSystem::ThreePointsWithOriginWidgetStep3()
{
	QWidget* widget = new QWidget(this);
	QHBoxLayout* layoutMain = new QHBoxLayout(widget);
	QGroupBox* groupBox = new QGroupBox(tr("Plane Point"), widget);

	layoutMain->addWidget(groupBox);

	QVBoxLayout* layout = new QVBoxLayout(groupBox);

	auto btnXY = new QRadioButton("XY", widget);
	auto btnZX = new QRadioButton("ZX", widget);
	auto btnYZ = new QRadioButton("YZ", widget);
	QHBoxLayout* radioLayout = new QHBoxLayout(widget);
	radioLayout->addWidget(btnXY);
	radioLayout->addWidget(btnZX);
	radioLayout->addWidget(btnYZ);

	layout->addLayout(radioLayout);
	layout->addWidget(PointWidget());

	layout->setStretch(1, 1);

	return widget;
}

QWidget* DialogTeachReferenceSystem::ThreePointsWithoutOriginWidgetStep1()
{
	QWidget* widget = new QWidget(this);
	QHBoxLayout* layoutMain = new QHBoxLayout(widget);
	QGroupBox* groupBox = new QGroupBox(tr("First point on axis"), widget);

	layoutMain->addWidget(groupBox);

	QVBoxLayout* layout = new QVBoxLayout(groupBox);

	auto btnX = new QRadioButton("X", widget);
	auto btnY = new QRadioButton("Y", widget);
	auto btnZ = new QRadioButton("Z", widget);
	QHBoxLayout* radioLayout = new QHBoxLayout(widget);
	radioLayout->addWidget(btnX);
	radioLayout->addWidget(btnY);
	radioLayout->addWidget(btnZ);

	layout->addLayout(radioLayout);
	layout->addWidget(PointWidget());

	layout->setStretch(1, 1);

	return widget;
}

QWidget* DialogTeachReferenceSystem::ThreePointsWithoutOriginWidgetStep2()
{
	QWidget* widget = new QWidget(this);
	QHBoxLayout* layoutMain = new QHBoxLayout(widget);
	QGroupBox* groupBox = new QGroupBox(tr("Second point on axis"), widget);
	layoutMain->addWidget(groupBox);

	QVBoxLayout* layout = new QVBoxLayout(groupBox);
	layout->addWidget(PointWidget());

	layout->setStretch(0, 1);

	return widget;
}

QWidget* DialogTeachReferenceSystem::ThreePointsWithoutOriginWidgetStep3()
{
	QWidget* widget = new QWidget(this);
	QHBoxLayout* layoutMain = new QHBoxLayout(widget);
	QGroupBox* groupBox = new QGroupBox(tr("Point on second axis"), widget);

	layoutMain->addWidget(groupBox);

	QVBoxLayout* layout = new QVBoxLayout(groupBox);

	auto btnX = new QRadioButton("X", widget);
	auto btnY = new QRadioButton("Y", widget);
	auto btnZ = new QRadioButton("Z", widget);
	QHBoxLayout* radioLayout = new QHBoxLayout(widget);
	radioLayout->addWidget(btnX);
	radioLayout->addWidget(btnY);
	radioLayout->addWidget(btnZ);

	layout->addLayout(radioLayout);
	layout->addWidget(PointWidget());

	layout->setStretch(1, 1);

	return widget;

}

QWidget* DialogTeachReferenceSystem::GetReferenceSystemWidget()
{
	QGroupBox* box = new QGroupBox(this);

	box->setTitle(tr("System"));
	QHBoxLayout* layout = new QHBoxLayout(box);

	QLabel* lbReference = new QLabel(tr("Reference System"), this);
	lbReference->setAlignment(Qt::AlignCenter);
	QComboBox* comboBoxReference = new QComboBox(this);
	comboBoxReference->addItem(QIcon(VariateWidgetProducer::GetIconPath(m_controller.m_oldVariate->GetScope())),
		m_controller.m_oldVariate->GetScope()+"."+m_controller.m_oldVariate->GetName());
	comboBoxReference->setEnabled(false);

	layout->addWidget(lbReference);
	layout->addWidget(comboBoxReference);

	return box;
}

QWidget* DialogTeachReferenceSystem::GetTeachMethodWidget()
{
	QGroupBox* box = new QGroupBox(tr("Select teach method"), this);

	QGridLayout* layout = new QGridLayout(box);

	QRadioButton* threePointsWithOriginButton = new QRadioButton(this);
	QRadioButton* threePointsWithoutOriginButton = new QRadioButton(this);
	QRadioButton* onePointWithOrientation = new QRadioButton(this);

	layout->addWidget(threePointsWithOriginButton, 0, 0);
	layout->addWidget(threePointsWithoutOriginButton, 1, 0);
	layout->addWidget(onePointWithOrientation, 2, 0);
	layout->addWidget(new QLabel(tr("3 points(with origin)")), 0, 1);
	layout->addWidget(new QLabel(tr("3 points(without origin)")), 1, 1);
	layout->addWidget(new QLabel(tr("1 points(keep orientation)")), 2, 1);

	layout->setColumnStretch(1, 1);

	QButtonGroup* buttonGroup = new QButtonGroup(this);
	buttonGroup->addButton(threePointsWithOriginButton, Controller::THREE_POINTS_WITH_ORIGIN);
	buttonGroup->addButton(threePointsWithoutOriginButton, Controller::THREE_POINTS_WITHOUT_ORIGIN);
	buttonGroup->addButton(onePointWithOrientation, Controller::ONE_POINT_KEEP_ORIENTATION);

	connect(buttonGroup, static_cast<void (QButtonGroup::*)(int)>(&QButtonGroup::buttonClicked),
		[this](int id){m_controller.m_teachMethod = static_cast<Controller::TeachMethod>(id); });

	threePointsWithOriginButton->setChecked(true);

	return box;
}

QWidget* DialogTeachReferenceSystem::GetTeachToolWidget()
{
	QGroupBox* box = new QGroupBox(tr("Tool for teaching"), this);

	return box;
}

QWidget* DialogTeachReferenceSystem::GetIllustrationWidget()
{
	QGroupBox* box = new QGroupBox(tr("Illustration"), this);

	return box;
}

QLayout* DialogTeachReferenceSystem::GetButtonLayout()
{
	QHBoxLayout* layout = new QHBoxLayout(this);

	auto btnNext = new Button(tr("Next"), this);
	auto btnPre = new Button(tr("Pre"), this);
	btnPre->setEnabled(false);
	auto btnCancle = new Button(tr("Cancle"), this);

	layout->addWidget(btnPre);
	layout->addWidget(btnNext);
	layout->addWidget(btnCancle);

	connect(btnNext, &QPushButton::clicked, [this, btnPre,btnNext]{
		m_controller.NextStep();

		btnPre->setEnabled(m_controller.HavePreStep());
		btnNext->setEnabled(m_controller.HaveNextStep());
	});

	connect(btnPre, &QPushButton::clicked, [this, btnPre, btnNext]{
		m_controller.PreStep();

		btnPre->setEnabled(m_controller.HavePreStep());
		btnNext->setEnabled(m_controller.HaveNextStep());
	});

	connect(btnCancle, &QPushButton::clicked, [this]{delete this; });

	return layout;
}


DialogTeachReferenceSystem::Controller::Controller(DialogTeachReferenceSystem* screenTeachReferenceSystem, TRefSys* variate)
	:m_screenTeachReferenceSystem(screenTeachReferenceSystem)
	,m_oldVariate(variate)
{
	m_stepMap.insert(Controller::THREE_POINTS_WITH_ORIGIN,
		{ &DialogTeachReferenceSystem::ThreePointsWithOriginWidgetStep1
		, &DialogTeachReferenceSystem::ThreePointsWithOriginWidgetStep2 
		, &DialogTeachReferenceSystem::ThreePointsWithOriginWidgetStep3 });

	m_stepMap.insert(Controller::THREE_POINTS_WITHOUT_ORIGIN, 
		{ &DialogTeachReferenceSystem::ThreePointsWithoutOriginWidgetStep1,
		  &DialogTeachReferenceSystem::ThreePointsWithoutOriginWidgetStep2 
		, &DialogTeachReferenceSystem::ThreePointsWithoutOriginWidgetStep3 });
	m_stepMap.insert(Controller::ONE_POINT_KEEP_ORIENTATION, { &DialogTeachReferenceSystem::OnePointKeepOrientationStep1 });
}

void DialogTeachReferenceSystem::Controller::NextStep()
{
	++m_step;

	if (!HaveNextStep())
	{
		switch (QMessageBox::warning(m_screenTeachReferenceSystem, "not implement", "", QMessageBox::Cancel))
		{
		case QMessageBox::Cancel:{
			return;
		}break;
		default:
			break;
		}
	}

	m_screenTeachReferenceSystem->m_mainLayout->removeWidget(m_screenTeachReferenceSystem->m_currentWidget);
	delete m_screenTeachReferenceSystem->m_currentWidget;

	m_screenTeachReferenceSystem->m_currentWidget = (m_screenTeachReferenceSystem->*m_stepMap[m_teachMethod][m_step])();
	m_screenTeachReferenceSystem->m_mainLayout->addWidget(m_screenTeachReferenceSystem->m_currentWidget, 1, 0);
}

void DialogTeachReferenceSystem::Controller::PreStep()
{
	--m_step;

	m_screenTeachReferenceSystem->m_mainLayout->removeWidget(m_screenTeachReferenceSystem->m_currentWidget);
	delete m_screenTeachReferenceSystem->m_currentWidget;

	if (!HavePreStep())
	{
		m_screenTeachReferenceSystem->m_currentWidget = m_screenTeachReferenceSystem->OriginWidget();
	}
	else
	{
		m_screenTeachReferenceSystem->m_currentWidget = (m_screenTeachReferenceSystem->*m_stepMap[m_teachMethod][m_step])();
	}

	m_screenTeachReferenceSystem->m_mainLayout->addWidget(m_screenTeachReferenceSystem->m_currentWidget, 1, 0);
}

inline
bool DialogTeachReferenceSystem::Controller::HaveNextStep()
{
	return m_step < m_stepMap[m_teachMethod].size();
}

inline
bool DialogTeachReferenceSystem::Controller::HavePreStep()
{
	return m_step > -1;
}

