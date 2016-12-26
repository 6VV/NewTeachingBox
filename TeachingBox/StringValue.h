#ifndef _TEACHING_BOX_STRING_VALUE_H_
#define _TEACHING_BOX_STRING_VALUE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    StringValue.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/12/15
//  Description:    保存字符串值，继承自VariateValue
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/12/15
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "VariateValue.h"

class StringValue:public VariateValue
{
public:
	typedef QString ValueType;

public:
	explicit StringValue(ValueType value);
	operator ValueType() const;

	virtual void WriteToDataStream(QDataStream& dataStream) const override;

	virtual void ReadFromDataStream(QDataStream& dataStream) override;

private:
	ValueType m_value;
};

#endif