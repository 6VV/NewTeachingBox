#include "stdafx.h"
#include "ScreenCoordinate.h"
#include "ScreenReferenceSystem.h"
#include "Button.h"
#include <assert.h>
#include "ScreenToolSystem.h"

ScreenCoordiante::ScreenCoordiante(QWidget* parent/*=nullptr*/)
	:ScreenMainParent(parent)
	, m_btnReferenceSystem(new Button(this))
	, m_btnToolSystem(new Button(this))
{
	UpdateText();

}

QList<QPushButton*> ScreenCoordiante::GetButtonList()
{
	QList<QPushButton*> buttonList;
	buttonList.push_back(m_btnReferenceSystem);
	buttonList.push_back(m_btnToolSystem);

	connect(m_btnReferenceSystem, &QPushButton::clicked, [this]{this->ChangeType(REFERENCE_SYSTEM); });
	connect(m_btnToolSystem, &QPushButton::clicked, [this]{this->ChangeType(TOOL_SYSTEM); });

	return buttonList;
}

QLayout* ScreenCoordiante::GetMainLayout()
{
	m_mainLayout = new QHBoxLayout(this);

	m_currentWidget = new ScreenReferenceSystem(this);
	m_mainLayout->addWidget(m_currentWidget);

	return m_mainLayout;
}

void ScreenCoordiante::UpdateText()
{
	m_btnReferenceSystem->setText(tr("Ref System"));
	m_btnToolSystem->setText(tr("Tool System"));
}

void ScreenCoordiante::ChangeType(ScreenType screenType)
{
	m_mainLayout->removeWidget(m_currentWidget);
	delete m_currentWidget; 

	switch (screenType)
	{
	case ScreenCoordiante::REFERENCE_SYSTEM:{m_currentWidget = new ScreenReferenceSystem(this); }
		break;
	case ScreenCoordiante::TOOL_SYSTEM:{m_currentWidget = new ScreenToolSystem(this); }
		break;
	default:
		break;
	}

	m_mainLayout->addWidget(m_currentWidget);
}



