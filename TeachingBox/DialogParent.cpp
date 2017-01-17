#include "stdafx.h"
#include "DialogParent.h"
#include "TeachingBoxContext.h"



DialogParent::DialogParent(QWidget* parent)
	:InternationalWidget(parent)
{
	this->setWindowFlags(Qt::Dialog | Qt::WindowTitleHint);
	this->setWindowModality(Qt::ApplicationModal);
}

DialogParent::~DialogParent()
{

}

void DialogParent::showEvent(QShowEvent *)
{
	SetSize();
	SetPosition();
}

void DialogParent::SetSize()
{
	QRect screenRect = TeachingBoxContext::GetInstance()->GetScreenRect();

	/*设置固定大小*/
	this->setFixedSize(screenRect.width() * 2 / 3, screenRect.height() * 2 / 3);
}

void DialogParent::SetPosition()
{
	QRect screenRect = TeachingBoxContext::GetInstance()->GetScreenRect();

	/*移动到屏幕中央*/
	this->move(screenRect.left() + screenRect.width() / 2 - this->width() / 2,
		screenRect.top() + screenRect.height() / 2 - this->height() / 2);
}
