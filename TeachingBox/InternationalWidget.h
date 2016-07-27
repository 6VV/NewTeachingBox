#ifndef _INTERNATIONAL_WIDGET_H_
#define _INTERNATIONAL_WIDGET_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    InternationalWidget.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/07/27
//  Description:	该类继承自QWidget，重定义changeEvent函数，用于国际化支持，
					当某些Widget需要更改显示语言时，应继承自此类，并重写UpdateText函数。
//  Others:
//  History:
//    <author>      刘巍 
//    <time>        2016/07/27
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QWidget"

class QEvent;

class InternationalWidget:public QWidget
{
	Q_OBJECT
public:
	InternationalWidget(QWidget* parent=0);
	virtual ~InternationalWidget();
protected:
	void changeEvent(QEvent *e) override;

private:
	virtual void UpdateText()=0;
	
};

#endif