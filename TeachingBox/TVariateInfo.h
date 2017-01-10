#ifndef _TEACHING_BOX_T_VARIATE_INFO_H_
#define _TEACHING_BOX_T_VARIATE_INFO_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TVariateCategory.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/10
//  Description:    记录变量的一些信息，包括变量分类、变量名缩写等。
		变量分类：将变量类型（如Integer、Double等）按功能、特点等归在不同类下；
		变量名缩写：用于默认变量的生成、变量名的显示等。
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/10
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <map>
#include <set>

class TVariateInfo
{
private:
	typedef std::map<QString, std::shared_ptr<std::set<QString>>> CategoryMapType;
	typedef std::map<QString, QString> AbbreviationMapType;

public:
	static void RegisterCategory(const QString& category, const QString& newType);
	static void RegisterAbbreviation(const QString& wholeName, const QString& abbreviation);
	
	static CategoryMapType& CategoryMap();

	static QString GetAbbreviation(const QString& wholeName);

private:
	static AbbreviationMapType& AbbreviationMap();

};

#endif