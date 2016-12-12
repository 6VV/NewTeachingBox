﻿#ifndef _TEACHING_BOX_VARIATE_WIDGET_WIDGET_MANAGER_NEW_POSITION_H_
#define _TEACHING_BOX_VARIATE_WIDGET_WIDGET_MANAGER_NEW_POSITION_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    WidgetManagerNewPosition.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/15
//  Description: 用于生成新建Position变量控件，并从该控件中获取变量值
	本类位于VariateWidget命名控件中，避免与其它Variate相关类命名冲突
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/15
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "WidgetManagerNewVariate.h"

namespace VariateWidget
{
	class WidgetManagerNewPosition:public WidgetManagerNewVariate
	{
	public:
		WidgetManagerNewPosition(QTableWidget* tableWidget, int startRowCount);
		~WidgetManagerNewPosition();

		virtual std::shared_ptr<TVariate> GetVariate(const QString& name, const QString& scope) override;

		virtual void InitParameter() override;

	};
}

#endif