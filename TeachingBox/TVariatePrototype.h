#ifndef _TEACHING_BOX_T_VARIATE_PROTOTYPE_H_
#define _TEACHING_BOX_T_VARIATE_PROTOTYPE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TVariatePrototype.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/09
//  Description:    从xml文件中解析变量定义，并根据变量原型生成新的变量供其它类使用。
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/09
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "qdom.h"

class TComplex;
class TVariate;
class TSymbol;
class EnumValue;

class TVariatePrototype
{
private:
	typedef std::map<QString, std::shared_ptr<TComplex>> PrototypeMap;

public:
	static std::shared_ptr<TVariate> CreateVariate(const TSymbol& symbol);

private:
	static std::shared_ptr<EnumValue> GetEnumValue(const QDomNode& node);

	static void InitPrototype();
	static void InitCategoryProperty(const QDomNode& categoryNode);
	static void InitVariateProperty(const QDomNode& variateNode);

private:
	static PrototypeMap m_prototypeMap;

private:
	class Initialization
	{
	public:
		Initialization();
	};

	static Initialization m_initialization;
};

#endif