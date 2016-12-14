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
	//TBool(const QString& scope, const QString& name, const bool value=false);
	TBool(const TBool& variate);
	TBool(QDataStream& dataStream);

	virtual TVariate* Clone() const override;

	const ValueType GetValue() const;
	void SetValue(const ValueType value);


protected:
	virtual void WriteValueToStream(QDataStream& dataStream) const override;
	virtual void UpdateFromValue(const TVariate& variate) override;



private:
	ValueType m_value;

	static TVariateRegister<TBool> m_register;
};

#endif