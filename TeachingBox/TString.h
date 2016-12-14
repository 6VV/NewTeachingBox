#ifndef _TEACHING_BOX_TSTRING_H_
#define _TEACHING_BOX_TSTRING_H_

#include "TVariate.h"
#include "TVariateRegister.h"

class TString:public TVariate
{
	Q_OBJECT

public:
	typedef QString ValueType;
	static QString TypeName();

public:
	TString(const TSymbol& symbol, ValueType value = "");
	TString(const TString& variate);
	TString(QDataStream& dataStream);

	virtual TVariate* Clone() const override;

	const ValueType GetValue() const;
	void SetValue(const ValueType& value);


protected:
	virtual void WriteValueToStream(QDataStream& dataStream) const override;
	virtual void UpdateFromValue(const TVariate& variate) override;


private:
	ValueType m_value;

	static TVariateRegister<TString> m_register;
};

#endif