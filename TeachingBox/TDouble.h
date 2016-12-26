#ifndef _TEACHING_BOX_TDOUBLE_H_
#define _TEACHING_BOX_TDOUBLE_H_

#include "TVariate.h"
#include "TVariateRegister.h"

class TDouble:public TVariate
{
	Q_OBJECT

public:
	typedef double ValueType;
	static QString TypeName();

public:
	TDouble(const TSymbol& symbol, ValueType value = 0);
	TDouble(const TDouble& variate);

	virtual TVariate* Clone() const override;
	virtual void WriteValueToStream(QDataStream& dataStream) const override;
	virtual void ReadValueFromStream(QDataStream& dataStream) override;

	ValueType GetValue();
	void SetValue(const ValueType value);


private:
	ValueType m_value;

	static TVariateRegister<TDouble> m_register;
};

#endif