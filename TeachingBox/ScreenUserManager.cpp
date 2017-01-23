#include "stdafx.h"
#include "ScreenUserManager.h"
#include "Button.h"
#include "DialogEditUser.h"
#include "QList"
#include "User.h"
#include "UserDatabase.h"
#include "QMessageBox"
#include "TeachingBoxInitialization.h"

using namespace Database;

ScreenUserManager::ScreenUserManager(QWidget* parent)
	:InternationalWidget(parent)
	, m_tableWidget(new QTableWidget(this))
	, m_btnNew(new Button(this))
	, m_btnEdit(new Button(this))
	, m_btnDelete(new Button(this))
{
	Init();
}

ScreenUserManager::~ScreenUserManager()
{

}

void ScreenUserManager::OnUpdate()
{
	int currentAuthority = TeachingBoxContext::GetInstance()->GetUser().GetAuthority();
	QList<User> suitableUsers;

	QList<User> allUsers = UserDatabase::SelectAllUsers();
	for (auto var : allUsers)
	{
		if (var.GetAuthority() <= currentAuthority)
		{
			suitableUsers.append(var);
		}
	}

	m_tableWidget->setRowCount(suitableUsers.size());

	int index = 0;
	for (auto user:suitableUsers)
	{
		m_tableWidget->setItem(index, 0, new QTableWidgetItem(user.GetName()));
		m_tableWidget->setItem(index, 1, new QTableWidgetItem(QString::number(user.GetAuthority())));
		m_tableWidget->setItem(index, 2, new QTableWidgetItem(user.GetLanguage()));

		++index;
	}
}

void ScreenUserManager::showEvent(QShowEvent *)
{
	OnUpdate();
}

QLayout* ScreenUserManager::GetButtonLayout()
{
	QHBoxLayout* layout = new QHBoxLayout;

	layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));
	layout->addWidget(m_btnEdit);
	layout->addWidget(m_btnNew);
	layout->addWidget(m_btnDelete);
	layout->addSpacerItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Preferred));

	return layout;
}

QLayout* ScreenUserManager::GetMainLayout()
{
	/*添加用户列表*/
	m_tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);	/*整行选中*/
	m_tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);	/*禁止编辑*/

	/*平均分布各列*/
	m_tableWidget->setColumnCount(3);
	m_tableWidget->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
	m_tableWidget->horizontalHeader()->setDefaultAlignment(Qt::AlignCenter);

	QHBoxLayout* layout = new QHBoxLayout;
	layout->addWidget(m_tableWidget);

	return layout;
}

void ScreenUserManager::Init()
{
	InitLayout();
	InitSignalSlot();

	UpdateText();
}

void ScreenUserManager::InitLayout()
{
	/*总布局*/
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->addLayout(GetMainLayout());
	layout->addLayout(GetButtonLayout());
	layout->setStretch(0, 1);
	layout->setStretch(1, 0);
}

void ScreenUserManager::InitSignalSlot()
{
	connect(m_btnNew, SIGNAL(clicked()), this, SLOT(SlotOnNewButtonClicked()));
	connect(m_btnEdit, SIGNAL(clicked()), this, SLOT(SlotOnEditButtonClicked()));
	connect(m_btnDelete, SIGNAL(clicked()), this, SLOT(SlotOnDeleteButtonClicked()));
}

bool ScreenUserManager::IsCouldDelete(const User& user)
{
	/*若操作对象为管理员*/
	if (user.GetName()==TeachingBoxInitialization::Adminastrator()->GetName())
	{
		return false;
	}

	/*若操作者与操作对象权限相同*/
	if(user.GetAuthority() == TeachingBoxContext::GetInstance()->GetUser().GetAuthority())
	{
		/*若操作者为管理员*/
		if (TeachingBoxContext::GetInstance()->GetUser().GetName() == TeachingBoxInitialization::Adminastrator()->GetName())
		{
			return true;
		}
		
		return false;
	}

	return TeachingBoxContext::GetInstance()->GetUser().GetAuthority()>user.GetAuthority();
}

bool ScreenUserManager::IsCouldEdit(const User& user)
{
	/*若操作者为管理员*/
	if (TeachingBoxContext::GetInstance()->GetUser().GetName() == TeachingBoxInitialization::Adminastrator()->GetName())
	{
		return true;
	}
	/*若操作者与操作对象权限相同*/
	if (user.GetAuthority() == TeachingBoxContext::GetInstance()->GetUser().GetAuthority())
	{
		/*若操作者为操作对象本身*/
		if (TeachingBoxContext::GetInstance()->GetUser().GetName() == user.GetName())
		{
			return true;
		}

		return false;
	}

	return TeachingBoxContext::GetInstance()->GetUser().GetAuthority()>user.GetAuthority();
}

void ScreenUserManager::UpdateText()
{
	m_btnNew->setText(tr("New"));
	m_btnEdit->setText(tr("Edit"));
	m_btnDelete->setText(tr("Delete"));

	QStringList strHeader;
	strHeader << tr("User")
		<< tr("Authority")
		<< tr("Language");
	m_tableWidget->setHorizontalHeaderLabels(strHeader);
}

void ScreenUserManager::SlotOnNewButtonClicked()
{
	(new DialogEidtUser(this,this,DialogEidtUser::ADD))->show();
}

void ScreenUserManager::SlotOnEditButtonClicked()
{
	auto item = m_tableWidget->item(m_tableWidget->currentRow(), 0);
	if (item==nullptr)
	{
		return;
	}
	QString name = item->text();
	User user = UserDatabase::SelectUser(name);

	if (IsCouldEdit(user))
	{
		(new DialogEidtUser(this, this, DialogEidtUser::EDIT, name))->show();
	}
	else
	{
		QMessageBox::warning(this, tr("Operator failed"), tr("Cann't edit user: ") + name);
	}
}

void ScreenUserManager::SlotOnDeleteButtonClicked()
{
	int row = m_tableWidget->currentRow();
	if (row < 0)
	{
		QMessageBox::warning(this, tr("Warning"),tr("Please Select An User"));
		return;
	}

	/*获取删除的用户名*/
	QString userName = m_tableWidget->item(row, 0)->text();

	/*获取要删除的用户*/
	User user=UserDatabase::SelectUser(userName);

	if (IsCouldDelete(user))
	{
		switch (QMessageBox::question(this, tr("Delete User"), userName,
			QMessageBox::Ok | QMessageBox::Cancel, QMessageBox::Ok))
		{
		case QMessageBox::Ok:
		{
			UserDatabase::DeleteUserInfo(userName);
			OnUpdate();
		}break;
		case QMessageBox::Cancel:
		{
			return;
		}break;
		default:
			break;
		}
	}
	else
	{
		QMessageBox::warning(this, tr("Operator failed"), tr("Cann't delete user: ") + user.GetName());
	}

	
}
