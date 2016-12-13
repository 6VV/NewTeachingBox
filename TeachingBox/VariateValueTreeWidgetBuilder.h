#ifndef _TEACHING_BOX_VARIATE_VALUE_TREE_WIDGET_BUILDER_H_
#define _TEACHING_BOX_VARIATE_VALUE_TREE_WIDGET_BUILDER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    VariateValueTreeWidgetBuilder.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/29
//  Description:    变量树形控件构建器，用于程序启动时将变量树形控件添加到控件管理器中，
		所有VariateValueTreeWidgetItem的子类均需声明一个VariateValueTreeWidgetBuilder的静态成员变量。
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/11/29
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <memory>
#include "VariateWidgetMap.h"

template<typename T>
class VariateValueTreeWidgetBuilder
{
public:
	VariateValueTreeWidgetBuilder(const QString& type);
};

template<typename T>
VariateValueTreeWidgetBuilder<T>::VariateValueTreeWidgetBuilder(const QString& type)
{
	VariateWidgetMap::VaraiteWidgetMap()[type] = std::shared_ptr<T>(new T);
}

#endif