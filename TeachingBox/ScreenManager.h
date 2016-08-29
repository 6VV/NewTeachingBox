#ifndef _TEACHING_BOX_SCREEN_MANAGER_H_
#define _TEACHING_BOX_SCREEN_MANAGER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ScreenManager.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/08/29
//  Description:	界面管理器，用于切换、显示、控制界面的生命周期
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/08/29
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "SingleTon.h"
#include <memory>

class QStackedWidget;

class ScreenManager
{
	friend SingleTon<ScreenManager>;

public:
	enum ScreenType
	{
		SERVICE,
		VARIATE,
	};

public:
	static ScreenManager* GetInstance();

public:
	void ChangeScreen(ScreenType screenType);

	QWidget* GetWidget(QWidget* parent);

private:
	ScreenManager();
	ScreenManager(const ScreenManager&);
	ScreenManager& operator=(const ScreenManager&);
	~ScreenManager();

	QWidget* CreateWithoutCheck(const ScreenType type, QWidget* parent);
	QWidget* Find(const ScreenType type);
	QWidget* GetScreen(const ScreenType type, QWidget* parent);

private:
	QStackedWidget* m_mainWidget=nullptr;
	QHash<ScreenType, QWidget*> m_screens;
};

#endif