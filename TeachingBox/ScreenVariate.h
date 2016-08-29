#ifndef _TEACHING_BOX_SCREEN_VARIATE_H_
#define _TEACHING_BOX_SCREEN_VARIATE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenVariate.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/08/29
//  Description:	变量编辑界面，包括添加、删除、修改、清除未用变量
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/08/29
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "ScreenMainParent.h"
#include "Button.h"

class QTreeWidget;
class ButtonGroup;

class ScreenVariate:public ScreenMainParent
{
	friend class ScreenManager;

	Q_OBJECT

private:
	ScreenVariate(QWidget* parent = 0);
	ScreenVariate(const ScreenVariate&);
	ScreenVariate& operator=(const ScreenVariate&);
	~ScreenVariate();

private slots:
	void SlotOnVariateButtonClicked();

private:
	virtual QList<QPushButton*> GetButtonList() override;
	virtual QLayout* GetMainLayout() override;

	void Init();
	void InitTreeWidget();
	void InitButtonWidget();
	void InitSignalSlot();

	virtual void UpdateText() override;

private:
	QTreeWidget* m_treeWidget;

	Button* m_btnVariate;
	Button* m_btnTeach;
	Button* m_btnClearUnused;
	Button* m_btnCheck;

	ButtonGroup* m_btnGroupVariate;
	Button* m_btnCopy;
	Button* m_btnCut;
	Button* m_btnPaste;
	Button* m_btnRename;
	Button* m_btnNew;
	Button* m_btnDelete;
};

#endif