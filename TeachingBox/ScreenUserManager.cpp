#include "stdafx.h"
#include "ScreenUserManager.h"
#include "Button.h"



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
