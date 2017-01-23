#include "stdafx.h"
#include "Screen.h"
#include "QBoxLayout"
#include "ScreenState.h"
#include "ScreenAxis.h"
#include "ScreenWarningHeader.h"
#include "TeachingBoxContext.h"
#include "ScreenManager.h"



Screen::Screen(QWidget* parent/*=0*/)
	:QWidget(parent)
{
	Init();
}

Screen::~Screen()
{

}

void Screen::showEvent(QShowEvent *e)
{
	QWidget::showEvent(e);

	TeachingBoxContext::GetInstance()->SetScreenRect(geometry());
}

void Screen::Init()
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->setSpacing(0);

	layout->addWidget(new ScreenState(this),HEAD_HEIGHT_RATIO);
	layout->addLayout(GetBottomLayout(), MAIN_SCREEN_HEIGHT_RATIO+WARNING_HEIGHT_RATIO);
}

QLayout* Screen::GetBottomLayout()
{
	QHBoxLayout* layout = new QHBoxLayout(this);
	layout->setMargin(0);

	layout->addLayout(GetLeftLayout(),LEFT_WIDTH_RATIO);
	layout->addWidget(new ScreenAxis(this), RIGHT_WIDTH_RATIO);

	return layout;
}

QLayout* Screen::GetLeftLayout()
{
	QVBoxLayout* layout = new QVBoxLayout(this);
	layout->setMargin(0);
	layout->addWidget(new ScreenWarningHeader(this),WARNING_HEIGHT_RATIO);
	QWidget* widget = ScreenManager::GetInstance()->GetWidget(this);
	ScreenManager::GetInstance()->ChangeScreen(ScreenManager::SERVICE);
	layout->addWidget(widget, MAIN_SCREEN_HEIGHT_RATIO);

	return layout;
}

