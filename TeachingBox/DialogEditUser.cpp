#include "stdafx.h"
#include "DialogEditUser.h"
#include "QLabel"
#include "QLineEdit"
#include "QComboBox"
#include "QCheckBox"
#include "Button.h"
#include "TeachingBoxContext.h"
#include "Language.h"
#include "IUserManager.h"
#include "UserDatabase.h"

using namespace Database;

DialogEidtUser::DialogEidtUser(QWidget* parent, IUserManager* userManager, OperatorType type, const QString& name/*=""*/)
	:DialogParent(parent)
	, m_userManager(userManager)
	, m_type(type)
	, m_oldName(name)
	, m_lbName(new QLabel(this))
	, m_lbPassword(new QLabel(this))
	, m_lbConfirmPassword(new QLabel(this))
	, m_lbAuthority(new QLabel(this))
	, m_lbLanguage(new QLabel(this))
	, m_lineEditName(new QLineEdit(this))
	, m_lineEditPassword(new QLineEdit(this))
	, m_lineEditConfirmPassword(new QLineEdit(this))
	, m_comboBoxAuthority(new QComboBox(this))
	, m_comboBoxLanguage(new QComboBox(this))
	, m_btnConfirm(new Button(this))
	, m_btnCancel(new Button(this))
{
	Init();
}

void DialogEidtUser::showEvent(QShowEvent *e)
{
	DialogParent::showEvent(e);

	///*设置固定大小*/
	//this->setFixedSize(this->width(), this->height());

	///*移动到屏幕中央*/
	//this->move(TeachingBoxContext::GetScreenRect().left()+ TeachingBoxContext::GetScreenRect().width() / 2 - this->width() / 2,
	//	TeachingBoxContext::GetScreenRect().top() + TeachingBoxContext::GetScreenRect().height() / 2 - this->height() / 2);

	InitUser();
}

void DialogEidtUser::UpdateText()
{
	m_lbName->setText(tr("Name"));
	m_lbPassword->setText(tr("Password"));
	m_lbConfirmPassword->setText(tr("Confirm Password"));
	m_lbAuthority->setText(tr("Authority"));
	m_lbLanguage->setText(tr("Language"));
	m_btnConfirm->setText(tr("Confirm"));
	m_btnCancel->setText(tr("Cancel"));
}

void DialogEidtUser::SetSize()
{
	this->setFixedSize(this->width(), this->height());
}

void DialogEidtUser::Init()
{
	InitLayout();
	InitSignalSlot();
	UpdateText();
}

void DialogEidtUser::InitLayout()
{
	//this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint );
	//this->setWindowModality(Qt::ApplicationModal);

	m_lineEditPassword->setEchoMode(QLineEdit::Password);
	m_lineEditConfirmPassword->setEchoMode(QLineEdit::Password);

	User user = TeachingBoxContext::GetInstance()->GetUser();

	/*添加权限，最大权限不得超过当前用户的权限*/
	for (int i = 1; i <= user.GetAuthority(); ++i)
	{
		m_comboBoxAuthority->addItem(QString::number(i));
	}

	m_comboBoxLanguage->addItem(Language::English());
	m_comboBoxLanguage->addItem(Language::Chinese());
	m_comboBoxLanguage->setCurrentText(user.GetLanguage());

	/*布局*/
	QVBoxLayout* layoutMain = new QVBoxLayout(this);
	QGridLayout* layoutUser = new QGridLayout;
	QHBoxLayout* layoutButton = new QHBoxLayout;

	layoutMain->addLayout(layoutUser);
	layoutMain->addLayout(layoutButton);
	layoutMain->setStretch(0, 1);

	layoutUser->setMargin(10);
	layoutUser->setSpacing(10);

	layoutUser->addWidget(m_lbName, 0, 0);
	layoutUser->addWidget(m_lbPassword, 1, 0);
	layoutUser->addWidget(m_lbConfirmPassword, 2, 0);
	layoutUser->addWidget(m_lbAuthority, 3, 0);
	layoutUser->addWidget(m_lbLanguage, 4, 0);

	layoutUser->addWidget(m_lineEditName, 0, 1);
	layoutUser->addWidget(m_lineEditPassword, 1, 1);
	layoutUser->addWidget(m_lineEditConfirmPassword, 2, 1);
	layoutUser->addWidget(m_comboBoxAuthority, 3, 1);
	layoutUser->addWidget(m_comboBoxLanguage, 4, 1);

	layoutButton->addStretch(0);
	layoutButton->addWidget(m_btnConfirm);
	layoutButton->addStretch(0);
	layoutButton->addWidget(m_btnCancel);
	layoutButton->addStretch(0);

}

void DialogEidtUser::InitSignalSlot()
{
	connect(m_btnCancel, SIGNAL(clicked()), this, SLOT(SlotOnButtonCancleClicked()));
	connect(m_btnConfirm, SIGNAL(clicked()), this, SLOT(SlotOnButtonConfirmClicked()));
}

void DialogEidtUser::InitUser()
{
	switch (m_type)
	{
	case DialogEidtUser::EDIT:
	{
		User user = UserDatabase::SelectUser(m_oldName);
		m_lineEditName->setText(user.GetName());
		m_lineEditPassword->setText(user.GetPassword());
		m_lineEditConfirmPassword->setText(user.GetPassword());
		m_comboBoxAuthority->setCurrentText(QString::number(user.GetAuthority()));
		m_comboBoxLanguage->setCurrentText(user.GetLanguage());

		/*若编辑对象为自身，则禁止修改名字与权限*/
		if (m_oldName==TeachingBoxContext::GetInstance()->GetUser().GetName())
		{
			m_lineEditName->setEnabled(false);
			m_comboBoxAuthority->setEnabled(false);
		}
	}break;
	default:
		break;
	}
}

void DialogEidtUser::SlotOnButtonConfirmClicked()
{
	QString name = m_lineEditName->text();
	QString password = m_lineEditPassword->text();
	QString confirmPassword = m_lineEditConfirmPassword->text();

	if (name.simplified().size() == 0) 
	{
		QMessageBox::warning(this, tr("Operator failed"), tr("Name cann't be empty"));
		return;
	}

	if (password.size() == 0)
	{
		QMessageBox::warning(this, tr("Operator failed"), tr("Password cann't be empty"));
		return;
	}

	if (confirmPassword.size() == 0)
	{
		QMessageBox::warning(this, tr("Operator failed"), tr("Confirm Password cann't be empty"));
		return;
	}

	if (password!=confirmPassword)
	{
		QMessageBox::warning(this, tr("Operator failed"), tr("Password is not equal to confirm password"));
		return;
	}

	int authority = m_comboBoxAuthority->currentText().toInt();
	QString language = m_comboBoxLanguage->currentText();
	User user(name, password, authority, language);

	switch (m_type)
	{
	case DialogEidtUser::ADD:
	{
		UserDatabase::InsertUserInfo(user);
	}break;
	case DialogEidtUser::EDIT:
	{
		UserDatabase::UpdateUserInfo(m_oldName, user);
	}break;
	default:
		break;
	}
	m_userManager->OnUpdate();
	delete this;
}

void DialogEidtUser::SlotOnButtonCancleClicked()
{
	delete this;
}
