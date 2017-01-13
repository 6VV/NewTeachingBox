#ifndef _TEACHING_BOX_MACRO_INFO_H_
#define _TEACHING_BOX_MACRO_INFO_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    MacroInfo.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/12/28
//  Description:    记录命令相关信息
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/12/28
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QStringList"

class MacroInfo
{
public:
	MacroInfo(const QString& name, int id,const QStringList& parameterTypes,const QString& category,const QString& type,const QString& text);
	
	int GetId() const;
	QString GetText() const;
	QString GetName() const;
	QStringList GetParameterTypes() const;

private:
	QString m_category{};	/*分类*/
	QString m_type{};	/*类型*/
	QString m_name{};	/*名字*/
	int m_id{};	/*id*/
	QStringList m_parameterTypes{};	/*参数类型*/
	QString m_text;	/*生成文本*/
};

#endif