#ifndef _TEACHING_BOX_USER_MANAGER_H_
#define _TEACHING_BOX_USER_MANAGER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenUserManager.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/08/29
//  Description:	用户管理界面，用于显示、编辑用户信息
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/08/29
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "InternationalWidget.h"
#include "IUserManager.h"

class QTableWidget;
class Button;

class ScreenUserManager:public InternationalWidget,public IUserManager
{
	Q_OBJECT

public:
	ScreenUserManager(QWidget* parent);
	~ScreenUserManager();

	virtual void OnUpdate() override;

protected slots:
	void showEvent(QShowEvent *) override;

private:
	QLayout* GetButtonLayout();
	QLayout* GetMainLayout();

	void Init();
	void InitLayout();
	void InitSignalSlot();

	virtual void UpdateText() override;

private slots:
	void SlotOnNewButtonClicked();
	void SlotOnEditButtonClicked();
	void SlotOnDeleteButtonClicked();

private:
	const char* CLASS_NAME = "ScreenUserManager";

	QTableWidget* m_tableWidget;
	Button* m_btnEdit;
	Button* m_btnNew;
	Button* m_btnDelete;
};

#endif