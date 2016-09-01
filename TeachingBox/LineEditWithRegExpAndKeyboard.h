#ifndef _TEACHING_BOX_LINEEDIT_WITH_REGEXP_AND_KEYBOARD_H_
#define _TEACHING_BOX_LINEEDIT_WITH_REGEXP_AND_KEYBOARD_H_

#include "KeyboardInterface.h"
#include "RegExp.h"
#include "QLineEdit"

class LineEditWithRegExpAndKeyboard:public QLineEdit,public KeyboardInterface
{
	Q_OBJECT

public:
		/*显示模式*/
	enum KEYBOARD_SHOW_MODE
	{
		KEYBOARD_SHOW_TEXT,	/*显示文本*/
		KEYBOARD_NOT_SHOW_TEXT,	/*不显示文本*/
	};

public:
	LineEditWithRegExpAndKeyboard(const QString& text = "", const QString& regExp = RegExp::STR_REG_ANY_CHAR, QWidget* const widget = 0);
	~LineEditWithRegExpAndKeyboard();

	virtual void KeyboardEdit() override;

	void SetRegExp(const QString& regExp);
	void SetKeyboardShowMode(const KEYBOARD_SHOW_MODE mode);

protected:
	void mousePressEvent(QMouseEvent *) override;

protected:
	QString m_regExp=RegExp::STR_REG_ANY_CHAR;
	KEYBOARD_SHOW_MODE m_keyboardShowMode=KEYBOARD_SHOW_TEXT;
	
};

#endif
