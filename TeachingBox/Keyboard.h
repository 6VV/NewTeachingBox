#ifndef _TEACHING_BOX_KEYBOARD_H_
#define _TEACHING_BOX_KEYBOARD_H_

#include "SingleTon.h"
#include "QWidget"

class QLineEdit;

class KeyboardInterface;
class KeyboardButton;

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

	QLineEdit* GetLineEdit();	
	QString GetCurrentText();	/*获取当前文本*/
	void SetConfirmCommand(int);	/*设置确认按钮对应命令*/
	void SetCurrentWidget(QWidget*);	/*设置调用本键盘的窗口*/
	void SetCurrentText(const QString&);	/*设置键盘当前文本*/
	void SetKeyboardInterface(KeyboardInterface*);	/*设置Confirm按钮按下时调用的函数*/


	/*回调函数所在类*/
private:
	KeyboardInterface* m_keyboardInterface;

	/*自定义私有函数*/
private:
	void Init();
	void InitLayout();
	void InitSignalSlot();

	void OnButtonConfirmClicked();

	void ChangeToLower();	/*切换为小写*/
	void ChangeToUpper();	/*切换为大写*/

	void Clear();	/*清空参数*/

	/*重定义父类函数*/
protected:
	void showEvent(QShowEvent *event) Q_DECL_OVERRIDE;
	void hideEvent(QHideEvent *event) Q_DECL_OVERRIDE;

protected slots:
	void SlotOnButtonClicked();

	/*定义确认按钮按下后所执行的操作指令*/
public:
	const static int CONFIRM_SCREEN_SETTING_LOGIN;			/*登录*/
	const static int CONFIRM_SCREEN_PROGRAM_EDIT_PROGRAM;	/*编辑程序*/
	const static int CONFIRM_SCREEN_PROJECT_NEW_PROJECT;	/*新建项目*/
	const static int CONFIRM_SCREEN_PROJECT_NEW_PROGRAM;	/*新建程序*/
	const static int CONFIRM_MACRO_POSITION_EIDT;			/*编辑位置变量参数*/
	const static int CONFIRM_MACRO_VELOCITY_EDIT;			/*编辑速度变量参数*/
	const static int CONFIRM_MACRO_ZONE_EDIT;				/*编辑过渡变量参数*/
	const static int CONFIRM_MACRO_DOUBLE_EDIT;				/*编辑浮点数变量参数*/
	const static int CONFIRM_MACRO_LABEL_EDIT;				/*编辑标签变量*/
	const static int CONFIRM_NEW_PARAMETER;					/*添加新变量*/
	const static int CONFIRM_MACRO_INT_EDIT;				/*编辑整数变量*/
	const static int CONFIRM_MACRO_BOOL_EDIT;				/*编辑布尔变量*/
	const static int CONFIRM_MACRO_STRING_EDIT;				/*编辑字符串变量*/
	const static int CONFIRM_MACRO_NUMBER_EDIT;				/*编辑数值参数*/

	/*控件*/
private:
	const char* CLASS_NAME = "CKeyBoard";
	int m_confirmCommand = -1;	/*当前确认按钮对应的命令*/
	QWidget* m_currentWidget=NULL;	/*调用本键盘的窗口*/
	QLineEdit* m_lineEditText;	/*显示文本控件*/
	bool m_isLower = true;	/*是否为小写字符*/

	KeyboardButton* m_btnTilde;
	KeyboardButton* m_btnNum1;
	KeyboardButton* m_btnNum2;
	KeyboardButton* m_btnNum3;
	KeyboardButton* m_btnNum4;
	KeyboardButton* m_btnNum5;
	KeyboardButton* m_btnNum6;
	KeyboardButton* m_btnNum7;
	KeyboardButton* m_btnNum8;
	KeyboardButton* m_btnNum9;
	KeyboardButton* m_btnNum0;
	KeyboardButton* m_btnMinus;
	KeyboardButton* m_btnPlus;
	KeyboardButton* m_btnBackspace;

	KeyboardButton* m_btnTab;
	KeyboardButton* m_btnQ;
	KeyboardButton* m_btnW;
	KeyboardButton* m_btnE;
	KeyboardButton* m_btnR;
	KeyboardButton* m_btnT;
	KeyboardButton* m_btnY;
	KeyboardButton* m_btnU;
	KeyboardButton* m_btnI;
	KeyboardButton* m_btnO;
	KeyboardButton* m_btnP;
	KeyboardButton* m_btnLeftBracket;
	KeyboardButton* m_btnRightBracket;
	KeyboardButton* m_btnBackSlash;
	KeyboardButton* m_btnEqual;

	KeyboardButton* m_btnCapsLock;
	KeyboardButton* m_btnA;
	KeyboardButton* m_btnS;
	KeyboardButton* m_btnD;
	KeyboardButton* m_btnF;
	KeyboardButton* m_btnG;
	KeyboardButton* m_btnH;
	KeyboardButton* m_btnJ;
	KeyboardButton* m_btnK;
	KeyboardButton* m_btnL;
	KeyboardButton* m_btnSemicolon;
	KeyboardButton* m_btnQuotation;
	KeyboardButton* m_btnEnter;

	KeyboardButton* m_btnShift;
	KeyboardButton* m_btnZ;
	KeyboardButton* m_btnX;
	KeyboardButton* m_btnC;
	KeyboardButton* m_btnV;
	KeyboardButton* m_btnB;
	KeyboardButton* m_btnN;
	KeyboardButton* m_btnM;
	KeyboardButton* m_btnComma;
	KeyboardButton* m_btnPeriod;
	KeyboardButton* m_btnSlash;
	KeyboardButton* m_btnUp;

	KeyboardButton* m_btnCtrl;
	KeyboardButton* m_btnAlt;
	KeyboardButton* m_btnSpace;
	KeyboardButton* m_btnLf;
	KeyboardButton* m_btnRg;
	KeyboardButton* m_btnBt;

	KeyboardButton* m_btnCancle;
	KeyboardButton* m_btnConfirm;
};

#endif
