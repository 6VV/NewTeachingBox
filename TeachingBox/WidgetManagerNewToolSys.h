#ifndef _TEACHING_BOX_VARIATE_WIDGET_WIDGET_MANAGER_NEW_TOOL_SYS_H_
#define _TEACHING_BOX_VARIATE_WIDGET_WIDGET_MANAGER_NEW_TOOL_SYS_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    WidgetManagerNewToolSys.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/16
//  Description:	用于生成新建RefSys变量控件的管理器
	继承自WidgetManagerNewVariate类
	位于VariateWidget命名空间中
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/16
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "WidgetManagerNewVariate.h"

namespace VariateWidget
{
	class WidgetManagerNewToolSys:public WidgetManagerNewVariate
	{
	public:
		WidgetManagerNewToolSys(QTableWidget* tableWidget, int startRowCount);
		~WidgetManagerNewToolSys();

		virtual std::unique_ptr<TVariate> GetVariate(const QString& name, const QString& scope) override;

		virtual void InitParameter() override;

	protected:

	private:
	};

}
#endif