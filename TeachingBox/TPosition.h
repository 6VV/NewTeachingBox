#ifndef _TEACHING_BOX_TPOSITION_H_
#define _TEACHING_BOX_TPOSITION_H_

#include "QVector"
#include "DataStruct.h"
#include "TVariateRegister.h"
#include "TComplex.h"

class TPosition:public TComplex
{
	Q_OBJECT

public:
	typedef tAxesAllPositions ValueType;
	static QString TypeName();

public:
	TPosition(const TSymbol& symbol, ValueType value = ValueType{});

	virtual TVariate* Clone() const override;

	const ValueType GetValue() const;

	void SetValue(const ValueType& value);

private:
	void MakeCommonValue(const ValueType& value);
	ValueType GetSpecialValue() const;

private:
	static TVariateRegister<TPosition> m_register;
};

#endif