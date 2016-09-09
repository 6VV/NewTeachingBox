#ifndef _TEACHING_BOX_DIALOG_NEW_MACRO_H_
#define _TEACHING_BOX_DIALOG_NEW_MACRO_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    DialogNewMacro.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/09/07
//  Description:	命令选择界面。
//					显示命令分类，用户点击分类后，显示该分类下的所有命令；
//					用户选择命令后，再编辑器界面自动生成命令
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/09/07
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "DialogParent.h"

class QTreeWidget;
class QTreeWidgetItem;
class QListWidget;
class Button;
class QLayout;

class DialogNewMacro:public DialogParent
{
	Q_OBJECT

public:
	DialogNewMacro(QWidget* parent);
	~DialogNewMacro();

private slots:
	void SlotOnButtonConfirmClicked();
	void SlotOnButtonCancleClicked();

	void SlotOnTreeItemClicked(QTreeWidgetItem* item);

private:
	virtual void UpdateText() override;

	QWidget* GetCategoryWidget();

	void Init();
	void InitLayout();
	void InitSignalSlot();
	bool IsValidTypeItem(QTreeWidgetItem* item);

private:
	QTreeWidget* m_categoryTree;
	QListWidget* m_macroWidget;

	Button* m_btnConfirm;
	Button* m_btnCancle;
};

#endif
