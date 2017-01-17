#ifndef _TEACHING_BOX_SCREEN_WARNING_HEADER_H_
#define _TEACHING_BOX_SCREEN_WARNING_HEADER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenWarning.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/07/28
//  Description:	用于监听并显示当前警告信息，位于示教盒上部状态栏
//  Others:			只有在所有警告信息都被清除的情况下，才能继续控制机器人运行
//  History:
//    <author>      刘巍 
//    <time>        2016/07/28
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "InternationalWidget.h"

class WidgetWithBorderAndIcon;
class ConfirmButton;
class WarningInfo;

class ScreenWarningHeader:public InternationalWidget
{
	Q_OBJECT

public:
	ScreenWarningHeader(QWidget* parent=0);
	~ScreenWarningHeader();

private:
	virtual void UpdateText() override;

	void ChangeWarningInfo(const WarningInfo& warningInfo);
	void ChangeCurrentInfo();
	void ChangeDisplay(const QString& iconPath, const QString& text, const QColor& backgroundColor);
	void Init();


private:

	QLabel* m_lbWarningText;
	ConfirmButton* m_btnConfrim;
	WidgetWithBorderAndIcon* m_warningWidget;
};

#endif