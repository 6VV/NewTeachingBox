#include "stdafx.h"
#include "ScreenService.h"
#include "ScreenSetting.h"
#include "Button.h"
#include "ScreenUser.h"
#include "ScreenUserManager.h"
#include "ScreenNetwork.h"
#include "TeachingBoxContext.h"
#include "TeachingBoxBroadcast.h"
#include "ScreenRobot.h"



ScreenService::ScreenService(QWidget* parent)
	:ScreenMainParent(parent)
	, m_stackedWidget(new QStackedWidget(this))
	, m_screenUser(new ScreenUser(this))
	, m_screenSetting(new ScreenSetting(this))
	, m_screenUserManager(new ScreenUserManager(this))
	, m_screenNetwork(new ScreenNetwork(this))
	, m_screenRobot(new ScreenRobot(this))
	, m_btnSetting(new Button(this))
	, m_btnUser(new Button(this))
	, m_btnUserManager(new Button(this))
	, m_btnRobot(new Button(this))
	, m_btnNetwork(new Button(this))
	, m_btnInformation(new Button(this))
{
	Init();
}

ScreenService::~ScreenService()
{

}

void ScreenService::Init()
{
	InitStackedWidget();
	InitSignalSlot();

	UpdateText();

	m_btnUser->setEnabled(false);
	m_btnUserManager->setEnabled(false);
}

void ScreenService::InitStackedWidget()
{
	m_stackedWidget->addWidget(m_screenSetting);
	m_stackedWidget->addWidget(m_screenUser);
	m_stackedWidget->addWidget(m_screenUserManager);
	m_stackedWidget->addWidget(m_screenNetwork);
	m_stackedWidget->addWidget(m_screenRobot);
}

void ScreenService::InitSignalSlot()
{
	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::CurrentUserChanged, this, [this]{
		if (TeachingBoxContext::GetInstance()->GetUser().GetName().size()==0)
		{
			m_btnUserManager->setEnabled(false);
			m_btnUser->setEnabled(false);
		}
		else
		{
			m_btnUserManager->setEnabled(true);
			m_btnUser->setEnabled(true);
		}
	});

	connect(m_btnSetting, SIGNAL(clicked()), this, SLOT(SlotOnChangeToScreenSetting()));
	connect(m_btnUser, SIGNAL(clicked()), this, SLOT(SlotOnChangeToScreenUser()));
	connect(m_btnUserManager, SIGNAL(clicked()), this, SLOT(SlotOnChangeToScreenUserManager()));
	connect(m_btnNetwork, SIGNAL(clicked()), this, SLOT(SlotOnChangeToScreenNetwork()));
	connect(m_btnRobot, &QPushButton::clicked, this, [this]() {
		m_stackedWidget->setCurrentWidget(m_screenRobot);
	});
}

void ScreenService::UpdateControlerEnabled()
{
	User user = TeachingBoxContext::GetInstance()->GetUser();
	if (user.GetName() == "")
	{
		UpdateControlerEnabled(false);
	}
	else
	{
		UpdateControlerEnabled(true);
	}
}

void ScreenService::UpdateControlerEnabled(bool enabled)
{
	m_btnSetting->setEnabled(false);
	m_btnUser->setEnabled(enabled);
	m_btnUserManager->setEnabled(enabled);
	m_btnInformation->setEnabled(enabled);
	m_btnRobot->setEnabled(enabled);
	m_btnNetwork->setEnabled(enabled);
}

void ScreenService::UpdateText()
{
	m_btnSetting->setText(tr("Setting"));
	m_btnUser->setText(tr("User"));
	m_btnUserManager->setText(tr("UserAdmin"));
	m_btnRobot->setText(tr("Robot"));
	m_btnInformation->setText(tr("Information"));
	m_btnNetwork->setText(tr("Network"));
}

QList<QWidget*> ScreenService::GetButtonList()
{
	QList<QWidget*> btnList;
	btnList.append(m_btnSetting);
	btnList.append(m_btnUser);
	btnList.append(m_btnUserManager);
	btnList.append(m_btnRobot);
	btnList.append(m_btnInformation);
	btnList.append(m_btnNetwork);
	return btnList;
}

QLayout* ScreenService::GetMainLayout()
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->addWidget(m_stackedWidget);
	return layout;
}

void ScreenService::showEvent(QShowEvent *e)
{
	ScreenMainParent::showEvent(e);
	//UpdateControlerEnabled();
}

void ScreenService::SlotOnChangeToScreenSetting()
{
	m_stackedWidget->setCurrentWidget(m_screenSetting);
}

void ScreenService::SlotOnChangeToScreenUser()
{
	m_stackedWidget->setCurrentWidget(m_screenUser);
}

void ScreenService::SlotOnChangeToScreenUserManager()
{
	m_stackedWidget->setCurrentWidget(m_screenUserManager);
}

void ScreenService::SlotOnChangeToScreenNetwork()
{
	m_stackedWidget->setCurrentWidget(m_screenNetwork);
}
