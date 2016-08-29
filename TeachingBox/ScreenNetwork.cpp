#include "stdafx.h"
#include "ScreenNetwork.h"
#include "Button.h"
#include "QListWidget"
#include "QBoxLayout"



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
	UpdateText();
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
