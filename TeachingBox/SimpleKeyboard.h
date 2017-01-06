#ifndef _TEACHING_BOX_SIMPLE_KEYBOARD_H_
#define _TEACHING_BOX_SIMPLE_KEYBOARD_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    SimpleKeyboard.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/05
//  Description:    基础键盘，提供基本的键盘界面及按钮操作事件，
		调用时需向其传入一继承键盘接口的子类，键盘按钮按下时，会调用该接口的接口函数
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/05
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QWidget"
#include "qcoreevent.h"

class IKeyboard;
class KeyboardButton;

class SimpleKeyboard:public QWidget
{
	Q_OBJECT
public:
	SimpleKeyboard(IKeyboard* iKeyboard,QWidget* parent=nullptr);
	~SimpleKeyboard()=default;

private:
	void ChangeToLower();	/*切换为小写*/
	void ChangeToUpper();	/*切换为大写*/
	void UpdateKeyboard(bool isLower); /*切换显示内容大小写*/

	void Init();
	void InitLayout();
	void InitSignalSlot();

	void OnButtonClicked();
private:
	struct KeyInfo
	{
		KeyInfo(Qt::Key lowerKeyType, Qt::Key upperKeyType, const QString& lowerText, const QString& upperText)
			:lowerKeyType(lowerKeyType)
			, upperKeyType(upperKeyType)
			, lowerText(lowerText)
			, upperText(upperText)
		{}
		KeyInfo() = default;
		Qt::Key lowerKeyType{};
		Qt::Key upperKeyType{};
		QString lowerText{};
		QString upperText{};
	};

private:
	IKeyboard* m_iKeyboard;
	std::map<KeyboardButton*, KeyInfo> m_keyMap{};
	QObject* m_targetObject;
	
	bool m_isCapPressed = false;
	bool m_isShiftPressed = false;

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
	KeyboardButton* m_btnSpace;
};

#endif