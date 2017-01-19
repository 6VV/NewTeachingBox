#ifndef _TEACHING_BOX_TOOL_SYS_DIALOG_H_
#define _TEACHING_BOX_TOOL_SYS_DIALOG_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ToolSysDialog.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/19
//  Description:    工具坐标系示教对话框
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/19
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "DialogParent.h"

class TToolSys;
class ICoordinate;
class QStackedWidget;
class SystemDialogWidgetParent;

class ToolSysDialog :public DialogParent
{
public:
	ToolSysDialog(TToolSys* oldVariate, ICoordinate* iCoor, QWidget* parent = nullptr);
	~ToolSysDialog()=default;
	
private:
	QWidget* CreateToolWidget();

	void Init();

	virtual void UpdateText() override;

private:
	TToolSys* m_oldVariate;
	ICoordinate* m_iCoor;
	QStackedWidget* m_stackedWidget;

	SystemDialogWidgetParent* m_widgetOrigin;
	SystemDialogWidgetParent* m_fourPointsStep1;
	SystemDialogWidgetParent* m_fourPointsStep2;
	SystemDialogWidgetParent* m_fourPointsStep3;
	SystemDialogWidgetParent* m_fourPointsStep4;
	SystemDialogWidgetParent* m_onePoint6D;
	SystemDialogWidgetParent* m_widgetEnd;

};

#endif