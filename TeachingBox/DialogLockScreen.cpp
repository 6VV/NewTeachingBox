#include "stdafx.h"
#include "DialogLockScreen.h"
#include "TeachingBoxContext.h"
#include "QBoxLayout"
#include "QLCDNumber"
#include "QPalette"



DialogLockScreen::DialogLockScreen(QWidget* parent/*=nullptr*/, int lockTime/*=16*/)
	:DialogParent(parent)
	, m_lockTime(lockTime)
{
	this->setWindowFlags(Qt::Dialog | Qt::FramelessWindowHint);
	this->setWindowModality(Qt::ApplicationModal);
	this->setWindowOpacity(0.5);

	setPalette(QPalette(Qt::lightGray));

	QHBoxLayout* layout = new QHBoxLayout(this);

	auto lcd = new QLCDNumber(3, this);
	lcd->display(lockTime);
	layout->addWidget(lcd);

	m_thread = new QThread(this);
	auto timer = new QTimer(this);
	connect(timer, &QTimer::timeout, this, [this,lcd]{
		lcd->display(--m_lockTime);
		if (m_lockTime<=0)
		{
			delete this;
		}
	}, Qt::DirectConnection);
	connect(this, &DialogLockScreen::SignalStopTimer, timer, &QTimer::stop);

	timer->start(1000);
	timer->moveToThread(m_thread);

	m_thread->start();
}

DialogLockScreen::~DialogLockScreen()
{
	emit(SignalStopTimer());

	m_thread->quit();
	m_thread->wait();
}

void DialogLockScreen::SetSize()
{
	QRect screenRect = TeachingBoxContext::GetInstance()->GetScreenRect();

	/*设置固定大小*/
	this->setFixedSize(screenRect.width() * 1/5, screenRect.height() * 1/5);

}

void DialogLockScreen::UpdateText()
{

}
