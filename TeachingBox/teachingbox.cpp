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
#include "DynamicController.h"
#include "CodeEditorManager.h"
#include "TeachingBoxBroadcast.h"
#include "WarningInfo.h"
#include "WarningModel.h"
#include "RemoteManager.h"

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
	TeachingBoxContext::GetInstance()->SetTeachingBoxRect(geometry());
}

void TeachingBox::Init()
{
	InitContext();
	setFixedSize(WIDTH, HEIGHT);
	InitVertical();
	UpdateText();
	InitState();
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
	InitBottomButton(bottomLayout);
}

/*************************************************
//  Function: 		TeachingBox::InitTop(QLayout* layout)
//  Description: 	生成示教器顶部控件，包括切换调试按钮、急停
//  Calls:		 	TeachingBox::SlotOnModelChanged()
//  Called By: 		TeachingBox::InitVertical()
//  Parameter:      QLayout* layout
//  Return: 		void
//  Others: 		// 其它说明
*************************************************/
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

	Button* servoSwitch = new Button("Servo",this);
	realLayout->addWidget(servoSwitch);
	realLayout->addStretch(1);

	connect(btnMode1, SIGNAL(clicked()), this, SLOT(SlotOnModelChanged()));
	connect(btnMode2, SIGNAL(clicked()), this, SLOT(SlotOnModelChanged()));
	connect(btnMode3, SIGNAL(clicked()), this, SLOT(SlotOnModelChanged()));

	connect(servoSwitch, &Button::clicked, [this]{
		if (Context::interpreterContext.GetExecuteMode()==InterpreterContext::AUTO)
		{
			emit(TeachingBoxBroadcast::GetInstance()->WarningThrowed(
				WarningInfo{ WarningInfo::ID_PRESS_MANUAL_SERVO_BUTTON_AT_AUTO_MODE}));
		}
		auto isServoOn = !TeachingBoxContext::GetInstance()->IsServoOn();
		TeachingBoxContext::GetInstance()->SetIsServoOn(isServoOn);
		emit(TeachingBoxBroadcast::GetInstance()->ServoStateChanged(isServoOn));
	});
}

void TeachingBox::InitBottomButton(QLayout* layout)
{
	QHBoxLayout* realLayout = dynamic_cast<QHBoxLayout*>(layout);
	QHBoxLayout* mainLayout = new QHBoxLayout();
	realLayout->addStretch(WARNING_WIDTH_RATIO + OPTION_WIDTH_RATIO);
	realLayout->addLayout(mainLayout, SCREEN_WIDTH_RATIO);
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

	connect(btnVMinus, &Button::pressed, DynamicController::GetInstance(), &DynamicController::Decelerate);
	connect(btnVMinus, &Button::released, DynamicController::GetInstance(), &DynamicController::Stop);
	connect(btnVPlus, &Button::pressed, DynamicController::GetInstance(), &DynamicController::Accelerate);
	connect(btnVPlus, &Button::released, DynamicController::GetInstance(), &DynamicController::Stop);
	connect(btnMot, &Button::clicked, [this]{
		if (Context::interpreterContext.GetExecuteMode()!=InterpreterContext::AUTO)
		{
			emit(TeachingBoxBroadcast::GetInstance()->WarningThrowed(WarningInfo{WarningInfo::ID_PRESS_AUTO_SERVO_BUTTON_AT_MANUAL_MODE}));
			return;
		}

		bool isMotOn = !TeachingBoxContext::GetInstance()->IsMotOn();
		TeachingBoxContext::GetInstance()->SetIsMotOn(isMotOn);
		emit(TeachingBoxBroadcast::GetInstance()->ServoStateChanged(isMotOn));
	});
	connect(btnJog, &Button::clicked, []{
		auto state = TeachingBoxContext::GetInstance()->GetJogState();
		if (state==TeachingBoxContext::AXIS)
		{
			TeachingBoxContext::GetInstance()->SetJog(TeachingBoxContext::XYZ);
		}
		else
		{
			TeachingBoxContext::GetInstance()->SetJog(TeachingBoxContext::AXIS);
		}
	});
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
	InitMovementButton(movementLayout);
}

void TeachingBox::InitContext()
{
	TcpManager::GetInstance();
	WarningModel::GetInstance();
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

	btnProgram->setEnabled(false);

	connect(btnService, &QPushButton::clicked, []{
		ScreenManager::GetInstance()->ChangeScreen(ScreenManager::SERVICE);
	});
	connect(btnVariate, &QPushButton::clicked, this, []{
		ScreenManager::GetInstance()->ChangeScreen(ScreenManager::VARIATE);
	});
	connect(btnProject, &QPushButton::clicked, []{
		ScreenManager::GetInstance()->ChangeScreen(ScreenManager::PROJECT);
	});
	connect(btnProgram, &QPushButton::clicked, []{
		ScreenManager::GetInstance()->ChangeScreen(ScreenManager::PROGRAM);
	});
	connect(btnCoordinate, &QPushButton::clicked, []{
		ScreenManager::GetInstance()->ChangeScreen(ScreenManager::COORDINATE);
	});
	connect(btnWarning, &QPushButton::clicked, []{
		ScreenManager::GetInstance()->ChangeScreen(ScreenManager::WARNING);
	});

	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::OpenProgram, [btnProgram](){
		btnProgram->setEnabled(true);
	});
}

void TeachingBox::InitMovementButton(QLayout* layout)
{
	QGridLayout* realLayout = dynamic_cast<QGridLayout*>(layout);

	//示教盒右侧控件
	Button* btnStop = new Button("Stop", this);
	Button* btnStart = new Button("Start", this);
	Button* btnA1Plus = new Button("+", this);
	Button* btnA1Minus = new Button("-", this);
	Button* btnA2Plus = new Button("+", this);
	Button* btnA2Minus = new Button("-", this);
	Button* btnA3Plus = new Button("+", this);
	Button* btnA3Minus = new Button("-", this);
	Button* btnA4Plus = new Button("+", this);
	Button* btnA4Minus = new Button("-", this);
	Button* btnA5Plus = new Button("+", this);
	Button* btnA5Minus = new Button("-", this);
	Button* btnA6Plus = new Button("+", this);
	Button* btnA6Minus = new Button("-", this);
	Button* btn2nd = new Button("2nd", this);

	realLayout->addWidget(btnStart, 0, 0);
	realLayout->addWidget(btnStop, 0, 1);
	realLayout->addWidget(btnA1Plus, 1, 0);
	realLayout->addWidget(btnA1Minus, 1, 1);

	realLayout->addWidget(btnA2Plus, 2, 0);
	realLayout->addWidget(btnA2Minus, 2, 1);

	realLayout->addWidget(btnA3Plus, 3, 0);
	realLayout->addWidget(btnA3Minus, 3, 1);

	realLayout->addWidget(btnA4Plus, 4, 0);
	realLayout->addWidget(btnA4Minus, 4, 1);

	realLayout->addWidget(btnA5Plus, 5, 0);
	realLayout->addWidget(btnA5Minus, 5, 1);

	realLayout->addWidget(btnA6Plus, 6, 0);
	realLayout->addWidget(btnA6Minus, 6, 1);

	realLayout->addWidget(btn2nd, 7, 0);

	connect(btnStart, SIGNAL(pressed()), this, SLOT(SlotOnStartButtonPressed()));
	connect(btnStart, SIGNAL(released()), this, SLOT(SlotOnStartButtonReleased()));
	connect(btnStop, SIGNAL(clicked()), this, SLOT(SlotOnStopButtonClicked()));

	connect(btnA1Plus, &Button::pressed, this, []{
		auto state = TeachingBoxContext::GetInstance()->GetJogState();
		if (state==TeachingBoxContext::AXIS)
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_AXIS_PLUS_1);
		}
		else
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_X_PLUS);
		}
	});
	connect(btnA1Minus, &Button::pressed, this, []{
		auto state = TeachingBoxContext::GetInstance()->GetJogState();
		if (state == TeachingBoxContext::AXIS)
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_AXIS_MINUS_1);
		}
		else
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_X_MINUS);
		}
	});

	connect(btnA2Plus, &Button::pressed, this, []{
		auto state = TeachingBoxContext::GetInstance()->GetJogState();
		if (state == TeachingBoxContext::AXIS)
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_AXIS_PLUS_2);
		}
		else
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_Y_PLUS);
		}
	});
	connect(btnA2Minus, &Button::pressed, this, []{
		auto state = TeachingBoxContext::GetInstance()->GetJogState();
		if (state == TeachingBoxContext::AXIS)
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_AXIS_MINUS_2);
		}
		else
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_Y_MINUS);
		}
	});

	connect(btnA3Plus, &Button::pressed, this, []{
		auto state = TeachingBoxContext::GetInstance()->GetJogState();
		if (state == TeachingBoxContext::AXIS)
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_AXIS_PLUS_3);
		}
		else
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_Z_PLUS);
		}
	});
	connect(btnA3Minus, &Button::pressed, this, []{
		auto state = TeachingBoxContext::GetInstance()->GetJogState();
		if (state == TeachingBoxContext::AXIS)
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_AXIS_MINUS_3);
		}
		else
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_Z_MINUS);
		}
	});

	connect(btnA4Plus, &Button::pressed, this, []{
		auto state = TeachingBoxContext::GetInstance()->GetJogState();
		if (state == TeachingBoxContext::AXIS)
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_AXIS_PLUS_4);
		}
		else
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_A_PLUS);
		}
	});
	connect(btnA4Minus, &Button::pressed, this, []{
		auto state = TeachingBoxContext::GetInstance()->GetJogState();
		if (state == TeachingBoxContext::AXIS)
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_AXIS_MINUS_4);
		}
		else
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_A_MINUS);
		}
	});

	connect(btnA5Plus, &Button::pressed, this, []{
		auto state = TeachingBoxContext::GetInstance()->GetJogState();
		if (state == TeachingBoxContext::AXIS)
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_AXIS_PLUS_5);
		}
		else
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_B_PLUS);
		}
	});
	connect(btnA5Minus, &Button::pressed, this, []{
		auto state = TeachingBoxContext::GetInstance()->GetJogState();
		if (state == TeachingBoxContext::AXIS)
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_AXIS_MINUS_5);
		}
		else
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_B_MINUS);
		}
	});

	connect(btnA6Plus, &Button::pressed, this, []{
		auto state = TeachingBoxContext::GetInstance()->GetJogState();
		if (state == TeachingBoxContext::AXIS)
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_AXIS_PLUS_6);
		}
		else
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_C_PLUS);
		}
	});
	connect(btnA6Minus, &Button::pressed, this, []{
		auto state = TeachingBoxContext::GetInstance()->GetJogState();
		if (state == TeachingBoxContext::AXIS)
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_AXIS_MINUS_6);
		}
		else
		{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::MOVE_C_MINUS);
		}
	});

	std::vector<Button*> vec{};
	vec.push_back(btnA1Plus);
	vec.push_back(btnA2Plus);
	vec.push_back(btnA3Plus);
	vec.push_back(btnA4Plus);
	vec.push_back(btnA5Plus);
	vec.push_back(btnA6Plus);
	vec.push_back(btnA1Minus);
	vec.push_back(btnA2Minus);
	vec.push_back(btnA3Minus);
	vec.push_back(btnA4Minus);
	vec.push_back(btnA5Minus);
	vec.push_back(btnA6Minus);

	for (auto btn:vec)
	{
		connect(btn, &Button::released, []{
			RemoteManager::GetInstance()->SendSpecialCommand(CommandId::STOP_MOVE);
		});
	}
}

void TeachingBox::InitScreen(QLayout* layout)
{
	layout->addWidget(new Screen(this));
	layout->setSpacing(0);
	layout->setMargin(0);
}

void TeachingBox::InitState()
{
	SlotOnModelChanged();

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
	if (Context::projectContext.ProjectLoaded().isEmpty())
	{
		WarningManager::Warning(this, WarningManager::PleaseLoadProject);
		return;
	}
	try{
		CodeEditorManager::GetInstance()->ClearWrongLine();

		switch (Context::interpreterContext.GetExecuteMode())
		{
		case InterpreterContext::AUTO:{
			if (Context::interpreterContext.GetPCLine() < 0 || Context::interpreterContext.GetProgramExecuting().size() == 0)
			{
				QMessageBox::warning(this, tr("Lose PC Line"), tr("Please set PC line"));
				return;
			}
			if (!InterpreterManager::GetInstance()->AutoExecute())
			{
				QMessageBox::warning(this, tr("Operator failed"), tr("Already execute"));
			}
		}break;
		case InterpreterContext::MANUAL:{
			if (Context::interpreterContext.GetPCLine() < 0 || Context::interpreterContext.GetProgramExecuting().size() == 0)
			{
				QMessageBox::warning(this, tr("Lose PC Line"), tr("Please set PC line"));
				return;
			}
			if (!InterpreterManager::GetInstance()->ManualExecute())
			{
				QMessageBox::warning(this, tr("Operator failed"), tr("Already execute"));
			}
		}break;
		case InterpreterContext::STEP:{
			if (Context::interpreterContext.GetPCLine() < 0 || Context::interpreterContext.GetProgramExecuting().size() == 0)
			{
				QMessageBox::warning(this, tr("Lose PC Line"), tr("Please set PC line"));
				return;
			}
			InterpreterManager::GetInstance()->StepExecute();
		}break;
		default:
			break;
		}
	}
	catch (TInterpreterException& e){
		CodeEditorManager::GetInstance()->HighlightWrongLine(Context::interpreterContext.GetProgramLoading(), e.LineNumber());
		WarningManager::Warning(this, e.Info());
		return;
	}
}

void TeachingBox::SlotOnStopButtonClicked()
{
	InterpreterManager::GetInstance()->StopExecute();
}
