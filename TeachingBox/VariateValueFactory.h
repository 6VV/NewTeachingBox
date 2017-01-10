#ifndef _TEACHING_BOX_VARIATE_VALUE_FACTORY_H_
#define _TEACHING_BOX_VARIATE_VALUE_FACTORY_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    VariateValueFactory.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/10
//  Description:    用于根据变量值名获取变量值对象，该变量对象需首先进行注册
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/10
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include <memory>
#include "QString"
#include <map>

class VariateValue;

class VariateValueFactory
{
private:
	typedef std::shared_ptr<VariateValue>(*FunCreateValue)();
	typedef std::map<QString, FunCreateValue> FunMapType;

public:
	static void Register(const QString& valueType, FunCreateValue fun);
	
	static std::shared_ptr<VariateValue> CreateVariateValue(const QString& valueType);

private:
	static FunMapType& FunMap();

};

#endif