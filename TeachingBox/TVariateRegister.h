#ifndef _TEACHING_BOX_T_VARIATE_REGISTER_H_
#define _TEACHING_BOX_T_VARIATE_REGISTER_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TVariateRegister.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/12/14
//  Description:    用于将变量注册到变量工厂，以便于能够直接根据变量类型名创建变量
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/12/14
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "TVariateFactory.h"

class TVariate;

template<typename Type>
class TVariateRegister
{
public:
	TVariateRegister(const QString& name);

	static std::shared_ptr<TVariate> GetVariate(QDataStream& data);

	static std::shared_ptr<TVariate> CreateVariate(const TSymbol& symbol);
};

template<typename Type>
std::shared_ptr<TVariate> TVariateRegister<Type>::CreateVariate(const TSymbol& symbol)
{
	return std::make_shared<Type>(symbol);
}

template<typename Type>
std::shared_ptr<TVariate> TVariateRegister<Type>::GetVariate(QDataStream& data)
{
	return std::make_shared<Type>(data);
}

template<typename Type>
TVariateRegister<Type>::TVariateRegister(const QString& name)
{
	TVariateFactory::FunMapCreateVariate()[name] = CreateVariate;
}

#endif