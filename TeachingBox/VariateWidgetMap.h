#ifndef _TEACHING_BOX_VARIATE_WIDGET_MAP_H_
#define _TEACHING_BOX_VARIATE_WIDGET_MAP_H_

#include <map>
#include "QString"
#include <memory>

class VariateValueTreeWidgetItem;

class VariateWidgetMap
{
private:
	typedef std::map<QString, std::shared_ptr<VariateValueTreeWidgetItem>> VariateWidgetMapType;

public:
	/*************************************************
	//  Method:        static std::shared_ptr<VariateValueTreeWidgetItem>& VaraiteWidgetMap()
	//  Description:   获取静态VariateValueTreeWidgetItem集合引用，调用该函数的同时，初始化静态VariateValueTreeWidgetItem集合
	//  Author:        刘巍
	//  Date:          2016/11/29
	//  Returns:       static std::shared_ptr<VariateValueTreeWidgetItem>&：静态VariateValueTreeWidgetItem集合引用
	//  Parameter:     void
	//  History:
	*************************************************/
	static VariateWidgetMapType& VaraiteWidgetMap();

	/*************************************************
	//  Method:        static std::shared_ptr<VariateValueTreeWidgetItem> GetVariateWidget(const QString& type)
	//  Description:   获取某类型的变量控件头
	//  Author:        刘巍 
	//  Date:          2016/12/12
	//  Returns:       std::shared_ptr<VariateValueTreeWidgetItem>：变量控件头
	//  Parameter:     const QString& type：变量类型
	//  History:       
	*************************************************/
	static std::shared_ptr<VariateValueTreeWidgetItem> GetVariateWidget(const QString& type);

};
#endif