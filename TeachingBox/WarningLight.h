#ifndef _WARNING_LIGHT_H_
#define _WARNING_LIGHT_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    WarningLight.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/07/27
//  Description:	指示灯，用于模拟灯报警
//  Others:			在示教盒中应替换为真实灯
//  History:
//    <author>      刘巍 
//    <time>        2016/07/27
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QWidget"
#include "QColor"

class WarningLight:public QWidget
{
	Q_OBJECT
private:
	static const QColor COLOR_ON;
	static const QColor COLOR_OFF;

public:
	WarningLight(QWidget* parent=0);

	void LightOn();
	void LightOff();

private:
	void paintEvent(QPaintEvent*) override;
	QColor m_color = COLOR_OFF;
};

#endif