#ifndef _TEACHING_BOX_TPOSITION_H_
#define _TEACHING_BOX_TPOSITION_H_

#include "TComplex.h"

struct tAxesAllPositions;

class TPosition
{
public:
	//typedef tAxesAllPositions ValueType;
	static QString TypeName();
	static TComplex::ValueType ToCommonValue(const tAxesAllPositions& value);

public:
	//TPosition(const TSymbol& symbol, ValueType value = ValueType{});

	//virtual TVariate* Clone() const override;

	//void SetValue(const ValueType& value);

private:


private:
	//static TVariateRegister<TPosition> m_register;
};

#endif