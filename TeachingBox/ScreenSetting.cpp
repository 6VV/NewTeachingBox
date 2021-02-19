#include "stdafx.h"
#include "ScreenSetting.h"
#include "QGridLayout"
#include "Button.h"
#include "Language.h"
#include "TeachingBoxContext.h"
#include "UserDatabase.h"
#include "Keyboard.h"
#include "TeachingBoxBroadcast.h"
#include "DialogLockScreen.h"



ScreenSetting::ScreenSetting(QWidget* parent)
	:InternationalWidget(parent)
{
	Init();
}

ScreenSetting::~ScreenSetting()
{

}

void ScreenSetting::UpdateText()
{
	/*登录窗口*/
	m_groupboxLogin->setTitle(tr("Login"));
	m_lbUser->setText(tr("User"));
	m_lbAuthority->setText(tr("Level"));
	m_btnLogout->setText(tr("Logout"));

	/*系统设置窗口*/
	m_groupboxSystemSettings->setTitle(tr("System settings"));
	m_lbLanguage->setText(tr("Language"));
	m_lbDate->setText(tr("Date"));
	m_lbTime->setText(tr("time"));

	/*机器人控制权限窗口*/
	m_groupboxRobotControlAuthority->setTitle(tr("Robot control authority"));
	m_lbControlAuthority->setText(tr("Control authority"));
	m_lbDevice->setText(tr("Device"));
	m_lbDeviceIp->setText(tr("Device IP"));

	/*显示设置窗口*/
	m_groupboxDispaySettings->setTitle(tr("Display setting"));
	m_lbLockScreen->setText(tr("Displaylock"));
	m_btnLockScreen->setText(tr("Lock"));
	m_lbLockTime->setText(tr("Lock Time(s)"));

	/*更新日期时间*/
	QDateTime dateTime = QDateTime::currentDateTime();
	QString date = dateTime.toString("yyyy-MM-dd");
	QString time = dateTime.toString("hh:mm:ss");
	m_ltDateValue->setText(date);
	m_ltTimeValue->setText(time);
}

void ScreenSetting::UpdateState(const User& user)
{
	m_cmbUser->setCurrentText(user.GetName());
	m_ltAuthorityValue->setText(QString::number(user.GetAuthority()));
	m_cmbLanguage->setCurrentText(user.GetLanguage());

	if (user.GetName().size()==0)
	{
		m_btnLogout->setEnabled(false);
	}
	else
	{
		m_btnLogout->setEnabled(true);
	}

	emit(TeachingBoxBroadcast::GetInstance()->CurrentUserChanged());
}

void ScreenSetting::Init()
{
	QGridLayout* layout = new QGridLayout(this);

	layout->addWidget(CreateBoxLogin(), 0, 0);
	layout->addWidget(CreateBoxSystemSettings(), 0, 1);
	layout->addWidget(CreateBoxRobotControlAuthority(), 1, 0);
	layout->addWidget(CreateBoxLockScreenSetting(), 1, 1);

	layout->setRowStretch(0, 1);
	layout->setRowStretch(1, 1);
	layout->setColumnStretch(0, 1);
	layout->setColumnStretch(1, 1);
	layout->setSpacing(5);
	layout->setMargin(5);

	UpdateText();
}

QGroupBox* ScreenSetting::CreateBoxLogin()
{
	m_groupboxLogin = new QGroupBox(this);

	/*布局*/
	QVBoxLayout* layoutLogin = new QVBoxLayout(m_groupboxLogin);
	QHBoxLayout* layoutUser = new QHBoxLayout;
	QHBoxLayout* layoutLevel = new QHBoxLayout;
	QHBoxLayout* layoutLogout = new QHBoxLayout;

	layoutLogin->addStretch(0);
	layoutLogin->addLayout(layoutUser);
	layoutLogin->addStretch(0);
	layoutLogin->addLayout(layoutLevel);
	layoutLogin->addStretch(0);
	layoutLogin->addLayout(layoutLogout);
	layoutLogin->addStretch(0);

	/*创建窗口控件*/
	m_lbUser = new QLabel(this);
	m_lbAuthority = new QLabel(this);
	m_ltAuthorityValue = new QLineEdit("1",this);
	m_cmbUser = new QComboBox(this);
	connect(m_cmbUser, static_cast<void (QComboBox::*)(const QString& text)>(&QComboBox::textActivated), [this](const QString& name){
		auto lastUserName = TeachingBoxContext::GetInstance()->GetUser().GetName();
		if (name == lastUserName || name.size()==0)
		{
			return;
		}
		Keyboard::GetInstance()->SetKeyboardInterface(this);
		Keyboard::GetInstance()->SetEchoMode(QLineEdit::Password);
		Keyboard::GetInstance()->show();
	});

	m_btnLogout = new Button(this);
	m_btnLogout->setEnabled(false);
	connect(m_btnLogout, &Button::clicked, this, [this]{
		User user{};
		TeachingBoxContext::GetInstance()->SetUser(user);
		UpdateState(user);
	});

	/*添加控件并布局*/
	layoutUser->addWidget(m_lbUser);
	layoutUser->addWidget(m_cmbUser);
	layoutUser->setStretch(0, 1);
	layoutUser->setStretch(1, 1);

	layoutLevel->addWidget(m_lbAuthority);
	layoutLevel->addWidget(m_ltAuthorityValue);
	layoutLevel->setStretch(0, 1);
	layoutLevel->setStretch(1, 1);

	layoutLogout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding));
	layoutLogout->addWidget(m_btnLogout);
	layoutLogout->setStretch(0, 1);
	layoutLogout->setStretch(1, 1);

	/*设置控件样式*/
	m_ltAuthorityValue->setAlignment(Qt::AlignRight | Qt::AlignCenter);
	m_ltAuthorityValue->setEnabled(false);

	return m_groupboxLogin;
}

QGroupBox* ScreenSetting::CreateBoxSystemSettings()
{
	/*新窗口*/
	m_groupboxSystemSettings = new QGroupBox;

	/*布局*/
	QVBoxLayout* layoutSystemSettings = new QVBoxLayout(m_groupboxSystemSettings);
	QHBoxLayout* layoutLanguage = new QHBoxLayout;
	QHBoxLayout* layoutDate = new QHBoxLayout;
	QHBoxLayout* layoutTime = new QHBoxLayout;

	layoutSystemSettings->addStretch(0);
	layoutSystemSettings->addLayout(layoutLanguage);
	layoutSystemSettings->addStretch(0);
	layoutSystemSettings->addLayout(layoutDate);
	layoutSystemSettings->addStretch(0);
	layoutSystemSettings->addLayout(layoutTime);
	layoutSystemSettings->addStretch(0);

	/*创建窗口控件并布局*/
	m_lbLanguage = new QLabel;
	m_lbDate = new QLabel;
	m_lbTime = new QLabel;
	m_cmbLanguage = new QComboBox;
	m_ltDateValue = new QLineEdit;
	m_ltTimeValue = new QLineEdit;

	layoutLanguage->addWidget(m_lbLanguage);
	layoutLanguage->addWidget(m_cmbLanguage);
	layoutLanguage->setStretch(0, 1);
	layoutLanguage->setStretch(1, 1);

	layoutDate->addWidget(m_lbDate);
	layoutDate->addWidget(m_ltDateValue);
	layoutDate->setStretch(0, 1);
	layoutDate->setStretch(1, 1);

	layoutTime->addWidget(m_lbTime);
	layoutTime->addWidget(m_ltTimeValue);
	layoutTime->setStretch(0, 1);
	layoutTime->setStretch(1, 1);

	/*为控件添加内容*/
	for (auto var :Language::LANGUAGES)
	{
		m_cmbLanguage->addItem(var.first, var.second);
	}
	connect(m_cmbLanguage, SIGNAL(currentIndexChanged(int)), this, SLOT(SlotChangeLanguage(int)));

	/*设置控件样式*/
	//m_ltDateValue->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
	//m_ltTimeValue->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
	m_ltDateValue->setEnabled(false);
	m_ltTimeValue->setEnabled(false);

	return m_groupboxSystemSettings;
}

QGroupBox* ScreenSetting::CreateBoxRobotControlAuthority()
{
	/*创建窗口*/
	m_groupboxRobotControlAuthority = new QGroupBox;

	/*布局*/
	QVBoxLayout* layoutRobotControlAuthority = new QVBoxLayout(m_groupboxRobotControlAuthority);
	QHBoxLayout* layoutControlAuthority = new QHBoxLayout;
	QHBoxLayout* layoutDevice = new QHBoxLayout;
	QHBoxLayout* layoutDeviceIp = new QHBoxLayout;

	layoutRobotControlAuthority->addStretch(0);
	layoutRobotControlAuthority->addLayout(layoutControlAuthority);
	layoutRobotControlAuthority->addStretch(0);
	layoutRobotControlAuthority->addLayout(layoutDevice);
	layoutRobotControlAuthority->addStretch(0);
	layoutRobotControlAuthority->addLayout(layoutDeviceIp);
	layoutRobotControlAuthority->addStretch(0);

	/*创建窗口控件并布局*/
	m_lbControlAuthority = new QLabel;
	m_checkboxControlAuthority = new QCheckBox;
	m_checkboxControlAuthority->setChecked(false);
	m_lbDevice = new QLabel;
	m_ltDeviceValue = new QLineEdit;
	m_lbDeviceIp = new QLabel;
	m_ltDeviceIpValue = new QLineEdit;

	layoutControlAuthority->addWidget(m_lbControlAuthority);
	layoutControlAuthority->addWidget(m_checkboxControlAuthority);
	layoutControlAuthority->setStretch(0, 1);
	layoutControlAuthority->setStretch(1, 1);
	layoutControlAuthority->setAlignment(m_checkboxControlAuthority, Qt::AlignRight);

	layoutDevice->addWidget(m_lbDevice);
	layoutDevice->addWidget(m_ltDeviceValue);
	layoutDevice->setStretch(0, 1);
	layoutDevice->setStretch(1, 1);

	layoutDeviceIp->addWidget(m_lbDeviceIp);
	layoutDeviceIp->addWidget(m_ltDeviceIpValue);
	layoutDeviceIp->setStretch(0, 1);
	layoutDeviceIp->setStretch(1, 1);

	/*设置控件样式*/
	//m_ltDeviceValue->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
	//m_ltDeviceIpValue->setFrameStyle(QFrame::WinPanel | QFrame::Sunken);
	m_ltDeviceValue->setEnabled(false);
	m_ltDeviceIpValue->setEnabled(false);

	return m_groupboxRobotControlAuthority;
}

QGroupBox* ScreenSetting::CreateBoxLockScreenSetting()
{
	/*创建窗口*/
	m_groupboxDispaySettings = new QGroupBox;

	/*布局*/
	QVBoxLayout* layoutDisplaySetting = new QVBoxLayout(m_groupboxDispaySettings);
	QHBoxLayout* layoutDisplayLock = new QHBoxLayout(this);
	QHBoxLayout* layoutLockTime = new QHBoxLayout(this);

	layoutDisplaySetting->addStretch(1);
	layoutDisplaySetting->addLayout(layoutLockTime);
	layoutDisplaySetting->addLayout(layoutDisplayLock);
	layoutDisplaySetting->addStretch(1);

	/*创建窗口控件并布局*/
	m_lbLockTime = new QLabel;
	m_ltLockTimeValue = new QLineEdit("16");
	m_ltLockTimeValue->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,3}"), m_ltLockTimeValue));

	layoutLockTime->addWidget(m_lbLockTime);
	layoutLockTime->addWidget(m_ltLockTimeValue);
	layoutLockTime->setStretch(0, 1);
	layoutLockTime->setStretch(1, 1);

	m_lbLockScreen = new QLabel;
	m_btnLockScreen = new Button;
	connect(m_btnLockScreen, &Button::clicked, this, [this]{
		(new DialogLockScreen(this,m_ltLockTimeValue->text().toInt()))->show();
	});

	layoutDisplayLock->addWidget(m_lbLockScreen);
	layoutDisplayLock->addWidget(m_btnLockScreen);
	layoutDisplayLock->setStretch(0, 1);
	layoutDisplayLock->setStretch(1, 1);

	return m_groupboxDispaySettings;
}

void ScreenSetting::showEvent(QShowEvent *)
{
	m_cmbUser->clear();
	m_cmbUser->addItem("");
	auto users = Database::UserDatabase::SelectAllUsers();
	for (auto u:users)
	{
		m_cmbUser->addItem(u.GetName());
	}

	User user = TeachingBoxContext::GetInstance()->GetUser();

	m_cmbUser->setCurrentText(user.GetName());
	m_ltAuthorityValue->setText(QString::number(user.GetAuthority()));
	m_cmbLanguage->setCurrentText(TeachingBoxContext::GetInstance()->GetLanguage());

	connect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::DateTimeChanged, this, [this](const QDateTime& dateTime){
		m_ltDateValue->setText(dateTime.toString("yyyy-MM-dd"));
		m_ltTimeValue->setText(dateTime.toString("hh::mm::ss"));
	});
}

void ScreenSetting::hideEvent(QHideEvent *event)
{
	InternationalWidget::hideEvent(event);
	disconnect(TeachingBoxBroadcast::GetInstance(), &TeachingBoxBroadcast::DateTimeChanged, this, 0);
}

void ScreenSetting::SlotChangeLanguage(int index)
{
	static QTranslator* translator = nullptr;
	if (translator != nullptr)
	{
		qApp->removeTranslator(translator);
		delete(translator);
		translator = nullptr;
	}
	translator = new QTranslator;

	QString languate = m_cmbLanguage->itemData(index).toString();
	QString text = QString(":/TeachingBox/teachingbox_%1.qm").arg(languate);
	if (translator->load(text))
	{
		qApp->installTranslator(translator);
	}
	TeachingBoxContext::GetInstance()->SetLanguage(m_cmbLanguage->currentText());

}

void ScreenSetting::KeyboardEdit(const QString& text)
{
	auto user = Database::UserDatabase::SelectUser(m_cmbUser->currentText());
	if (text==user.GetPassword())
	{
		TeachingBoxContext::GetInstance()->SetUser(user);
		UpdateState(user);
	}
	else
	{
		QMessageBox::warning(this, tr("Log failed"), tr("Password wrong"));
	}

}

