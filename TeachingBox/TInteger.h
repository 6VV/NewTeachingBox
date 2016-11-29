#ifndef _TEACHING_BOX_TINTEGER_H_
#define _TEACHING_BOX_TINTEGER_H_

#include "TVariate.h"

class TInteger:public TVariate
{
	Q_OBJECT

public:
	typedef int ValueType;
	static QString TypeName();

public:
	TInteger(const TSymbol& symbol, ValueType value = 0);
	TInteger(const TInteger& variate);
	TInteger(QDataStream& dataStream);

	virtual TVariate* Clone() const override;

	int GetValue();
	void SetValue(const int value);

protected:
	virtual void WriteValueToStream(QDataStream& dataStream) const override;
	virtual void UpdateFromValue(const TVariate& variate) override;

private:
	void Init();


private:
	int m_value;
};

#endif