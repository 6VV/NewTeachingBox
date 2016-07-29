#ifndef _TEACHING_BOX_SCREEN_FACTORY_H_
#define _TEACHING_BOX_SCREEN_FACTORY_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenManager.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/07/28
//  Description:	用于生产并销毁Screen相关类的唯一实例。
//  Others:			
//  History:
//    <author>      刘巍 
//    <time>        2016/07/28
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QHash"
#include "ScreenType.h"

class QWidget;

class ScreenFactory
{
public:
	~ScreenFactory();

	QWidget* Create(const ScreenType::ScreenType type, QWidget* parent);
	void Destroy(const ScreenType::ScreenType type);

private:
	void Clear();
	QWidget* CreateWithoutCheck(const ScreenType::ScreenType type, QWidget* parent);
	QWidget* Find(const ScreenType::ScreenType type);

private:
	QHash<ScreenType::ScreenType, QWidget*> m_screens;
};

#endif