#include "stdafx.h"
#include "ScreenCoordinate.h"
#include "ScreenReferenceSystem.h"
#include "Button.h"

ScreenCoordiante::ScreenCoordiante(QWidget* parent/*=nullptr*/)
	:ScreenMainParent(parent)
	, m_btnReferenceSystem(new Button(this))
{
}

QList<QPushButton*> ScreenCoordiante::GetButtonList()
{
	QList<QPushButton*> buttonList;
	buttonList.push_back(m_btnReferenceSystem);

	return buttonList;
}

QLayout* ScreenCoordiante::GetMainLayout()
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	ScreenReferenceSystem* system = new ScreenReferenceSystem(this);

	layout->addWidget(system);

	return layout;
}

void ScreenCoordiante::UpdateText()
{
	m_btnReferenceSystem->setText(tr("Ref System"));
}




