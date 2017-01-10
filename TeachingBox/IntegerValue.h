#ifndef _TEACHING_BOX_INTEGER_VALUE_H_
#define _TEACHING_BOX_INTEGER_VALUE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    IntegerValue.h
//  Author:			刘巍
//  Version: 		1.0
//  Date: 			2016/12/13
//  Description:    保存整数值，并继承自VariateValue
//  Others:
//  Function List:
//  History:
//    <author>      刘巍
//    <time>        2016/12/13
//    <version>     1.0
//    <desc>        build this moudle
*************************************************/

#include "VariateValue.h"
#include "VariateValueRegister.h"

class IntegerValue :public VariateValue
{
public:
	typedef int ValueType;
	static QString TypeText();

public:
	explicit IntegerValue(int value=0);
	operator int() const;

	virtual void WriteToDataStream(QDataStream& dataStream) const override;


	virtual void ReadFromDataStream(QDataStream& dataStream) override;

	virtual std::shared_ptr<VariateValue> Clone() const override;

	virtual QStringList ToStrings() override;


private:
	int m_value = 0;

	static VariateValueRegister<IntegerValue> m_register;
};


#endif // !_TEACHING_BOX_N_VARIATE_VALUE_INTEGER_VALUE_H_
