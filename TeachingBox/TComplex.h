#ifndef _TEACHING_BOX_T_COMPLEX_H_
#define _TEACHING_BOX_T_COMPLEX_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TComplex.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/12/14
//  Description:    复合变量,由基本变量int、double、string、bool组成，该变量提供了一些基本接口用于生成变量控件，
		由四种基本变量组成的变量可继承自此类，并实现所有接口，用于生成控件
//  Others:         
//  Function List:  
//  History:
//    <author>      刘巍 
//    <time>        2016/12/14
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "TVariate.h"
#include "QStringList"
#include <vector>
#include <memory>

class QString;
class VariateValue;
class TVariatePrototype;

class TComplex:public TVariate
{
	friend TVariatePrototype;

public:
	typedef std::vector<std::shared_ptr<VariateValue>> ValueType;
	static const QString TypeName();

public:
	TComplex(const TSymbol& symbol, ValueType value = ValueType{});
	TComplex(const TComplex& variate);

	virtual ~TComplex(){};

	virtual TVariate* Clone() const override;

	virtual QStringList GetValueNames() const;
	virtual ValueType GetValues() const;
	virtual void SetValues(const ValueType& values);

	virtual void WriteValueToStream(QDataStream& dataStream) const override;

	virtual void ReadValueFromStream(QDataStream& dataStream) override;

protected:
	ValueType m_commonValues{};
	QStringList m_valueNames{};
};

#endif // !_TEACHING_BOX_T_COMPLEX_H_
