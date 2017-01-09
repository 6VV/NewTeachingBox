#ifndef _TEACHING_BOX_PROJECT_VARIATES_XML_MANAGER_H_
#define _TEACHING_BOX_PROJECT_VARIATES_XML_MANAGER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    ProjectVariatesXmlManager.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/09
//  Description:    
//  Others:         将项目变量导出到xml文件，或从xml文件中导入项目变量
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/09
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "QString"
#include "qdom.h"

class TVariate;

class ProjectVariatesXmlManager
{
public:
	void WriteToXml(const QString& projectName) const;	/*将项目变量导出到xml文件*/

private:
	void WriteOriVariates(QXmlStreamWriter& writer,QVector<QByteArray>& variatesArray) const;	/*导出初始作用域（SYSTEM、SYNERGIC、GLOBAL）变量*/
	void WriteProjectVariates(QXmlStreamWriter& writer, QVector<QByteArray>& variatesArray, const QString& projectName) const;	/*导出项目变量*/
	void WriteScopeVariates(QXmlStreamWriter& writer, const QString& scope, QVector<QByteArray>& variatesArray) const;	/*写入特定作用域变量*/
	void WriteVariate(QXmlStreamWriter& writer, std::shared_ptr<TVariate> variate) const;	/*写入变量*/
	

};

#endif