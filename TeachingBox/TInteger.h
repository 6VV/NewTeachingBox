#ifndef _TEACHING_BOX_TINTEGER_H_
#define _TEACHING_BOX_TINTEGER_H_

#include "TVariate.h"
#include "TVariateRegister.h"

class TInteger:public TVariate
{
	Q_OBJECT

public:
	typedef int ValueType;
	static QString TypeName();

public:
	TInteger(const TSymbol& symbol=TSymbol{}, ValueType value = 0);
	TInteger(const TInteger& variate);
	//TInteger(QDataStream& dataStream);

	virtual TVariate* Clone() const override;
	virtual void WriteValueToStream(QDataStream& dataStream) const override;
	virtual void ReadValueFromStream(QDataStream& dataStream) override;

	int GetValue();
	void SetValue(const int value);


private:
	ValueType m_value;

	static TVariateRegister<TInteger> m_register;
};

#endif