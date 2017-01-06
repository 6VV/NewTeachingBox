#include "stdafx.h"
#include "KeyBoardButton.h"
#include "QIcon"



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
	this->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);/*¿Ø¼þ³äÂúÊ£Óà¿Õ¼ä*/

	this->setStyleSheet("QToolButton{border-image: url(:/new/image/Resources/Image/keyboard_normal.png);}"
		"QToolButton:hover{border-image: url(:/new/image/Resources/Image/keyboard_hover.png);}"
		"QToolButton:pressed{border-image: url(:/new/image/Resources/Image/keyboard_press.png);}");
}
