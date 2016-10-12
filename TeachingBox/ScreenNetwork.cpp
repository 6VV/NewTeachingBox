#include "stdafx.h"
#include "ScreenNetwork.h"
#include "Button.h"
#include "QListWidget"
#include "QBoxLayout"
#include "DialogNewAddress.h"
#include "TcpManager.h"
#include "WarningManager.h"
#include "RegExp.h"



ScreenNetwork::ScreenNetwork(QWidget* parent)
	:InternationalWidget(parent)
	, m_listWidgetHost(new QListWidget(this))
	, m_btnAdd(new Button(this))
	, m_btnDelete(new Button(this))
	, m_btnConnect(new Button(this))
{
	Init();
}

ScreenNetwork::~ScreenNetwork()
{

}


void ScreenNetwork::UpdateText()
{
	m_btnAdd->setText(tr("Add"));
	m_btnDelete->setText(tr("Delete"));
	m_btnConnect->setText(tr("Connect"));
}

void ScreenNetwork::Init()
{
	InitLayout();
	InitSignalSlot();
	UpdateText();

	m_listWidgetHost->addItem(TcpManager::LocalIPAddress());
}

void ScreenNetwork::InitLayout()
{
	QHBoxLayout* layout = new QHBoxLayout(this);

	QVBoxLayout* layoutButton = new QVBoxLayout(this);
	layoutButton->addWidget(m_btnAdd);
	layoutButton->addWidget(m_btnDelete);
	layoutButton->addWidget(m_btnConnect);
	layoutButton->addStretch(1);

	layout->addWidget(m_listWidgetHost);
	layout->addLayout(layoutButton);

	layout->setStretch(0, 1);
}

void ScreenNetwork::InitSignalSlot()
{
	connect(m_btnAdd, SIGNAL(clicked()), this, SLOT(SlotOnAddClicked()));
	connect(m_btnDelete, SIGNAL(clicked()), this, SLOT(SlotOnDeleteClicked()));
	connect(m_btnConnect, SIGNAL(clicked()), this, SLOT(SlotOnConnectClicked()));
}

bool ScreenNetwork::IsValidAddress(const QString& address)
{
	QRegExp regExp(RegExp::STR_REG_IP_ADDRESS);

	return regExp.exactMatch(address);
}

void ScreenNetwork::SlotOnAddClicked()
{
	(new DialogNewAddress(this, this))->show();
}

void ScreenNetwork::SlotOnDeleteClicked()
{
	delete m_listWidgetHost->takeItem(m_listWidgetHost->currentRow());
}

void ScreenNetwork::SlotOnConnectClicked()
{
	if (m_listWidgetHost->currentItem()==nullptr)
	{
		WarningManager::Warning(this, tr("Please select an address"));
		return;
	}

	auto address = m_listWidgetHost->currentItem()->text();
	if (!IsValidAddress(address))
	{
		WarningManager::Warning(this, tr("Not valid address"));
		return;
	}

	TcpManager::GetInstance()->ConnectAddress(address);
}

void ScreenNetwork::OnNewAddress(const QString& address)
{
	m_listWidgetHost->addItem(address);
}
