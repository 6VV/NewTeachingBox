#ifndef _TEACHING_BOX_TDYNAMIC_H_
#define _TEACHING_BOX_TDYNAMIC_H_

#include "DataStruct.h"
#include "TVariateRegister.h"
#include "TComplex.h"

class TDynamic:public TComplex
{
	Q_OBJECT

public:
	typedef tDynamicConstraint ValueType;
	static QString TypeName();

public:
	TDynamic(const TSymbol& symbol, ValueType value = ValueType{});

	virtual TVariate* Clone() const override;

	const ValueType& GetValue() const;
	void SetValue(const ValueType& value);

private:
	void MakeCommonValue(const ValueType& value);
	ValueType GetSpecialValue() const;

private:
	static TVariateRegister<TDynamic> m_register;
};

#endif