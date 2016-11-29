#ifndef _TEACHING_BOX_TDOUBLE_H_
#define _TEACHING_BOX_TDOUBLE_H_

#include "TVariate.h"

class TDouble:public TVariate
{
	Q_OBJECT

public:
	typedef double ValueType;
	static QString TypeName();

public:
	TDouble(const TSymbol& symbol, ValueType value = 0);
	TDouble(const TDouble& variate);
	TDouble(QDataStream& dataStream);

	virtual TVariate* Clone() const override;

	ValueType GetValue();
	void SetValue(const ValueType value);

protected:
	virtual void WriteValueToStream(QDataStream& dataStream) const override;
	virtual void UpdateFromValue(const TVariate& variate) override;


private:
	void Init();


private:
	ValueType m_value;
};

#endif