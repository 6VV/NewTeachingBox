#include "stdafx.h"
#include "KeyBoardButton.h"



KeyboardButton::KeyboardButton(QWidget* parent/*=0*/) :QToolButton(parent)
{
	Init();
}

KeyboardButton::KeyboardButton(const QString& text, QWidget* parent /*= 0*/) : QToolButton(parent)
{
	Init();
	this->setText(text);
}

KeyboardButton::~KeyboardButton()
{

}

//QSize CButtonKeyBoard::sizeHint() const
//{
//	QSize size = QToolButton::sizeHint();
//	int maxSize = qMax(size.width(), size.height());
//	size.rheight() = maxSize;
//	size.rwidth() = maxSize;
//	return size;
//}

void KeyboardButton::Init()
{
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);/*¿Ø¼ş³äÂúÊ£Óà¿Õ¼ä*/
}
