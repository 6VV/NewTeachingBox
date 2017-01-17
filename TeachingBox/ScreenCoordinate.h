#ifndef _TEACHING_BOX_SCREEN_COORDINATE_H_
#define _TEACHING_BOX_SCREEN_COORDINATE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenCoordinate.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/11
//  Description:	用于进行坐标系相关操作
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/11
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "ScreenMainParent.h"

class ScreenCoordiante:public ScreenMainParent
{
	Q_OBJECT

private:
	enum ScreenType
	{
		REFERENCE_SYSTEM,
		TOOL_SYSTEM,
	};

public:
	ScreenCoordiante(QWidget* parent=nullptr);

private:
	virtual QList<QWidget*> GetButtonList() override;
	virtual QLayout* GetMainLayout() override;
	virtual void UpdateText() override;

	void ChangeType(ScreenType screenType);

private:
	QLayout* m_mainLayout;
	QWidget* m_currentWidget;

	Button* m_btnReferenceSystem;
	Button* m_btnToolSystem;
};

#endif