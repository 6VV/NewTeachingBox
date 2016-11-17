#ifndef _TEACHING_BOX_VARIATE_WIDGET_WIDGET_MANAGER_NEW_VARIATE_H_
#define _TEACHING_BOX_VARIATE_WIDGET_WIDGET_MANAGER_NEW_VARIATE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    WidgetManagerNewVariate.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/15
//  Description:	用于生成新建变量的相关控件，并从控件中获取变量值；
	本类作为相关新建变量类的父类，提供以下基本的接口：
	virtual std::unique_ptr<TVariate> GetVariate(const QString& name, const QString& scope)=0;
	virtual void InitParameter() = 0;
	virtual void OnScopeChanged(const QString& scope);
	其中OnScopeChanged函数可由子类选择性实现，其余接口子类必须实现
	不可从本类中生成对象；
	本类及子类均位于命名控件VariateWidget中，用于避免与其它Vairate控件冲突。
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/15
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <memory>
#include "QObject"

class TVariate;
class QString;
class QTableWidget;

namespace VariateWidget
{
	class WidgetManagerNewVariate:public QObject
	{
		Q_OBJECT

	public:
		WidgetManagerNewVariate(QTableWidget* tableWidget, int startRowCount);
		virtual ~WidgetManagerNewVariate();

		virtual std::unique_ptr<TVariate> GetVariate(const QString& name, const QString& scope)=0;

		virtual void InitParameter() = 0;

		virtual void OnScopeChanged(const QString& scope);

	protected:
		QTableWidget* m_tableWidget;
		int m_startRowCount;
	};
}


#endif