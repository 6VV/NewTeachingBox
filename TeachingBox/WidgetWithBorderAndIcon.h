#ifndef _TEACHING_BOX_WIDGET_WITH_BORDER_AND_ICON_H_
#define _TEACHING_BOX_WIDGET_WITH_BORDER_AND_ICON_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    WidgetWithBorderAndIcon.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/16
//  Description:    带有边框和图标的控件
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/16
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "LabelWithBorder.h"

class WidgetWithBorderAndIcon :public LabelWithBorder
{
public:
	WidgetWithBorderAndIcon(QWidget* widget, const QString& iconPath, QWidget* parent = 0);

	virtual void showEvent(QShowEvent *) override;

	void AddStyleSheet(const QString& styleSheet);
	void SetIcon(const QString& iconPath,int height=0);

private:
	QString m_iconPath;
	QLabel* m_icon;
	QWidget* m_widget;
};

#endif