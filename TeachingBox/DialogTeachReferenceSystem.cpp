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
#include "RemoteFeedbackController.h"
#include "..\DataStream\DataStruct.h"
#include "RemoteManager.h"
#include "WarningManager.h"
#include "CoordinateAdapter.h"
#include "ICoordinate.h"



//DialogTeachReferenceSystem::DialogTeachReferenceSystem(TRefSys* oldVariate, QWidget* parent/*=nullptr*/)
//	:DialogParent(parent)
//	, m_controller(this,oldVariate)
//	, m_lbIllustration(new QLabel(this))
//{
//}

DialogTeachReferenceSystem::DialogTeachReferenceSystem(TRefSys* oldVariate, ICoordinate* iCoor/*=nullptr*/, QWidget* parent/*=nullptr*/)
	:DialogParent(parent)
	, m_iCoor(iCoor)
	, m_controller(this, oldVariate)
	, m_lbIllustration(new QLabel(this))
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

	m_lbIllustration->setPixmap(QPixmap(":/new/image/Resources/Image/ref_sys_1_points_keep_origin_step1.png")
		.scaled(m_lbIllustration->width(), m_lbIllustration->height()));

	return widget;
}

QWidget* DialogTeachReferenceSystem::OriginWidget()
{
	QWidget* widget = new QWidget(this);

	QVBoxLayout* layout = new QVBoxLayout(widget);

	layout->addWidget(GetTeachToolWidget());
	layout->addWidget(GetTeachMethodWidget());

	m_lbIllustration->setPixmap(QPixmap(":/new/image/Resources/Image/ref_sys_illustration.png")
		.scaled(m_lbIllustration->width(), m_lbIllustration->height()));
	return widget;
}

QWidget* DialogTeachReferenceSystem::PointWidget()
{
	return new RefSysWidget(this);
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

	m_lbIllustration->setPixmap(QPixmap(":/new/image/Resources/Image/ref_sys_3_points_with_origin_step1.png")
		.scaled(m_lbIllustration->width(),m_lbIllustration->height()));

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

	btnX->setChecked(true);

	layout->addLayout(radioLayout);
	layout->addWidget(PointWidget());

	layout->setStretch(1, 1);

	m_lbIllustration->setPixmap(QPixmap(":/new/image/Resources/Image/ref_sys_3_points_with_origin_step2.png")
		.scaled(m_lbIllustration->width(), m_lbIllustration->height()));

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

	btnXY->setChecked(true);

	layout->addLayout(radioLayout);
	layout->addWidget(PointWidget());

	layout->setStretch(1, 1);

	m_lbIllustration->setPixmap(QPixmap(":/new/image/Resources/Image/ref_sys_3_points_with_origin_step3.png")
		.scaled(m_lbIllustration->width(), m_lbIllustration->height()));

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
	btnX->setChecked(true);
	QHBoxLayout* radioLayout = new QHBoxLayout(widget);
	radioLayout->addWidget(btnX);
	radioLayout->addWidget(btnY);
	radioLayout->addWidget(btnZ);

	layout->addLayout(radioLayout);
	layout->addWidget(PointWidget());

	layout->setStretch(1, 1);

	m_lbIllustration->setPixmap(QPixmap(":/new/image/Resources/Image/ref_sys_3_points_without_origin_step1.png")
		.scaled(m_lbIllustration->width(), m_lbIllustration->height()));

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

	m_lbIllustration->setPixmap(QPixmap(":/new/image/Resources/Image/ref_sys_3_points_without_origin_step2.png")
		.scaled(m_lbIllustration->width(), m_lbIllustration->height()));

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
	btnY->setChecked(true);
	QHBoxLayout* radioLayout = new QHBoxLayout(widget);
	radioLayout->addWidget(btnX);
	radioLayout->addWidget(btnY);
	radioLayout->addWidget(btnZ);

	layout->addLayout(radioLayout);
	layout->addWidget(PointWidget());

	layout->setStretch(1, 1);

	m_lbIllustration->setPixmap(QPixmap(":/new/image/Resources/Image/ref_sys_3_points_without_origin_step3.png")
		.scaled(m_lbIllustration->width(), m_lbIllustration->height()));

	return widget;
}


void DialogTeachReferenceSystem::UpdatePoseEuler(const tPoseEuler& point)
{
	m_iCoor->OnReceive(point);
	delete this;
}

void DialogTeachReferenceSystem::showEvent(QShowEvent *e)
{
	DialogParent::showEvent(e);
	m_lbIllustration->setPixmap(QPixmap(":/new/image/Resources/Image/ref_sys_illustration.png")
		.scaled(m_lbIllustration->width(), m_lbIllustration->height()));
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
	QVBoxLayout* layout = new QVBoxLayout(box);
	m_lbIllustration->setText("illustration");
	layout->addWidget(m_lbIllustration);

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
		if (!m_controller.HaveNextStep())
		{
			UpdatePoseEuler(m_controller.GetDesPoseEuler());
			return;
		}

		m_controller.NextStep();

		btnPre->setEnabled(m_controller.HavePreStep());
		if (!m_controller.HaveNextStep())
		{
			btnNext->setText(tr("Complete"));
		}
		else
		{
			btnNext->setText(tr("Next"));
		}
	});

	connect(btnPre, &QPushButton::clicked, [this, btnPre, btnNext]{
		m_controller.PreStep();

		btnPre->setEnabled(m_controller.HavePreStep());
		btnNext->setEnabled(m_controller.HaveNextStep());
	});

	connect(btnCancle, &QPushButton::clicked, [this]{delete this; });

	return layout;
}


QWidget* DialogTeachReferenceSystem::GetEndWidget()
{
	return new EndWidget(this);
}

DialogTeachReferenceSystem::Controller::Controller(DialogTeachReferenceSystem* screenTeachReferenceSystem, TRefSys* variate)
	:m_screenTeachReferenceSystem(screenTeachReferenceSystem)
	,m_oldVariate(variate)
{
	m_stepMap.insert(Controller::THREE_POINTS_WITH_ORIGIN,
		{ &DialogTeachReferenceSystem::ThreePointsWithOriginWidgetStep1
		, &DialogTeachReferenceSystem::ThreePointsWithOriginWidgetStep2 
		, &DialogTeachReferenceSystem::ThreePointsWithOriginWidgetStep3
		, &DialogTeachReferenceSystem::GetEndWidget });

	m_stepMap.insert(Controller::THREE_POINTS_WITHOUT_ORIGIN, 
		{ &DialogTeachReferenceSystem::ThreePointsWithoutOriginWidgetStep1,
		  &DialogTeachReferenceSystem::ThreePointsWithoutOriginWidgetStep2 
		, &DialogTeachReferenceSystem::ThreePointsWithoutOriginWidgetStep3
		, &DialogTeachReferenceSystem::GetEndWidget });
	m_stepMap.insert(Controller::ONE_POINT_KEEP_ORIENTATION, 
		{ &DialogTeachReferenceSystem::OnePointKeepOrientationStep1
		, &DialogTeachReferenceSystem::GetEndWidget });

	RemoteFeedbackController::GetInstance()->AddListener(this);
}

DialogTeachReferenceSystem::Controller::~Controller()
{
	RemoteFeedbackController::GetInstance()->DeleteListener(this);
}

void DialogTeachReferenceSystem::Controller::NextStep()
{
	if (!IsTeached())
	{
		WarningManager::Warning(m_screenTeachReferenceSystem, tr("Not teached"));
		return;
	}
	m_isTeached = false;

	/*若已保存该位置坐标，则替换该位置，否则添加该位置*/
	if (m_step >=0)
	{
		if (m_poses.size() > static_cast<size_t>(m_step))
		{
			m_poses[m_step] == m_poseEuler;
		}
		else
		{
			m_poses.push_back(m_poseEuler);
		}
	}

	++m_step;

	m_screenTeachReferenceSystem->m_mainLayout->removeWidget(m_screenTeachReferenceSystem->m_currentWidget);
	delete m_screenTeachReferenceSystem->m_currentWidget;

	m_screenTeachReferenceSystem->m_currentWidget = (m_screenTeachReferenceSystem->*m_stepMap[m_teachMethod][m_step])();
	m_screenTeachReferenceSystem->m_mainLayout->addWidget(m_screenTeachReferenceSystem->m_currentWidget, 1, 0);

	if (!HaveNextStep())
	{
		assert(m_poses.size() == static_cast<size_t>(m_stepMap[m_teachMethod].size() - 1));
		if (m_poses.size() != static_cast<size_t>(m_stepMap[m_teachMethod].size() - 1))
		{
			WarningManager::Warning(m_screenTeachReferenceSystem, tr("Failed"));
			return;
		}
		switch (m_teachMethod)
		{
		case DialogTeachReferenceSystem::Controller::THREE_POINTS_WITH_ORIGIN:
		{
			m_desPoseEuler =CoordinateAdapter::CartTeachThreeBase(*m_poses[0], *m_poses[1], *m_poses[2]);
		}
		break;
		case DialogTeachReferenceSystem::Controller::THREE_POINTS_WITHOUT_ORIGIN:
		{
			m_desPoseEuler =CoordinateAdapter::CartTeachThreeNoBase(*m_poses[0], *m_poses[1], *m_poses[2]);
		}
			break;
		case DialogTeachReferenceSystem::Controller::ONE_POINT_KEEP_ORIENTATION:
		{
			m_desPoseEuler =CoordinateAdapter::CartTeachOne(m_poses[0]->m_PositionCartesian);
		}
			break;
		default:
			break;
		}
		assert(typeid(*m_screenTeachReferenceSystem->m_currentWidget) == typeid(EndWidget));
		dynamic_cast<EndWidget*>(m_screenTeachReferenceSystem->m_currentWidget)->Update(m_desPoseEuler);
	}
}

void DialogTeachReferenceSystem::Controller::PreStep()
{
	--m_step;
	if (m_poses.size()> 0)
	{
		m_poses.erase(--m_poses.end());
	}

	m_screenTeachReferenceSystem->m_mainLayout->removeWidget(m_screenTeachReferenceSystem->m_currentWidget);
	delete m_screenTeachReferenceSystem->m_currentWidget;

	if (!HavePreStep())
	{
		m_poses.clear();
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
	return m_step < m_stepMap[m_teachMethod].size()-1;
}

inline
bool DialogTeachReferenceSystem::Controller::HavePreStep()
{
	return m_step > -1;
}

tPoseEuler DialogTeachReferenceSystem::Controller::GetDesPoseEuler() const
{
	return m_desPoseEuler;
}

void DialogTeachReferenceSystem::Controller::OnReseivePose(const tPoseEuler& pose)
{
	m_poseEuler = std::make_shared<tPoseEuler>(pose);
	m_isTeached = true;
}

bool DialogTeachReferenceSystem::Controller::IsTeached()
{
	if (m_step<0)
	{
		return true;
	}
	if (m_poses.size()>static_cast<size_t>(m_step))
	{
		return true;
	}

	return m_isTeached;
}


DialogTeachReferenceSystem::RefSysWidget::RefSysWidget(QWidget* parent /*= 0*/)
	:QWidget(parent)
{
	RemoteFeedbackController::GetInstance()->AddListener(this);

	QGridLayout* layout = new QGridLayout(this);

	m_lbX = new QLineEdit("0.00", this);
	m_lbY = new QLineEdit("0.00", this);
	m_lbZ = new QLineEdit("0.00", this);

	m_lbX->setEnabled(false);
	m_lbY->setEnabled(false);
	m_lbZ->setEnabled(false);

	layout->addWidget(new QLabel("X"), 0, 0);
	layout->addWidget(m_lbX, 0, 1);
	layout->addWidget(new QLabel("mm"), 0, 2);

	layout->addWidget(new QLabel("Y"), 1, 0);
	layout->addWidget(m_lbY, 1, 1);
	layout->addWidget(new QLabel("mm"), 1, 2);

	layout->addWidget(new QLabel("Z"), 2, 0);
	layout->addWidget(m_lbZ, 2, 1);
	layout->addWidget(new QLabel("mm"), 2, 2);

	auto teachButton = new QPushButton(QApplication::translate("DialogTeachReferenceSystem","Teach"));
	layout->addWidget(teachButton, 3, 0, 1, 3);

	connect(teachButton, &QPushButton::clicked, []{
		RemoteManager::GetInstance()->SendCommandToGetPose();
	});
}

DialogTeachReferenceSystem::RefSysWidget::~RefSysWidget()
{
	RemoteFeedbackController::GetInstance()->DeleteListener(this);
}

void DialogTeachReferenceSystem::RefSysWidget::OnReseivePose(const tPoseEuler& pose)
{
	m_lbX->setText(QString::number(pose.m_PositionCartesian.m_X));
	m_lbY->setText(QString::number(pose.m_PositionCartesian.m_Y));
	m_lbZ->setText(QString::number(pose.m_PositionCartesian.m_Z));
}


DialogTeachReferenceSystem::EndWidget::EndWidget(QWidget* parent /*= 0*/)
	:QWidget(parent)
{
	auto groupBox = new QGroupBox(tr("Reference system"), this);
	auto layout = new QGridLayout(groupBox);

	auto lbX = new QLabel("X", groupBox);
	auto lbY = new QLabel("Y", groupBox);
	auto lbZ = new QLabel("Z", groupBox);
	auto lbA = new QLabel("A", groupBox);
	auto lbB = new QLabel("B", groupBox);
	auto lbC = new QLabel("C", groupBox);

	m_ltX = new QLineEdit(groupBox);
	m_ltY = new QLineEdit(groupBox);
	m_ltZ = new QLineEdit(groupBox);
	m_ltA = new QLineEdit(groupBox);
	m_ltB = new QLineEdit(groupBox);
	m_ltC = new QLineEdit(groupBox);

	m_ltX->setEnabled(false);
	m_ltY->setEnabled(false);
	m_ltZ->setEnabled(false);
	m_ltA->setEnabled(false);
	m_ltB->setEnabled(false);
	m_ltC->setEnabled(false);


	layout->addWidget(lbX, 0, 0);
	layout->addWidget(lbY, 1, 0);
	layout->addWidget(lbZ, 2, 0);
	layout->addWidget(lbA, 3, 0);
	layout->addWidget(lbB, 4, 0);
	layout->addWidget(lbC, 5, 0);

	layout->addWidget(m_ltX, 0, 1);
	layout->addWidget(m_ltY, 1, 1);
	layout->addWidget(m_ltZ, 2, 1);
	layout->addWidget(m_ltA, 3, 1);
	layout->addWidget(m_ltB, 4, 1);
	layout->addWidget(m_ltC, 5, 1);
}

void DialogTeachReferenceSystem::EndWidget::Update(const tPoseEuler& poseEuler)
{
	m_ltX->setText(QString::number(poseEuler.m_PositionCartesian.m_X));
	m_ltY->setText(QString::number(poseEuler.m_PositionCartesian.m_Y));
	m_ltZ->setText(QString::number(poseEuler.m_PositionCartesian.m_Z));
	m_ltA->setText(QString::number(poseEuler.m_PostureEuler.m_A));
	m_ltB->setText(QString::number(poseEuler.m_PostureEuler.m_B));
	m_ltC->setText(QString::number(poseEuler.m_PostureEuler.m_C));
}

