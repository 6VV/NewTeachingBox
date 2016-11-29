#ifndef _TEACHING_BOX_TDYNAMIC_H_
#define _TEACHING_BOX_TDYNAMIC_H_

#include "TVariate.h"
#include "DataStruct.h"

class TDynamic:public TVariate
{
	Q_OBJECT

public:
	typedef tDynamicConstraint ValueType;
	static QString TypeName();

public:
	TDynamic(const TSymbol& symbol, ValueType value = ValueType{});
	//TDynamic(const QString& scope, const QString& name, const ValueType& value = tDynamicConstraint{});
	TDynamic(const TDynamic& variate);
	TDynamic(QDataStream& dataStream);

	virtual TVariate* Clone() const override;

	const ValueType& GetValue() const;
	void SetValue(const ValueType& value);


protected:
	virtual void WriteValueToStream(QDataStream& dataStream) const override;
	virtual void UpdateFromValue(const TVariate& variate) override;

	void WriteValueStream(QDataStream& dataStream);


private:
	void Init();


private:
	ValueType m_value;
};

#endif