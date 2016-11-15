#ifndef _TEACHING_BOX_TDYNAMIC_H_
#define _TEACHING_BOX_TDYNAMIC_H_

#include "TVariate.h"
#include "DataStruct.h"

class TDynamic:public TVariate
{
	Q_OBJECT

public:
	TDynamic(const QString& scope, const QString& name, const tDynamicConstraint& value = tDynamicConstraint{});
	TDynamic(const TDynamic& variate);
	TDynamic(QDataStream& dataStream);

	virtual TVariate* Clone() const override;

	const tDynamicConstraint& GetValue() const;
	void SetValue(const tDynamicConstraint& value);


protected:
	virtual void WriteValueToStream(QDataStream& dataStream) const override;
	virtual void UpdateFromValue(const TVariate& variate) override;

	void WriteValueStream(QDataStream& dataStream);


private:
	void Init();

private:
	tDynamicConstraint m_value;
};

#endif