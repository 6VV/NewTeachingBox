#ifndef _TEACHING_BOX_VARIATE_WIDGET_WIDGET_MANAGER_NEW_VARIATE_FACTORY_H_
#define _TEACHING_BOX_VARIATE_WIDGET_WIDGET_MANAGER_NEW_VARIATE_FACTORY_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    NewVariateWidgetFactory.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/15
//  Description:	工厂方法模式，用于生成新建变量控件相关类
	通过给出变量类型，生成并返回相关类对象
	生成的对象需由调用者销毁
	位于命名控件VariateWidget中
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/15
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

class QString;
class QTableWidget;

namespace VariateWidget
{
	class WidgetManagerNewVariate;

	class WidgetManagerNewVariateFactory
	{
	public:
		static WidgetManagerNewVariate* CreateWidgetManagerNewVariate(const QString& type, QTableWidget* tableWidget, int startRowCount);
	};
}


#endif