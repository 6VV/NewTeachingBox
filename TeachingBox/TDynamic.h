#ifndef _TEACHING_BOX_TDYNAMIC_H_
#define _TEACHING_BOX_TDYNAMIC_H_

#include "TVariate.h"
#include "DataStruct.h"
#include "TVariateRegister.h"

class TDynamic:public TVariate
{
	Q_OBJECT

public:
	typedef tDynamicConstraint ValueType;
	static QString TypeName();

public:
	TDynamic(const TSymbol& symbol, ValueType value = ValueType{});
	TDynamic(const TDynamic& variate);
	//TDynamic(QDataStream& dataStream);

	virtual TVariate* Clone() const override;
	virtual void WriteValueToStream(QDataStream& dataStream) const override;
	virtual void ReadValueFromStream(QDataStream& dataStream) override;

	const ValueType& GetValue() const;
	void SetValue(const ValueType& value);


private:
	ValueType m_value;

	static TVariateRegister<TDynamic> m_register;
};

#endif