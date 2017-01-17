#include "stdafx.h"
#include "DialogTeachToolSystem.h"
#include "Button.h"
#include "TToolSys.h"
#include "LineEditWithRegExpAndKeyboard.h"

DialogTeachToolSystem::DialogTeachToolSystem(TToolSys* variate, QWidget* parent /*= nullptr*/)
	: DialogParent(parent)
	, m_controller(this,variate)
{
	Init();
}

void DialogTeachToolSystem::UpdateText()
{
}

QWidget* DialogTeachToolSystem::GetToolWidget()
{
	QGroupBox* box = new QGroupBox(tr("Tool"),this);
	QHBoxLayout* layout = new QHBoxLayout(box);

	auto lbTool = new QLabel(tr("Tool"), box);
	lbTool->setAlignment(Qt::AlignCenter);

	auto variateBox = new QComboBox(box);
	variateBox->addItem(m_controller.m_oldVariate->GetScope() + "." + m_controller.m_oldVariate->GetName());
	variateBox->setEnabled(false);

	layout->addWidget(lbTool);
	layout->addWidget(variateBox);

	return box;
}

QWidget* DialogTeachToolSystem::GetButtonWidget()
{
	QWidget* widget = new QWidget(this);
	QHBoxLayout* layout = new QHBoxLayout(widget);

	auto btnPre = new Button(tr("Pre"), widget);
	btnPre->setEnabled(false);
	auto btnNext = new Button(tr("Next"), widget);
	auto btnCancle = new Button(tr("Cancle"), widget);

	layout->addWidget(btnPre);
	layout->addWidget(btnNext);
	layout->addWidget(btnCancle);

	connect(btnNext, &QPushButton::clicked, [this,btnNext,btnPre]{
		m_controller.NextStep();
		btnNext->setEnabled(m_controller.HaveNextStep());
		btnPre->setEnabled(m_controller.HavePreStep());
	});
	connect(btnPre, &QPushButton::clicked, [this, btnNext, btnPre]{
		m_controller.PreStep();
		btnNext->setEnabled(m_controller.HaveNextStep());
		btnPre->setEnabled(m_controller.HavePreStep());
	});
	connect(btnCancle, &QPushButton::clicked, [this]{delete this; });

	return widget;
}

QWidget* DialogTeachToolSystem::OriginWidget()
{
	QGroupBox* box = new QGroupBox(tr("Select teach method"), this);

	QVBoxLayout* layout = new QVBoxLayout(box);

	//auto btnOnePointKeepOrientation = new QRadioButton(tr("1 point XYZ"), box);
	auto btnFourPointKeepOrientation = new QRadioButton(tr("4 points XYZ"), box);
	//auto btnOnePointChangeOrientation = new QRadioButton(tr("1 point 6D"), box);

	layout->addStretch(1);
	layout->addWidget(new QLabel(tr("Keep orientation")));
	//layout->addWidget(btnOnePointKeepOrientation);
	layout->addWidget(btnFourPointKeepOrientation);
	layout->addStretch(1);
	//layout->addWidget(new QLabel(tr("Change orientation")));
	//layout->addWidget(btnOnePointChangeOrientation);
	layout->addStretch(1);

	//btnOnePointKeepOrientation->setChecked(true);
	btnFourPointKeepOrientation->setChecked(true);

	//connect(btnOnePointKeepOrientation, &QRadioButton::clicked, [this]{m_controller.m_teachMethod = Controller::ONE_POINT_KEEP_ORIENTATION; });
	connect(btnFourPointKeepOrientation, &QRadioButton::clicked, [this]{m_controller.m_teachMethod = Controller::FOUR_POINT_KEEP_ORIENTATION; });
	//connect(btnOnePointChangeOrientation, &QRadioButton::clicked, [this]{m_controller.m_teachMethod = Controller::ONE_POINT_CHANGE_ORIENTATION; });

	return box;
}

QWidget* DialogTeachToolSystem::FourPointKeepOrientationWidgetStep1()
{
	QGroupBox* box = new QGroupBox(tr("Method 4 points XYZ"));
	QGridLayout* layout = new QGridLayout(box);

	auto ltX = new QLineEdit("0.00");
	auto ltY = new QLineEdit("0.00");
	auto ltZ = new QLineEdit("0.00");
	auto ltA = new QLineEdit("0.00");
	auto ltB = new QLineEdit("0.00");
	auto ltC = new QLineEdit("0.00");

	ltX->setEnabled(false);
	ltY->setEnabled(false);
	ltZ->setEnabled(false);
	ltA->setEnabled(false);
	ltB->setEnabled(false);
	ltC->setEnabled(false);

	QVector<QLineEdit*> ltLists{ ltX, ltY, ltZ, ltA, ltB, ltC };
	QVector<QString> lbNames{ "X", "Y", "Z", "A", "B", "C" };
	QVector<QString> lbUnits{ "mm", "mm", "mm", QStringLiteral("°"), QStringLiteral("°"), QStringLiteral("°") };

	for (int i = 0; i < ltLists.size();++i)
	{
		layout->addWidget(new QLabel(lbNames[i]),i, 0);
		layout->addWidget(ltLists[i], i, 1);
		layout->addWidget(new QLabel(lbUnits[i]), i, 2);
	}

	auto btnTeach = new QPushButton(tr("Teach"), box);
	layout->addWidget(btnTeach,6,0,1,3);

	connect(btnTeach, &QPushButton::clicked, [this]{
		AssertNotImplement();

	});

	return box;
}

inline
void DialogTeachToolSystem::AssertNotImplement()
{
	QMessageBox::warning(this, tr(""), tr("not implement"), QMessageBox::Cancel);
}

QWidget* DialogTeachToolSystem::FourPointKeepOrientationWidgetStep2()
{
	return FourPointKeepOrientationWidgetStep1();
}

QWidget* DialogTeachToolSystem::FourPointKeepOrientationWidgetStep3()
{
	return FourPointKeepOrientationWidgetStep1();
}

QWidget* DialogTeachToolSystem::FourPointKeepOrientationWidgetStep4()
{
	return FourPointKeepOrientationWidgetStep1();
}

QWidget* DialogTeachToolSystem::KeepOrientationWidgetResult()
{
	QGroupBox* box = new QGroupBox(tr("Select teach method"));
	QVBoxLayout* layout = new QVBoxLayout(box);

	auto btnOnePointChangeOrientation = new QRadioButton(tr("1 point 6D"), box);
	btnOnePointChangeOrientation->setChecked(true);

	layout->addStretch(1);
	layout->addWidget(new QLabel(tr("Change orientation")));
	layout->addWidget(btnOnePointChangeOrientation);
	layout->addStretch(1);

	return box;
}

QWidget* DialogTeachToolSystem::OnePointChangeOrientationWidgetStep1()
{
	QGroupBox* box = new QGroupBox(tr("Method 1 points 6D"));

	return box;
}

QWidget* DialogTeachToolSystem::GetIllustrationWidget()
{
	QGroupBox* box = new QGroupBox(tr("Illustration"), this);

	return box;
}

void DialogTeachToolSystem::Init()
{
	m_mainLayout = new QGridLayout(this);

	m_mainLayout->addWidget(GetToolWidget(), 0, 0, 1, 2);
	m_currentWidget = OriginWidget();
	m_mainLayout->addWidget(m_currentWidget, 1, 0);
	m_mainLayout->addWidget(GetIllustrationWidget(), 1, 1);
	m_mainLayout->addWidget(GetButtonWidget(), 2, 0, 1, 2);

	m_mainLayout->setColumnStretch(0, 1);
	m_mainLayout->setColumnStretch(1, 1);
	m_mainLayout->setRowStretch(1, 1);
}

DialogTeachToolSystem::Controller::Controller(DialogTeachToolSystem* screenMain, TToolSys* variate)
	:m_oldVariate(variate)
	, m_screenMain(screenMain)
{
	m_stepMap.insert(TeachMethod::FOUR_POINT_KEEP_ORIENTATION, 
	{&DialogTeachToolSystem::FourPointKeepOrientationWidgetStep1,
	&DialogTeachToolSystem::FourPointKeepOrientationWidgetStep2,
	&DialogTeachToolSystem::FourPointKeepOrientationWidgetStep3,
	&DialogTeachToolSystem::FourPointKeepOrientationWidgetStep4,
	&DialogTeachToolSystem::KeepOrientationWidgetResult,
	&DialogTeachToolSystem::OnePointChangeOrientationWidgetStep1 });

	m_stepMap.insert(TeachMethod::ONE_POINT_CHANGE_ORIENTATION,
	{ &DialogTeachToolSystem::OnePointChangeOrientationWidgetStep1});
}

void DialogTeachToolSystem::Controller::NextStep()
{
	++m_step;

	if (!HaveNextStep())
	{
		switch (QMessageBox::warning(m_screenMain, "not implement", "", QMessageBox::Cancel))
		{
		case QMessageBox::Cancel:{
			return;
		}break;
		default:
			break;
		}
	}

	m_screenMain->m_mainLayout->removeWidget(m_screenMain->m_currentWidget);
	delete m_screenMain->m_currentWidget;

	m_screenMain->m_currentWidget = (m_screenMain->*m_stepMap[m_teachMethod][m_step])();
	m_screenMain->m_mainLayout->addWidget(m_screenMain->m_currentWidget, 1, 0);
}

void DialogTeachToolSystem::Controller::PreStep()
{
	--m_step;

	m_screenMain->m_mainLayout->removeWidget(m_screenMain->m_currentWidget);
	delete m_screenMain->m_currentWidget;

	if (!HavePreStep())
	{
		m_screenMain->m_currentWidget = m_screenMain->OriginWidget();
	}
	else
	{
		m_screenMain->m_currentWidget = (m_screenMain->*m_stepMap[m_teachMethod][m_step])();
	}

	m_screenMain->m_mainLayout->addWidget(m_screenMain->m_currentWidget, 1, 0);
}

bool DialogTeachToolSystem::Controller::HaveNextStep()
{
	return m_step < m_stepMap[m_teachMethod].size();
}

bool DialogTeachToolSystem::Controller::HavePreStep()
{
	return m_step > -1;
}
