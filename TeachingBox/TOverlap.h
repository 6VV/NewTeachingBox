#ifndef _TEACHING_BOX_TOVERLAP_H_
#define _TEACHING_BOX_TOVERLAP_H_

#include "TVariate.h"
#include "DataStruct.h"

class TOverlap:public TVariate
{
	Q_OBJECT

public:
	typedef tOverlapConstraint ValueType;
	static QString TypeName();

public:
	TOverlap(const TSymbol& symbol, ValueType value = ValueType{});
	TOverlap(const TOverlap& variate);
	TOverlap(QDataStream& dataStream);

	virtual TVariate* Clone() const override;

	const ValueType& GetValue() const;
	void SetValue(const ValueType& value);

protected:
	virtual void WriteValueToStream(QDataStream& dataStream) const override;
	virtual void UpdateFromValue(const TVariate& variate) override;

	void WriteValueSteam(QDataStream& dataStream);


private:
	void Init();


private:
	ValueType m_value;
};

#endif