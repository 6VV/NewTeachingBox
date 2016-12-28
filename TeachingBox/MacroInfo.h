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
	
	QString GetText() const;
	QString GetName() const;
	QStringList GetParameterTypes() const;
private:
	QString m_category{};
	QString m_type{};
	QString m_name{};
	int m_id{};
	QStringList m_parameterTypes{};
	QString m_text;
};

#endif