#include "stdafx.h"
#include "ScreenState.h"
#include "LabelWithBorder.h"
#include "DynamicController.h"
#include "TeachingBoxBroadcast.h"
#include "InterpreterContext.h"
#include "WidgetWithBorderAndIcon.h"
#include "Context.h"
#include "RemoteManager.h"
#include "TVariateContext.h"
#include "TRefSys.h"
#include "TeachingBoxInitialization.h"
#include "TToolSys.h"
#include "TVariateManager.h"
#include "RobotDatabase.h"



ScreenState::ScreenState(QWidget* parent/*=0*/)
	:InternationalWidget(parent)
	, m_lbLogo(new LabelWithBorder(this))			/*商标*/
	, m_lbServoState(new LabelWithBorder(this))			/*程序状态*/
	, m_lbExecuteMode(new LabelWithBorder(this))		/*同上*/
	, m_lbExecuteState(new LabelWithBorder(this))				/*用户自定义*/
	, m_lb4(new LabelWithBorder(this))				/*同上*/
	, m_lb5(new LabelWithBorder(this))				/*同上*/
	, m_lbSpace(new LabelWithBorder(this))			/*空间监控*/
	, m_lbSecurityState(new LabelWithBorder(this))	/*安全状态*/
	, m_lbUserAuthority(new LabelWithBorder(this))	/*用户权限*/
	, m_lbCurrentTime(new LabelWithBorder(this))	/*当前时间*/
{
	Init();
}

ScreenState::~ScreenState()
{

}

void ScreenState::UpdateText()
{
}

void ScreenState::showEvent(QShowEvent *)
{
	if (m_isFirstCreate)
	{
		InitState();
		m_isFirstCreate = false;
	}
}

void ScreenState::Init()
{
	InitLayout();
	InitSignalSlot();
	UpdateText();

	/*更新速度*/
	m_comboBoxSpeed->clear();
	for (int i = 1; i < 101; ++i)
	{
		m_comboBoxSpeed->AddIconItem(QString::number(i)+"%");
	}
	m_comboBoxSpeed->setCurrentText(QString::number(DynamicController::InitSpeed()) + "%");
	DynamicController::GetInstance()->AddWidget(m_comboBoxSpeed);

	TeachingBoxContext::GetInstance()->SetCurrentRefSys(TVariateManager::GetInstance()
		->GetVariate(ProjectContext::ScopeSystem(), TeachingBoxInitialization::WorldRefSys()->GetName()));
	TeachingBoxContext::GetInstance()->SetCurrentToolSys(TVariateManager::GetInstance()
		->GetVariate(ProjectContext::ScopeSystem(), TeachingBoxInitialization::DefaultToolSys()->GetName()));

	UpdateRefSysBox();
	UpdateToolRefBox();
	updateRobot();
}

void ScreenState::UpdateToolRefBox()
{
	m_comboBoxTool->clear();
	auto toolSyses = TVariateContext::GetInstance()->GetAllVariates(TToolSys::TypeName());
	for (auto toolSys : toolSyses)
	{
		m_comboBoxTool->AddIconItem(toolSys->GetScope()+"."+toolSys->GetName());
	}
	auto currentSys = TeachingBoxContext::GetInstance()->GetCurrentToolSys();
	auto newItemText = currentSys->GetScope() + "." + currentSys->GetName();
	m_comboBoxTool->setCurrentText(newItemText);

	auto currentText = m_comboBoxTool->currentText();
	/*若当前选择的变量不是设置的变量*/
	if (newItemText != currentText)
	{
		TeachingBoxContext::GetInstance()->SetCurrentToolSys(TVariateManager::GetInstance()->GetVariate(
			currentText.split(".").at(0), currentText.split(".").at(1)));
	}

}

void ScreenState::updateRobot()
{
	auto currentText = m_comboBoxRobot->currentText();
	m_comboBoxRobot->clear();
	auto robots = Database::RobotDatabase::selectRobot();
	for (auto& robot : robots)
	{
		m_comboBoxRobot->AddIconItem(robot.name, robot.id);
	}
	if (currentText.isEmpty())
	{
		m_comboBoxRobot->setCurrentIndex(-1);
	}
	else {
		m_comboBoxRobot->setCurrentText(currentText);
	}
}

void ScreenState::UpdateRefSysBox()
{
	m_comboBoxRefSys->clear();
	auto refSyses = TVariateContext::GetInstance()->GetAllVariates(TRefSys::TypeName());
	for (auto refSys : refSyses)
	{
		m_comboBoxRefSys->AddIconItem(refSys->GetScope() + "." + refSys->GetName());
	}
	auto currentSys = TeachingBoxContext::GetInstance()->GetCurrentRefSys();
	auto newItemText = currentSys->GetScope() + "." + currentSys->GetName();
	m_comboBoxRefSys->setCurrentText(newItemText);

	auto currentText = m_comboBoxRefSys->currentText();
	/*若当前选择的变量不是设置的变量*/
	if (newItemText != currentText)
	{
		TeachingBoxContext::GetInstance()->SetCurrentRefSys(TVariateManager::GetInstance()->GetVariate(
			currentText.split(".").at(0), currentText.split(".").at(1)));
	}
}

void ScreenState::InitLayout()
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);

	layout->addLayout(GetFirstLayout());
	layout->addLayout(GetSecondLayout());
}

void ScreenState::InitSignalSlot()
{
	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::ExecuteModeChanged, this, &ScreenState::ChangeRunningMode, Qt::QueuedConnection);
	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::ExecuteStateChanged, this,&ScreenState::ChangeRunningState,Qt::QueuedConnection);
	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::ServoStateChanged, this, &ScreenState::ChangeServoState, Qt::QueuedConnection);
	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::LoadProject, this, &ScreenState::LoadProject, Qt::QueuedConnection);
	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::OpenProgram, this, &ScreenState::OpenProgram, Qt::QueuedConnection);
	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::LoadFilesChanged, this, &ScreenState::LoadFilesChanged, Qt::QueuedConnection);
	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::DateTimeChanged, this, [this](const QDateTime& dateTime){
		m_lbCurrentTime->setText(dateTime.toString("hh::mm::ss"));
	}, Qt::DirectConnection);
	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::AddVariate, this, &ScreenState::OnChangeVariate);
	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::DeleteVariate, this, &ScreenState::OnChangeVariate);
	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::RobotInfoChanged, this, &ScreenState::updateRobot);


	connect(m_comboBoxProgram, static_cast<void (QComboBox::*)(const QString& text)>(&QComboBox::textActivated), [this](const QString& program){
		if (m_comboBoxProject->currentText().size()==0)
		{
			return;
		}
		emit(TeachingBoxBroadcast::GetInstance()->OpenProgram(m_comboBoxProject->currentText(), program));
	});
	connect(m_comboBoxSpeed, static_cast<void (QComboBox::*)(const QString& text)>(&QComboBox::textActivated), [this](const QString& text){
		int speed = text.left(text.size() - 1).toInt();
		RemoteManager::GetInstance()->SendSpecialCommand(CommandId::SET_SPEED_PRECENT,speed);
	});
	connect(m_comboBoxRefSys, static_cast<void (QComboBox::*)(const QString& text)>(&QComboBox::textActivated), [this](const QString& text){
		auto scope = text.split(".").at(0);
		auto name = text.split(".").at(1);
		auto currentRefSys = TeachingBoxContext::GetInstance()->GetCurrentRefSys();

		/*若选择的变量已被设置*/
		if (scope==currentRefSys->GetScope() && name==currentRefSys->GetName())
		{
			return;
		}

		TeachingBoxContext::GetInstance()->SetCurrentRefSys(TVariateManager::GetInstance()->GetVariate(scope, name));
	});
	connect(m_comboBoxTool, static_cast<void (QComboBox::*)(const QString& text)>(&QComboBox::textActivated), [this](const QString& text){
		auto scope = text.split(".").at(0);
		auto name = text.split(".").at(1);
		auto currentSys = TeachingBoxContext::GetInstance()->GetCurrentToolSys();

		/*若选择的变量已被设置*/
		if (scope == currentSys->GetScope() && name == currentSys->GetName())
		{
			return;
		}

		TeachingBoxContext::GetInstance()->SetCurrentToolSys(TVariateManager::GetInstance()->GetVariate(scope, name));
	});
	connect(m_comboBoxRobot, static_cast<void (QComboBox::*)(const QString& text)>(&QComboBox::textActivated), [this](const QString&) {
		if (m_comboBoxRobot->currentIndex() < 0)
		{
			return;
		}
		int id = m_comboBoxRobot->currentData().toInt();
		RemoteManager::GetInstance()->SendSpecialCommand(CommandId::SET_ROBOT_ID, id);
	});
}

void ScreenState::InitState()
{
	ChangeRunningState(InterpreterContext::STOP);
	ChangeServoState(false);
	UpdatePixmap(m_lbLogo,(":/new/image/Resources/Image/brand_icon.png"),Qt::KeepAspectRatio);
}

void ScreenState::ChangeRunningMode(int id)
{
	switch (id)
	{
	case InterpreterContext::AUTO:{
		UpdatePixmap(m_lbExecuteMode, ":/new/image/Resources/Image/execute_auto.png");
	}break;
	case InterpreterContext::STEP:{
		UpdatePixmap(m_lbExecuteMode, ":/new/image/Resources/Image/execute_step.png");
	}break;
	case InterpreterContext::MANUAL:{
		UpdatePixmap(m_lbExecuteMode, ":/new/image/Resources/Image/execute_manual.png");
	}break;
	default:
		break;
	}
}

void ScreenState::ChangeRunningState(int id)
{
	switch (static_cast<InterpreterContext::ExecuteState>(id))
	{
	case InterpreterContext::EXECUTING: {
		UpdatePixmap(m_lbExecuteState, ":/new/image/Resources/Image/execute_running.png");
	}break;
	case InterpreterContext::STOP:{
		UpdatePixmap(m_lbExecuteState, ":/new/image/Resources/Image/execute_stop.png");
	}break;
	default:
		break;
	}
}

void ScreenState::ChangeServoState(bool isOn)
{
	if (isOn)
	{
		UpdatePixmap(m_lbServoState, ":/new/image/Resources/Image/power_on.png");
	}
	else
	{
		UpdatePixmap(m_lbServoState, ":/new/image/Resources/Image/power_off.png");
	}
}

QLayout* ScreenState::GetFirstLayout()
{
	QHBoxLayout* layout = new QHBoxLayout(this);

	//QLabel* robotLabel = new QLabel("My Robot",this);
	//robotLabel->setAlignment(Qt::AlignCenter);
	m_comboBoxRefSys = new ComboBoxWithUniqueIcon(":/new/image/Resources/Image/coordinate_system_icon.png", this);
	m_comboBoxTool = new ComboBoxWithUniqueIcon(":/new/image/Resources/Image/tool_icon.png",this);
	m_comboBoxSpeed = new ComboBoxWithUniqueIcon(":/new/image/Resources/Image/speed_icon.png",this);
	m_comboBoxRobot = new ComboBoxWithUniqueIcon(":/new/image/Resources/Image/robot_icon.png", this);

	layout->addWidget(m_lbLogo);
	layout->addWidget(new ComboBoxWithBorder(m_comboBoxRefSys));
	layout->addWidget(new ComboBoxWithBorder(m_comboBoxTool));
	layout->addWidget(new ComboBoxWithBorder(m_comboBoxSpeed));
	layout->addWidget(m_comboBoxRobot);

	layout->setStretch(0, 4);
	layout->setStretch(1, 6);
	layout->setStretch(2, 6);
	layout->setStretch(3, 6);
	layout->setStretch(4, 4);

	layout->setSpacing(0);/*各控件间隔为0*/

	return layout;
}

QLayout* ScreenState::GetSecondLayout()
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	
	m_comboBoxProject = new ComboBoxWithUniqueIcon(PROJECT_ICON_PATH,this);
	m_comboBoxProgram = new ComboBoxWithUniqueIcon(PROGRAM_ICON_PATH,this);

	layout->addWidget(new ComboBoxWithBorder(m_comboBoxProject));
	layout->addWidget(new ComboBoxWithBorder(m_comboBoxProgram));
	layout->addWidget(m_lbServoState);
	layout->addWidget(m_lbExecuteMode);
	layout->addWidget(m_lbExecuteState);
	layout->addWidget(m_lb4);
	layout->addWidget(m_lb5);
	layout->addWidget(m_lbSpace);
	layout->addWidget(m_lbSecurityState);
	layout->addWidget(m_lbUserAuthority);
	layout->addWidget(m_lbCurrentTime);

	layout->setStretch(0, 6);
	layout->setStretch(1, 6);
	for (int i = 2; i < layout->count() - 1;++i)
	{
		layout->setStretch(i, 1);
	}

	layout->setStretch(layout->count() - 1, 4);

	layout->setSpacing(0);

	return layout;
}

void ScreenState::LoadProject(const QString& project, const QStringList& programs)
{
	m_comboBoxProject->clear();
	m_comboBoxProgram->clear();

	if (project.size()==0)
	{
		m_comboBoxProject->AddIconItem("");
		m_comboBoxProgram->AddIconItem("");
		return;
	}

	m_comboBoxProject->AddIconItem(project);
	m_comboBoxProgram->AddIconItems(programs);
}

void ScreenState::LoadFilesChanged()
{
	m_comboBoxProgram->clear();

	for (auto file : Context::projectContext.Programs())
	{
		m_comboBoxProgram->AddIconItem(file.split(".").at(1));
	}
	m_comboBoxProgram->setCurrentText(Context::projectContext.ProgramOpened().split(".").at(1));
}

void ScreenState::OpenProgram(const QString&, const QString& program)
{
	m_comboBoxProgram->setCurrentText(program);
}

void ScreenState::OnChangeVariate(std::shared_ptr<TVariate> variate)
{
	if (variate->GetTypeName() == TRefSys::TypeName())
	{
		UpdateRefSysBox();
	}
	else if (variate->GetTypeName() == TToolSys::TypeName())
	{
		UpdateToolRefBox();
	}
}

void ScreenState::UpdatePixmap(LabelWithBorder* widget, const QString& pixmapPath, Qt::AspectRatioMode aspectRatioMode /*= Qt::IgnoreAspectRatio*/,
	Qt::TransformationMode transformMode /*= Qt::SmoothTransformation*/)
{
	widget->setPixmap(QPixmap(pixmapPath).scaled(widget->width() - widget->GetBorderWidth() * 2,
		widget->height() - widget->GetBorderWidth() * 2, aspectRatioMode, transformMode));
}


ScreenState::ComboBoxWithBorder::ComboBoxWithBorder(QComboBox* widget, QWidget* parent /*= 0*/)
	:LabelWithBorder(parent)
	, m_widget(widget)
	, m_layout(new QHBoxLayout(this))
{
	m_layout->setSpacing(0);
	m_layout->setMargin(0);

	m_layout->addWidget(widget);
}

void ScreenState::ComboBoxWithBorder::showEvent(QShowEvent *)
{
	m_widget->setFixedHeight(this->height());
}

ScreenState::ComboBoxWithUniqueIcon::ComboBoxWithUniqueIcon(const QString& iconPath, QWidget* parent /*= 0*/)
	:QComboBox(parent)
	, m_iconPath(iconPath)
{
	setIconSize(QSize(this->height(), this->height()));
	AddIconItem("");
}

void ScreenState::ComboBoxWithUniqueIcon::AddIconItem(const QString& text)
{
	QComboBox::addItem(QIcon(QPixmap(m_iconPath)), text);
}

void ScreenState::ComboBoxWithUniqueIcon::AddIconItem(const QString& text, const QVariant& userData)
{
	QComboBox::addItem(QIcon(QPixmap(m_iconPath)), text, userData);
}

void ScreenState::ComboBoxWithUniqueIcon::AddIconItems(const QStringList& texts)
{
	for (auto text:texts)
	{
		AddIconItem(text);
	}
}
