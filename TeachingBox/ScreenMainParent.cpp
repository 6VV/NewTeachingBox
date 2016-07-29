#include "stdafx.h"
#include "ScreenMainParent.h"
#include "QBoxLayout"
#include "Button.h"



ScreenMainParent::ScreenMainParent(QWidget* parent)
	:InternationalWidget(parent)
	, m_btnBack(new Button("<-", this))
{
	Init();
}

ScreenMainParent::~ScreenMainParent()
{

}

void ScreenMainParent::UpdateButtonLayout(const QList<QPushButton*>& btnList)
{
	for (auto var : btnList)
	{
		m_layoutButtons->addWidget(var);
	}

	int lastNum = BUTTON_MAX_NUM - btnList.size();
	for (int i = 0; i < lastNum; i++)
	{
		Button* btn = new Button(this);
		m_layoutButtons->addWidget(btn);
		btn->setEnabled(false);
	}

	m_layoutButtons->addWidget(m_btnBack);
}

void ScreenMainParent::showEvent(QShowEvent *)
{
	if (m_isFirstShow)
	{
		m_layoutMain->addLayout(GetMainLayout());
		UpdateButtonLayout(GetButtonList());

		m_isFirstShow = false;
	}
}

void ScreenMainParent::Init()
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	m_layoutMain = new QHBoxLayout(this);
	m_layoutButtons = new QHBoxLayout(this);
	layout->addLayout(m_layoutMain, HEAD_HEIGHT_RATIO);
	layout->addLayout(m_layoutButtons, BOTTOM_HEIGHT_RATIO);

	layout->setSpacing(0);
	layout->setMargin(0);
}
