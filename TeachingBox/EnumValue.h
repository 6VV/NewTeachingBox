#ifndef _TEACHING_BOX_ENUM_VALUE_H_
#define _TEACHING_BOX_ENUM_VALUE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    EnumValue.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2017/01/09
//  Description:    基本变量值：枚举值
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2017/01/09
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "VariateValue.h"
#include <map>

class EnumValue:public VariateValue
{
public:
	typedef std::map<int, QString> EnumMapType;

public:
	EnumValue(int id);
	EnumValue(const QString& text);
	EnumValue(const EnumMapType& enumMap);

	operator int() const;

	virtual std::shared_ptr<VariateValue> Clone() const override;

	virtual void WriteToDataStream(QDataStream& dataStream) const override;

	virtual void ReadFromDataStream(QDataStream& dataStream) override;

	virtual QStringList ToStrings() override;

	QStringList Texts() const;

private:
	EnumMapType m_enumMap{};
	int m_value = 0;
};

#endif