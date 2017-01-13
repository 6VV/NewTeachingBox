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
#include <map>

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

private:
	struct KeyInfo
	{
		KeyInfo(Qt::Key keyType,const QString& lowerText, const QString& upperText)
			:keyType(keyType)
			, lowerText(lowerText)
			, upperText(upperText)
		{}
		KeyInfo() = default;
		Qt::Key keyType{};
		QString lowerText{};
		QString upperText{};
	};

private:
	IKeyboard* m_iKeyboard;
	std::map<KeyboardButton*, KeyInfo> m_keyMap{};
	QObject* m_targetObject;
	
	bool m_isCapPressed = false;
	bool m_isShiftPressed = false;
};

#endif