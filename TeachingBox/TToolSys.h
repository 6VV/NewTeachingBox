#ifndef _TEACHING_BOX_T_TOOL_SYS_H_
#define _TEACHING_BOX_T_TOOL_SYS_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TToolSys.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/16
//  Description:	工具坐标系变量，保存工具坐标系的值，并提供相关操作
	继承自TVariate类
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/16
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "TVariate.h"
#include <array>

class TToolSys:public TVariate
{
public:
	typedef std::array<double, 6> ValueType;
	static QString TypeName();

public:
	TToolSys(const TSymbol& symbol, ValueType value = ValueType{});
	TToolSys(const TToolSys& variate);
	TToolSys(QDataStream& dataStream);
	~TToolSys();

	virtual TVariate* Clone() const override;

	ValueType GetValue() const;
	void SetValue(ValueType value);

private:
	virtual void WriteValueToStream(QDataStream& dataStream) const override;
	virtual void UpdateFromValue(const TVariate& variate) override;
	
	void Init();


private:
	ValueType m_value;
};

#endif