#include "stdafx.h"
#include "LineEditWithRegExpAndKeyboard.h"
#include "Keyboard.h"
#include "WarningManager.h"


LineEditWithRegExpAndKeyboard::LineEditWithRegExpAndKeyboard(const QString& text /*= ""*/, 
	const QString& regExp /*= CRegExpManager::STR_REG_ANY_CHAR*/, QWidget* const widget /*= 0*/)
	: QLineEdit(text, widget)
	, m_regExp(regExp)
{

}

LineEditWithRegExpAndKeyboard::~LineEditWithRegExpAndKeyboard()
{

}

void LineEditWithRegExpAndKeyboard::KeyboardEdit(const QString& text)
{
	QRegExp regExp(m_regExp);
	if (regExp.exactMatch(text))
	{
		this->setText(text);
	}
	else
	{
		WarningManager::GetInstance()->Warning(this, QString("not match"));
	}
}

void LineEditWithRegExpAndKeyboard::SetRegExp(const QString& regExp)
{
	m_regExp = regExp;
}

void LineEditWithRegExpAndKeyboard::SetKeyboardShowMode(const KEYBOARD_SHOW_MODE mode)
{
	m_keyboardShowMode = mode;
}

void LineEditWithRegExpAndKeyboard::mousePressEvent(QMouseEvent *)
{
	this->selectAll();
	Keyboard* keyboard = Keyboard::GetInstance();

	switch (m_keyboardShowMode)
	{
	case LineEditWithRegExpAndKeyboard::KEYBOARD_SHOW_TEXT:
	{
		keyboard->SetCurrentText(this->text());
	}break;
	default:
		break;
	}

	keyboard->SetKeyboardInterface(this);
	keyboard->show();
}
