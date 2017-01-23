#ifndef _TEACHING_BOX_KEYBOARD_H_
#define _TEACHING_BOX_KEYBOARD_H_

#include "SingleTon.h"
#include "QWidget"

class KeyboardLineEidt;
class KeyboardInterface;
class KeyboardButton;
class SimpleKeyboard;

class Keyboard:public QWidget
{
	friend class SingleTon<Keyboard>;	/*单例模式*/

	Q_OBJECT

private:
	Keyboard(QWidget* parent=0);
	Keyboard(const Keyboard&);
	Keyboard& operator=(const Keyboard&);
	~Keyboard();

	/*自定义公有函数*/
public:
	static Keyboard* GetInstance();

	void SetEchoMode(QLineEdit::EchoMode echoMode);
	void SetCurrentText(const QString&);	/*设置键盘当前文本*/
	void SetKeyboardInterface(KeyboardInterface*);	/*设置Confirm按钮按下时调用的函数*/

	
	/*自定义私有函数*/
private:
	void Init();
	void InitLayout();

	void Clear();	/*清空参数*/

	/*控件*/
private:
	const char* CLASS_NAME = "CKeyBoard";
	KeyboardInterface* m_keyboardInterface=nullptr;	/*回调函数所在类*/

	int m_confirmCommand = -1;	/*当前确认按钮对应的命令*/
	QWidget* m_currentWidget=nullptr;	/*调用本键盘的窗口*/
	KeyboardLineEidt* m_lineEditText=nullptr;	/*显示文本控件*/
	SimpleKeyboard* m_simpleKeyboard=nullptr;	/*基础键盘*/

	KeyboardButton* m_btnCancle;
	KeyboardButton* m_btnConfirm;
};

#endif
