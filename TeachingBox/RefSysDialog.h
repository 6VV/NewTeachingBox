#ifndef _TEACHING_BOX_REF_SYS_DIALOG_H_
#define _TEACHING_BOX_REF_SYS_DIALOG_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    RefSysDialog.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/18
//  Description:    参考坐标系示教对话框
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/18
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "DialogParent.h"

class TRefSys;
class ICoordinate;
class SystemDialogWidgetParent;
class Button;

class RefSysDialog :public DialogParent
{
	Q_OBJECT

public:
	RefSysDialog(TRefSys* oldVariate, ICoordinate* iCoor,QWidget* parent = nullptr);
	~RefSysDialog()=default;

private:
	virtual void UpdateText() override;

	QWidget* ReferenceSystemWidget();

	void Init();

private:
	TRefSys* m_oldVariate;
	ICoordinate* m_iCoordinate;
	QStackedWidget* m_stackedWidget;

	SystemDialogWidgetParent* m_originWidget;
	SystemDialogWidgetParent* m_threePointsWithOrigin1;
	SystemDialogWidgetParent* m_threePointsWithOrigin2;
	SystemDialogWidgetParent* m_threePointsWithOrigin3;
	SystemDialogWidgetParent* m_threePointsWithoutOrigin1;
	SystemDialogWidgetParent* m_threePointsWithoutOrigin2;
	SystemDialogWidgetParent* m_threePointsWithoutOrigin3;
	SystemDialogWidgetParent* m_onePointKeepOrientation;
	SystemDialogWidgetParent* m_endWidget;

};


#endif