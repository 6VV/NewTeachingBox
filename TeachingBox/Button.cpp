#include "stdafx.h"
#include "Button.h"



Button::Button(QWidget* parent /*= 0*/)
	:QPushButton(parent)
{
	Init();
}

Button::Button(const QString& text, QWidget* parent /*= 0*/)
	: QPushButton(text,parent)
{
	Init();
}

void Button::Init()
{
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
}
