#ifndef _TEACHING_BOX_TPOSITION_H_
#define _TEACHING_BOX_TPOSITION_H_

#include "TVariate.h"
#include "QVector"
#include "DataStruct.h"
#include "TVariateRegister.h"

class TPosition:public TVariate
{
	Q_OBJECT

public:
	typedef tAxesAllPositions ValueType;
	static QString TypeName();

public:
	TPosition(const TSymbol& symbol, ValueType value = ValueType{});
	TPosition(const TPosition& variate);
	TPosition(QDataStream& dataStream);

	virtual TVariate* Clone() const override;

	const ValueType GetValue() const;

	void SetValue(const ValueType& value);


private:
	virtual void WriteValueToStream(QDataStream& dataStream) const override;

	virtual void UpdateFromValue(const TVariate& variate) override;

private:
	ValueType m_value;

	static TVariateRegister<TPosition> m_register;
};

#endif