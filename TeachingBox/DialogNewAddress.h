#ifndef _TEACHING_BOX_DIALOG_NEW_ADDRESS_H_
#define _TEACHING_BOX_DIALOG_NEW_ADDRESS_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    DialogNewAddress.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/10/08
//  Description:	对话框，用于输入远程控制器IP地址
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/10/08
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "DialogParent.h"

class IScreenNetwork;
class Button;

class DialogNewAddress:public DialogParent
{
	Q_OBJECT

public:
	DialogNewAddress(QWidget* parent,IScreenNetwork* iScreenNetwork);
	~DialogNewAddress();
	
private:
	virtual void UpdateText() override;
	virtual void SetSize() override;

	void Destory();

	void Init();
	void InitLayout();
	void InitSignalSlot();

	bool IsValidAddress(const QString& address);

private slots:
	void SlotOnConfirmClicked();

	void SlotOnCancleClicked();
private:
	IScreenNetwork* m_iScreenNetwork=nullptr;

	QLineEdit* m_lineEdit;
	Button* m_btnConfirm;
	Button* m_btnCancle;
};

#endif