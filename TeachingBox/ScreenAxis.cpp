#include "stdafx.h"
#include "ScreenAxis.h"
#include "LabelWithBorder.h"
#include "QBoxLayout"



ScreenAxis::ScreenAxis(QWidget* parent/*=0*/)
	:QWidget(parent)
	, m_axis1(new LabelWithBorder("Axis1",this))
	, m_axis2(new LabelWithBorder("Axis2", this))
	, m_axis3(new LabelWithBorder("Axis3", this))
	, m_axis4(new LabelWithBorder("Axis4", this))
	, m_axis5(new LabelWithBorder("Axis5", this))
	, m_axis6(new LabelWithBorder("Axis6", this))
{
	Init();
}

void ScreenAxis::Init()
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setSpacing(0);
	layout->setMargin(0);

	layout->addWidget(m_axis1);
	layout->addWidget(m_axis2);
	layout->addWidget(m_axis3);
	layout->addWidget(m_axis4);
	layout->addWidget(m_axis5);
	layout->addWidget(m_axis6);
	layout->addWidget(new LabelWithBorder(this));
}
