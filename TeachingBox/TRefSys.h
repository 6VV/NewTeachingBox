#ifndef _TEACHING_BOX_T_REF_SYS_H_
#define _TEACHING_BOX_T_REF_SYS_H_

/*************************************************
//  Copyright (C), 2015-2016, CS&S. Co., Ltd.
//  File name: 	    TRefSys.h
//  Author:			刘巍      
//  Version: 		1.0     
//  Date: 			2016/11/14
//  Description:	系统参考坐标系变量。
	包括：
	基坐标系：即建立的参考坐标系是参考哪个坐标系建立的；
	x，y，z： 分别是相对于基坐标系的位置偏移；
	a，b，c：是相对于基坐标系的姿态。
	位置偏移及姿态采用一个含有6个元素的double数组表示，数组前三个值表示偏移，后三个值表示姿态。
	本变量行为与TInteger等普通变量类似，也具有全局、局部等作用域。
//  Others:
//  Function List:
//  History:
//    <author>      刘巍 
//    <time>        2016/11/14
//    <version>     1.0 
//    <desc>        build this moudle     
*************************************************/

#include "TVariate.h"
#include <utility>
#include <array>

class TRefSys:public TVariate
{
public:
	typedef QString BaseSysType;	/*基坐标系相关信息，分别为坐标系名及作用域*/
	typedef std::array<double, 6> OffsetType;	/*参考坐标系相对于基坐标系的偏移及姿态*/
	typedef struct  
	{
		BaseSysType baseSys;
		OffsetType offset;
	} ValueType;

	static QString TypeName();

public:
	TRefSys(const TSymbol& symbol, ValueType value = ValueType{});
	//TRefSys(const QString& scope, const QString& name, const ValueType& value = ValueType{});
	TRefSys(const TRefSys& refSys);
	TRefSys(QDataStream& dataStream);
	~TRefSys();

	virtual TVariate* Clone() const override;

	ValueType GetValue() const;
	void SetValue(ValueType value);

private:
	virtual void WriteValueToStream(QDataStream& dataStream) const override;
	virtual void UpdateFromValue(const TVariate& variate) override;

	void Init();


private:
	ValueType m_value{};	/*位置偏移及姿态*/
};

#endif