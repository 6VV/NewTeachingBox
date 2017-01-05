#ifndef _TEACHING_BOX_TOVERLAP_H_
#define _TEACHING_BOX_TOVERLAP_H_

#include "TVariate.h"
#include "DataStruct.h"
#include "TVariateRegister.h"

class TOverlap:public TVariate
{
	Q_OBJECT

public:
	typedef tOverlapConstraint ValueType;
	static QString TypeName();

public:
	TOverlap(const TSymbol& symbol, ValueType value = ValueType{});
	TOverlap(const TOverlap& variate);

	virtual TVariate* Clone() const override;
	virtual void WriteValueToStream(QDataStream& dataStream) const override;
	virtual void ReadValueFromStream(QDataStream& dataStream) override;

	const ValueType& GetValue() const;
	void SetValue(const ValueType& value);


private:
	ValueType m_value;

	static TVariateRegister<TOverlap> m_register;
};

#endif