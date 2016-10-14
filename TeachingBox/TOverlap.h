#ifndef _TEACHING_BOX_TOVERLAP_H_
#define _TEACHING_BOX_TOVERLAP_H_

#include "TVariate.h"
#include "DataStruct.h"

class TOverlap:public TVariate
{
	Q_OBJECT

public:
	static const QString STR_MODE_ABSOLUTE;
	static const QString STR_MODE_RELATIVE;

public:
	TOverlap(const QString& scope, const QString& name, const tOverlapConstraint& value = tOverlapConstraint{});
	TOverlap(const TOverlap& variate);
	TOverlap(QDataStream& dataStream);

	virtual TVariate* Clone() const override;

	const tOverlapConstraint& GetValue() const;
	void SetValue(const tOverlapConstraint& value);

protected:
	virtual void ReadValueStream(QDataStream& dataStream) const override;
	virtual void UpdateFromValue(const TVariate& variate) override;

	void WriteValueSteam(QDataStream& dataStream);


private:
	void Init();

private:
	tOverlapConstraint m_value;
};

#endif