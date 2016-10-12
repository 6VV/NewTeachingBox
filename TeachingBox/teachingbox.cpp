#include "stdafx.h"
#include "TeachingBox.h"
#include "WarningLight.h"
#include "QBoxLayout"
#include "Button.h"
#include "Screen.h"
#include "ScreenManager.h"
#include "InterpreterContext.h"
#include "Context.h"
#include "TeachingBoxContext.h"
#include "InterpreterManager.h"
#include "TInterpreterException.h"
#include "WarningManager.h"
#include "TcpManager.h"
#include "CodeEditor.h"

TeachingBox::TeachingBox(QWidget *parent)
	: InternationalWidget(parent)
{
	Init();
}

TeachingBox::~TeachingBox()
{

}

void TeachingBox::paintEvent(QPaintEvent *e)
{
	InternationalWidget::paintEvent(e);
	TeachingBoxContext::SetTeachingBoxRect(geometry());
}

void TeachingBox::Init()
{
	InitContext();

	setFixedSize(WIDTH, HEIGHT);

	InitVertical();

	UpdateText();
}

void TeachingBox::InitVertical()
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	QHBoxLayout* topLayout = new QHBoxLayout(this);
	QHBoxLayout* centerLayout = new QHBoxLayout(this);
	QHBoxLayout* bottomLayout = new QHBoxLayout(this);

	layout->addLayout(topLayout,TOP_HEIGHT_RATIO);
	layout->addLayout(centerLayout,CENTER_HEIGHT_RATIO);
	layout->addLayout(bottomLayout, BOTTOM_HEIGHT_RATIO);

	layout->setSpacing(0);

	InitTop(topLayout);
	InitCenter(centerLayout);
	InitBottom(bottomLayout);
}

void TeachingBox::InitTop(QLayout* layout)
{
	QHBoxLayout* realLayout = dynamic_cast<QHBoxLayout*>(layout);
    m_modelButtonGroup = new QButtonGroup(this);
	QRadioButton* btnMode1 = new QRadioButton(this);
	QRadioButton* btnMode2 = new QRadioButton(this);
	QRadioButton* btnMode3 = new QRadioButton(this);
	m_modelButtonGroup->addButton(btnMode1, InterpreterContext::AUTO);
	m_modelButtonGroup->addButton(btnMode2, InterpreterContext::STEP);
	m_modelButtonGroup->addButton(btnMode3, InterpreterContext::MANUAL);
	btnMode1->setChecked(true);

	Button* btnScram = new Button("Scram",this);

	realLayout->addStretch(1);
	realLayout->addWidget(btnMode1);
	realLayout->addWidget(btnMode2);
	realLayout->addWidget(btnMode3);
	realLayout->addStretch(1);
	realLayout->addWidget(btnScram);
	realLayout->addStretch(1);

	connect(btnMode1, SIGNAL(clicked()), this, SLOT(SlotOnModelChanged()));
	connect(btnMode2, SIGNAL(clicked()), this, SLOT(SlotOnModelChanged()));
	connect(btnMode3, SIGNAL(clicked()), this, SLOT(SlotOnModelChanged()));
}

void TeachingBox::InitBottom(QLayout* layout)
{
	QHBoxLayout* realLayout = dynamic_cast<QHBoxLayout*>(layout);
	QHBoxLayout* mainLayout = new QHBoxLayout();
	realLayout->addStretch(WARNING_WIDTH_RATIO + OPTION_WIDTH_RATIO);
	realLayout->addLayout(mainLayout,SCREEN_WIDTH_RATIO);
	realLayout->addStretch(MOVEMENT_WIDTH_RATIO);
	realLayout->setSpacing(0);

	Button* btnF1 = new Button("F1", this);
	Button* btnF2 = new Button("F2", this);
	Button* btnMot = new Button("Mot", this);
	Button* btnRob = new Button("Rob", this);
	Button* btnJog = new Button("Jog", this);
	Button* btnFB = new Button("FB", this);
	Button* btnStep = new Button("Step", this);
	Button* btnVMinus = new Button("V-", this);
	Button* btnVPlus = new Button("V+", this);

	mainLayout->addWidget(btnF1);
	mainLayout->addWidget(btnF2);
	mainLayout->addWidget(btnMot);
	mainLayout->addWidget(btnRob);
	mainLayout->addWidget(btnJog);
	mainLayout->addWidget(btnFB);
	mainLayout->addWidget(btnStep);
	mainLayout->addWidget(btnVMinus);
	mainLayout->addWidget(btnVPlus);

	mainLayout->setSpacing(0);
}

void TeachingBox::InitCenter(QLayout* layout)
{
	QHBoxLayout* realLayout = dynamic_cast<QHBoxLayout*>(layout);

	QVBoxLayout* warningLayout = new QVBoxLayout();
	QVBoxLayout* optionLayout = new QVBoxLayout();
	QHBoxLayout* screenLayout = new QHBoxLayout();
	QGridLayout* movementLayout = new QGridLayout();

	realLayout->addLayout(warningLayout, WARNING_WIDTH_RATIO);
	realLayout->addLayout(optionLayout, OPTION_WIDTH_RATIO);
	realLayout->addLayout(screenLayout, SCREEN_WIDTH_RATIO);
	realLayout->addLayout(movementLayout, MOVEMENT_WIDTH_RATIO);

	InitWarning(warningLayout);
	InitOption(optionLayout);
	InitScreen(screenLayout);
	InitMovement(movementLayout);
}

void TeachingBox::InitContext()
{
	TcpManager::GetInstance();
}

void TeachingBox::InitOption(QLayout* layout)
{
	QVBoxLayout* realLayout = dynamic_cast<QVBoxLayout*>(layout);

	Button* btnUndefine=new Button("U",this);
	Button* btnService = new Button("Setting", this);
	Button* btnVariate = new Button("Variate", this);
	Button* btnProject = new Button("Project", this);
	Button* btnProgram = new Button("Program", this);
	Button* btnCoordinate = new Button("Coordinate", this);
	Button* btnWarning = new Button("Warning", this);

	realLayout->addWidget(btnUndefine);
	realLayout->addWidget(btnService);
	realLayout->addWidget(btnVariate);
	realLayout->addWidget(btnProject);
	realLayout->addWidget(btnProgram);
	realLayout->addWidget(btnCoordinate);
	realLayout->addWidget(btnWarning);

	connect(btnService, SIGNAL(clicked()), this, SLOT(SlotOnServiceButtonClicked()));
	connect(btnVariate, SIGNAL(clicked()), this, SLOT(SlotOnVariateButtonClicked()));
	connect(btnProject, SIGNAL(clicked()), this, SLOT(SlotOnProjectButtonClicked()));
	connect(btnProgram, SIGNAL(clicked()), this, SLOT(SlotOnProgramButtonClicked()));
}

void TeachingBox::InitMovement(QLayout* layout)
{
	QGridLayout* realLayout = dynamic_cast<QGridLayout*>(layout);

	//示教盒右侧控件
	Button* btnStop = new Button("Stop", this);
	Button* btnStart = new Button("Start", this);
	Button* A1Plus = new Button("+", this);
	Button* A1Minus = new Button("-", this);
	Button* A2Plus = new Button("+", this);
	Button* A2Minus = new Button("-", this);
	Button* A3Plus = new Button("+", this);
	Button* A3Minus = new Button("-", this);
	Button* A4Plus = new Button("+", this);
	Button* A4Minus = new Button("-", this);
	Button* A5Plus = new Button("+", this);
	Button* A5Minus = new Button("-", this);
	Button* A6Plus = new Button("+", this);
	Button* A6Minus = new Button("-", this);
	Button* btn2nd = new Button("2nd", this);

	realLayout->addWidget(btnStart, 0, 0);
	realLayout->addWidget(btnStop, 0, 1);
	realLayout->addWidget(A1Plus, 1, 0);
	realLayout->addWidget(A1Minus, 1, 1);

	realLayout->addWidget(A2Plus, 2, 0);
	realLayout->addWidget(A2Minus, 2, 1);

	realLayout->addWidget(A3Plus, 3, 0);
	realLayout->addWidget(A3Minus, 3, 1);

	realLayout->addWidget(A4Plus, 4, 0);
	realLayout->addWidget(A4Minus, 4, 1);

	realLayout->addWidget(A5Plus, 5, 0);
	realLayout->addWidget(A5Minus, 5, 1);

	realLayout->addWidget(A6Plus, 6, 0);
	realLayout->addWidget(A6Minus, 6, 1);

	realLayout->addWidget(btn2nd, 7, 0);

	connect(btnStart, SIGNAL(pressed()), this, SLOT(SlotOnStartButtonPressed()));
	connect(btnStart, SIGNAL(released()), this, SLOT(SlotOnStartButtonReleased()));
	connect(btnStop, SIGNAL(clicked()), this, SLOT(SlotOnStopButtonClicked()));
}

void TeachingBox::InitScreen(QLayout* layout)
{
	layout->addWidget(new Screen(this));
	layout->setSpacing(0);
	layout->setMargin(0);
}

void TeachingBox::InitWarning(QLayout* layout)
{
	QVBoxLayout* realLayout = dynamic_cast<QVBoxLayout*>(layout);
	QGridLayout* mainLayout = new QGridLayout(this);
	realLayout->addLayout(mainLayout);
	realLayout->addStretch(1);

	mainLayout->addWidget(new QLabel("RUN"), 0, 0,1,2);
	mainLayout->addWidget(new QLabel("ERR"), 1, 0,1,2);
	mainLayout->addWidget(new QLabel("PRO"), 2, 0,1,2);
	mainLayout->addWidget(new QLabel("MOT"), 3, 0,1,2);

	mainLayout->addWidget(new WarningLight(this), 0, 1);
	mainLayout->addWidget(new WarningLight(this), 1, 1);
	mainLayout->addWidget(new WarningLight(this), 2, 1);
	mainLayout->addWidget(new WarningLight(this), 3, 1);

	mainLayout->setSpacing(5);

}

void TeachingBox::SlotOnModelChanged()
{
	switch (m_modelButtonGroup->checkedId())
	{
	case InterpreterContext::AUTO:
	case InterpreterContext::STEP:
	case InterpreterContext::MANUAL:{
		Context::interpreterContext.SetExecuteMode(static_cast<InterpreterContext::ExecuteMode>(m_modelButtonGroup->checkedId()));
	}break;
	default:break;
	}
}

void TeachingBox::UpdateText()
{
}

void TeachingBox::SlotOnServiceButtonClicked()
{
	ScreenManager::GetInstance()->ChangeScreen(ScreenManager::SERVICE);
}

void TeachingBox::SlotOnVariateButtonClicked()
{
	ScreenManager::GetInstance()->ChangeScreen(ScreenManager::VARIATE);
}

void TeachingBox::SlotOnProjectButtonClicked()
{
	ScreenManager::GetInstance()->ChangeScreen(ScreenManager::PROJECT);
}

void TeachingBox::SlotOnProgramButtonClicked()
{
	ScreenManager::GetInstance()->ChangeScreen(ScreenManager::PROGRAM);
}

void TeachingBox::SlotOnStartButtonReleased()
{
	switch (Context::interpreterContext.GetExecuteMode())
	{
	case InterpreterContext::MANUAL:{
		SlotOnStopButtonClicked();
	}break;
	default:break;
	}
}

void TeachingBox::SlotOnStartButtonPressed()
{
	if (Context::projectContext.GetProjectLoaded().isEmpty())
	{
		WarningManager::Warning(this, WarningManager::PleaseLoadProject);
		return;
	}
	try{
		CodeEditor::GetInstance()->ClearWrongLine();

		switch (Context::interpreterContext.GetExecuteMode())
		{
		case InterpreterContext::AUTO:{
			InterpreterManager::GetInstance()->AutoExecute();
		}break;
		case InterpreterContext::MANUAL:{
			InterpreterManager::GetInstance()->ManualExecute();
		}break;
		case InterpreterContext::STEP:{
			InterpreterManager::GetInstance()->StepExecute();
		}break;
		default:
			break;
		}
	}
	catch (TInterpreterException& e){
		CodeEditor::GetInstance()->HighlightWrongLine(e.GetLineNumber());
		WarningManager::Warning(this, e.GetInfo());
		return;
	}
}

void TeachingBox::SlotOnStopButtonClicked()
{
	InterpreterManager::GetInstance()->StopExecute();
}
