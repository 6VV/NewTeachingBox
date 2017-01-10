#ifndef _TEACHING_BOX_VARIATE_VALUE_REGISTER_H_
#define _TEACHING_BOX_VARIATE_VALUE_REGISTER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    VariateValueRegister.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/10
//  Description:    用于将变量值信息注册于变量值工厂，以便可通过变量值名来获取变量值对象,仅用于注册可通过默认值生成的变量值对象，
		EnumValue之类的变量值不可通过此类进行注册
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/10
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "VariateValueFactory.h"

class VariateValue;

template<typename Type>
class VariateValueRegister
{
public:
	VariateValueRegister(const QString& type);
	
private:
	static std::shared_ptr<VariateValue> CreateVariateValue();
};

template<typename Type>
std::shared_ptr<VariateValue> VariateValueRegister<Type>::CreateVariateValue()
{
	return std::make_shared<Type>();
}

template<typename Type>
VariateValueRegister<Type>::VariateValueRegister(const QString& type)
{
	VariateValueFactory::Register(type, CreateVariateValue);
}

#endif