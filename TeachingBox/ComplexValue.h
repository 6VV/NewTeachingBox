#ifndef _TEACHING_BOX_COMPLEX_VALUE_H_
#define _TEACHING_BOX_COMPLEX_VALUE_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    PositionValue.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/12/13
//  Description:    保存位置值，继承自VariateValue
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/12/13
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "VariateValue.h"
#include <vector>
#include <memory>

	class ComplexValue:public VariateValue
	{
	public:
		typedef std::vector<std::shared_ptr<VariateValue>> ValueType;

	public:
		ComplexValue(ValueType value = {});
		operator ValueType() const;

		virtual void WriteToDataStream(QDataStream& dataStream) const override;

		virtual void ReadFromDataStream(QDataStream& dataStream) override;

		virtual std::shared_ptr<VariateValue> Clone() const override;

	private:
		ValueType m_value;
	};

#endif