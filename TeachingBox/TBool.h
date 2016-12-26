#ifndef _TEACHING_BOX_TBOOL_H_
#define _TEACHING_BOX_TBOOL_H_

#include "TVariate.h"
#include "QString"
#include "TVariateRegister.h"

class TBool:public TVariate
{
	Q_OBJECT

public:
	typedef bool ValueType;
	static QString TypeName();

public:
	TBool(const TSymbol& symbol, ValueType value = false);

	virtual TVariate* Clone() const override;
	virtual void WriteValueToStream(QDataStream& dataStream) const override;
	virtual void ReadValueFromStream(QDataStream& dataStream) override;

	const ValueType GetValue() const;
	void SetValue(const ValueType value);




private:
	ValueType m_value;

	static TVariateRegister<TBool> m_register;
};

#endif