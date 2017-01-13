#include "stdafx.h"
#include "ScreenWarning.h"
#include "LabelWithBorder.h"
#include "Button.h"
#include "QBoxLayout"



ScreenWarning::ScreenWarning(QWidget* parent/*=0*/)
	:InternationalWidget(parent)
	, m_labelWarning(new LabelWithBorder(this))
	, m_btnConfrim(new Button(this))
{
	Init();
}

ScreenWarning::~ScreenWarning()
{

}

void ScreenWarning::UpdateText()
{
	m_btnConfrim->setText(tr("Confirm"));
}

void ScreenWarning::Init()
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);
	layout->addWidget(m_labelWarning,8);
	layout->addWidget(m_btnConfrim, 1);
	m_btnConfrim->setIcon(QIcon(QPixmap(":/new/image/Resources/Image/confirm_icon.png")));

	UpdateText();
}
